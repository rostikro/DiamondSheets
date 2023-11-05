#include "TableModel.h"

#include "antlr4-runtime.h"
#include "AntlrGrammar/DiamondSheetsLexer.h"
#include "AntlrGrammar/DiamondSheetsParser.h"

#include "ExpressionParser.h"

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

        _gridData[index.row()][index.column()].setExpression(value.toString());
        if (value.toString().size() > 0)
            if (value.toString()[0] == '=')
                _gridData[index.row()][index.column()].setValue(EvaluateExpression(value.toString()));

        Q_EMIT EditCompleted();
        return true;
    }

    return false;
}

QString TableModel::EvaluateExpression(QString expression)
{
    expression[0] = ' ';

    antlr4::ANTLRInputStream input(expression.toStdString());
    DiamondSheetsLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    tokens.fill();
    DiamondSheetsParser parser(&tokens);
    DiamondSheetsParser::ExpressionContext* expressionContext = parser.expression();

    ExpressionParser expressionParser(&_gridData);

    auto exp_any = expressionParser.visit(expressionContext);

    if (!exp_any.has_value())
    {
        return "#ПОМИЛКА";
    }
    if (!strcmp(exp_any.type().name(), "bool"))
    {
        bool val = std::any_cast<bool>(exp_any);
        return val ? "ПРАВДА" : "НЕПРАВДА";
    }

    return QString::number(std::any_cast<double>(exp_any));
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
        row.erase(row.begin() + index.column());

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
                data.push_back(Cell(expression, expression[0] == '=' ? EvaluateExpression(expression) : expression));
                delimiterIndex = i;
                columnIndex++;
            }
        }
        rowIndex++;
        _gridData.push_back(data);
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
