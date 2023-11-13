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

    void addRef(std::shared_ptr<Cell>& cell) { refs.push_back(cell); }
    void deleteRef(std::shared_ptr<Cell>& cell) { refs.erase(std::remove(refs.begin(), refs.end(), cell)); }
    std::vector<std::shared_ptr<Cell>>& getRefs() { return refs; }

    void addReferenced(std::shared_ptr<Cell>& cell) { referenced.push_back(cell); }
    std::vector<std::shared_ptr<Cell>>& getReferenced() { return referenced; }
    void clearReferenced() { referenced.clear(); }
    bool isReferenced(std::shared_ptr<Cell>& cell) { return std::find(referenced.begin(), referenced.end(), cell) != referenced.end(); }

public:
    bool visited = false;

private:
    QString expression;
    QString value;

    std::vector<std::shared_ptr<Cell>> refs; // Notify
    std::vector<std::shared_ptr<Cell>> referenced; // We are reference
};
