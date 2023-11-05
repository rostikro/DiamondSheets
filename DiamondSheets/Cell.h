#pragma once

#include <QString>

class Cell
{
public:
    Cell() = default;
    Cell(QString expression, QString value) : expression(expression), value(value) {}

    // Getters and setters
public:
    void setExpression(const QString& expression) { this->expression = expression; value = expression; }
    void setValue(const QString& value) { this->value = value; }
    QString getExpression() const { return expression; }
    QString getValue() const { return value; }

private:
    QString expression;
    QString value;
};
