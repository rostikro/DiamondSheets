#pragma once

#include <QString>

class Cell
{
public:
    Cell() = default;
    Cell(QString expression, QString value) : expression(expression), value(value) {}

    static const QString errorText;
    static const QString refErrorText;
    static const QString trueText;
    static const QString falseText;

    // Getters and setters
public:
    void setExpression(const QString& expression) { this->expression = expression; value = expression; }
    void setValue(const QString& value) { this->value = value; }
    QString getExpression() const { return expression; }
    QString getValue() const { return value; }

    void addRef(Cell* cell) { refs.push_back(cell); }
    void deleteRef(Cell* cell) { refs.erase(std::remove(refs.begin(), refs.end(), cell)); }
    std::vector<Cell*> getRefs() { return refs; }

    void addReferenced(Cell* cell) { referenced.push_back(cell); }
    std::vector<Cell*> getReferenced() { return referenced; }
    void clearReferenced() { referenced.clear(); }
    bool isReferenced(Cell* cell) { return std::find(referenced.begin(), referenced.end(), cell) != referenced.end(); }

public:
    bool visited = false;

private:
    QString expression;
    QString value;

    std::vector<Cell*> refs; // Notify
    std::vector<Cell*> referenced; // We are reference
};
