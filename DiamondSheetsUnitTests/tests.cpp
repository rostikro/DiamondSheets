
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "antlr4-runtime.h"
#include "../DiamondSheets/AntlrGrammar/DiamondSheetsLexer.h"
#include "../DiamondSheets/AntlrGrammar/DiamondSheetsParser.h"

#include "../DiamondSheets/ExpressionParser.h"

#include "qstring.h"
#include "../DiamondSheets/Cell.h"

using namespace testing;

namespace gtest
{
    QString EvaluateExpression(QString expression)
    {
        std::vector<std::vector<Cell>> gridData{ {Cell("11", "11"), Cell("12", "12")}, {Cell("21", "21"), Cell("22", "22")}};
        expression[0] = ' ';

        antlr4::ANTLRInputStream input(expression.toStdString());
        DiamondSheetsLexer lexer(&input);
        antlr4::CommonTokenStream tokens(&lexer);
        tokens.fill();
        DiamondSheetsParser parser(&tokens);
        DiamondSheetsParser::ExpressionContext* expressionContext = parser.expression();

        ExpressionParser expressionParser(&gridData);

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


    TEST(BinaryOp, Plus_Minus)
    {
        EXPECT_EQ(EvaluateExpression("=5+2"), "7");
        EXPECT_EQ(EvaluateExpression("=5-10"), "-5");
        EXPECT_EQ(EvaluateExpression("=5-10+30-25"), "0");
    }

    TEST(BinaryOp, Mul_Div_Mod)
    {
        EXPECT_EQ(EvaluateExpression("=5*2"), "10");
        EXPECT_EQ(EvaluateExpression("=5/2"), "2.5");
        EXPECT_EQ(EvaluateExpression("=5/0"), "#ПОМИЛКА");
        EXPECT_EQ(EvaluateExpression("=5//2"), "2");
        EXPECT_EQ(EvaluateExpression("=5//0"), "#ПОМИЛКА");
        EXPECT_EQ(EvaluateExpression("=10%3"), "1");
    }

    TEST(BinaryOp, Power)
    {
        EXPECT_EQ(EvaluateExpression("=5^2"), "25");
        EXPECT_EQ(EvaluateExpression("=3^2^3"), "6561");
    }

    TEST(Comparison, Comparisons)
    {
        EXPECT_EQ(EvaluateExpression("=5=5"), "ПРАВДА");
        EXPECT_EQ(EvaluateExpression("=5=7"), "НЕПРАВДА");

        EXPECT_EQ(EvaluateExpression("=8>7"), "ПРАВДА");
        EXPECT_EQ(EvaluateExpression("=5>8"), "НЕПРАВДА");

        EXPECT_EQ(EvaluateExpression("=6<10"), "ПРАВДА");
        EXPECT_EQ(EvaluateExpression("=5<1"), "НЕПРАВДА");

        EXPECT_EQ(EvaluateExpression("=6<=10"), "ПРАВДА");
        EXPECT_EQ(EvaluateExpression("=7<=7"), "ПРАВДА");
        EXPECT_EQ(EvaluateExpression("=7<=5"), "НЕПРАВДА");

        EXPECT_EQ(EvaluateExpression("=10>=6"), "ПРАВДА");
        EXPECT_EQ(EvaluateExpression("=7>=7"), "ПРАВДА");
        EXPECT_EQ(EvaluateExpression("=5>=7"), "НЕПРАВДА");

        EXPECT_EQ(EvaluateExpression("=5<>5"), "НЕПРАВДА");
        EXPECT_EQ(EvaluateExpression("=5<>7"), "ПРАВДА");
    }

    TEST(Parenthesis, Parenthesis)
    {
        EXPECT_EQ(EvaluateExpression("=(5+5)*2"), "20");
        EXPECT_EQ(EvaluateExpression("=(5*2)^2"), "100");
    }

    TEST(AtomExp, AtomExp)
    {
        EXPECT_EQ(EvaluateExpression("=122"), "122");
        EXPECT_EQ(EvaluateExpression("=A1"), "11");
    }

}
