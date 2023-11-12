#pragma once

#include "Cell.h"
#include <QAbstractTableModel>
#include <QTimer>


class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    TableModel(QObject* parent = nullptr);
    ~TableModel() = default;

    void Serialize(QTextStream& out);
    void Deserialize(QTextStream& in);

private:
    int rowCount(const QModelIndex& index = QModelIndex()) const override;
    int columnCount(const QModelIndex& index = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    QString To26Base(int index) const;
    QString EvaluateExpression(QString expression, Cell* cell, bool isUpdate);
    void UpdateCell(Cell* cell);
    void SetREFError(Cell* cell);
    bool DetectLoop(Cell* cell);

public Q_SLOTS:
    void SetDefault();

    void AddRow(QModelIndex index, int offset = 0);
    void AddColumn(QModelIndex index, int offset = 0);
    void DeleteRow(QModelIndex index);
    void DeleteColumn(QModelIndex index);

Q_SIGNALS:
    void EditCompleted();

private:
    const int defaultRows = 10, defaultColumns = 10;
    int _rows, _columns;
    std::vector<std::vector<Cell>> _gridData;
};
