#include "TableModel.h"

#include "antlr4-runtime.h"
#include "AntlrGrammar/DiamondSheetsLexer.h"
#include "AntlrGrammar/DiamondSheetsParser.h"

#include "ExpressionParser.h"
#include "ParserResult.h"

TableModel::TableModel(QObject* parent)
    : QAbstractTableModel(parent)
{
    SetDefault();
}

int TableModel::rowCount(const QModelIndex&) const
{
    return _rows;
}

int TableModel::columnCount(const QModelIndex&) const
{
    return _columns;
}

QVariant TableModel::data(const QModelIndex& index, int role) const
{
    if (checkIndex(index))
    {
        if (role == Qt::DisplayRole)
            return _gridData[index.row()][index.column()].getValue();
        if (role == Qt::EditRole)
            return _gridData[index.row()][index.column()].getExpression();
    }

    return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
            return To26Base(section);

        return section + 1;
    }

    return QVariant();
}

bool TableModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (role == Qt::EditRole)
    {
        if (!checkIndex(index))
            return false;

        // Clear all references that this cell refers to
        for (auto cell : _gridData[index.row()][index.column()].getReferenced())
        {
            cell->deleteRef(&_gridData[index.row()][index.column()]);
        }
        _gridData[index.row()][index.column()].clearReferenced();

        _gridData[index.row()][index.column()].setExpression(value.toString());
        if (value.toString().size() > 0)
            if (value.toString()[0] == '=')
                _gridData[index.row()][index.column()].setValue(EvaluateExpression(value.toString(), &_gridData[index.row()][index.column()], false));


        if (DetectLoop(&_gridData[index.row()][index.column()]))
        {
            _gridData[index.row()][index.column()].setValue(Cell::refErrorText);
            SetREFError(&_gridData[index.row()][index.column()]);

            return true;
        }

        // Update refs
        for (auto& cell : _gridData[index.row()][index.column()].getRefs())
        {
            UpdateCell(cell);
        }

        Q_EMIT EditCompleted();
        return true;
    }

    return false;
}

void TableModel::SetREFError(Cell* cell)
{
    for (auto ref : cell->getRefs())
    {
        if (ref->getValue() == Cell::refErrorText)
            return;

        ref->setValue(Cell::refErrorText);
        SetREFError(ref);
    }
}

void TableModel::UpdateCell(Cell* cell)
{
    if (DetectLoop(cell))
        return;

    if (cell->getExpression()[0] == '=')
        cell->setValue(EvaluateExpression(cell->getExpression(), cell, true));

    auto test = cell->getRefs();
    // Update refs
    for (auto& cell : cell->getRefs())
    {
        UpdateCell(cell);
    }
}

QString TableModel::EvaluateExpression(QString expression, Cell* cell, bool isUpdate)
{
    expression[0] = ' ';

    antlr4::ANTLRInputStream input(expression.toStdString());
    DiamondSheetsLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    tokens.fill();
    DiamondSheetsParser parser(&tokens);
    DiamondSheetsParser::ExpressionContext* expressionContext = parser.expression();

    ExpressionParser expressionParser(&_gridData, cell, isUpdate);

    auto result_any = expressionParser.visit(expressionContext);
    if (!result_any.has_value())
        return Cell::errorText;

    auto result = std::any_cast<ParserResult>(result_any);

    if (result.type == 0)
    {
        return result.error;
    }

    if (result.type == 1)
    {
        return QString::number(result.value);
    }

    // type == 2
    return result.value ? Cell::trueText : Cell::falseText;
}

bool TableModel::DetectLoop(Cell* cell)
{
    cell->visited = 1;

    for (auto ref : cell->getReferenced())
    {
        if (ref->visited)
        {
            ref->visited = 0;
            return 1;
        }

        if (DetectLoop(ref))
            return 1;
    }

    cell->visited = 0;
    return 0;
}

void TableModel::AddRow(QModelIndex index, int offset)
{
    if (index.row() == -1)
        offset = _rows + 1;

    _gridData.insert(_gridData.begin() + (index.row() + offset), std::vector<Cell>(_columns));
    _rows++;
    Q_EMIT layoutChanged();
}

void TableModel::AddColumn(QModelIndex index, int offset)
{
    if (index.column() == -1)
        offset = _columns + 1;

    for (auto& row : _gridData)
        row.insert(row.begin() + (index.column() + offset), Cell());

    _columns++;
    Q_EMIT layoutChanged();
}

void TableModel::DeleteRow(QModelIndex index)
{
    if (index.row() == -1 || _rows == 1)
        return;

    _gridData.erase(_gridData.begin() + index.row());
    _rows--;
    Q_EMIT layoutChanged();
}

void TableModel::DeleteColumn(QModelIndex index)
{
    if (index.column() == -1 || _columns == 1)
        return;

    for (auto& row : _gridData)
    {
        row.erase(row.begin() + index.column());
    }

    _columns--;
    Q_EMIT layoutChanged();
}

Qt::ItemFlags TableModel::flags(const QModelIndex& index) const
{
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}

void TableModel::Serialize(QTextStream& out)
{
    for (int i = 0; i < _gridData.size(); i++)
    {
        if (i != 0) out << "\n";
        for (auto& cell : _gridData[i])
        {
            if (!cell.getExpression().isEmpty())
                out << cell.getExpression();
            out << ",";
        }
    }
}

void TableModel::Deserialize(QTextStream& in)
{
    _gridData.clear();
    int rowIndex = 0;

    while(!in.atEnd())
    {
        std::vector<Cell> data;

        int columnIndex = 0;
        int delimiterIndex = -1;

        QChar delimiter = ',';

        auto row = in.readLine();
        for (int i = 0; i < row.size(); i++)
        {
            if (row[i] == delimiter)
            {
                if (delimiterIndex + 1 == i)
                {
                    delimiterIndex = i;
                    columnIndex++;
                    data.push_back(Cell());
                    continue;
                }

                QString expression = row.mid(delimiterIndex + 1, i - delimiterIndex - 1);

                // Cell only with expression
                data.push_back(Cell(expression, ""));

                delimiterIndex = i;
                columnIndex++;
            }
        }
        rowIndex++;
        _gridData.push_back(data);
    }

    // Evaluate all expressions
    int i = -1;
    for (auto& row : _gridData)
    {
        i++;
        int j = -1;
        for (auto& cell : row)
        {
            j++;
            if (cell.getExpression() == nullptr) continue;
            setData(createIndex(i, j), cell.getExpression());
        }
    }

    _rows = _gridData.size();
    _columns = _gridData[0].size();

    Q_EMIT layoutChanged();
}

QString TableModel::To26Base(int index) const
{
    if (index < 26)
        return QChar(index + 'A');

    return To26Base(index / 26 - 1) + To26Base(index % 26);
}

void TableModel::SetDefault()
{
    _rows = defaultRows;
    _columns = defaultColumns;
    _gridData = std::vector(_rows, std::vector<Cell>(_columns));
    Q_EMIT dataChanged(createIndex(0, 0), createIndex(_rows - 1, _columns - 1));
    Q_EMIT layoutChanged();
}
