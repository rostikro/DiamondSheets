#include "ExpressionParser.h"
#include <qdebug.h>
#include "qregularexpression.h"

std::any ExpressionParser::visitNumericAtomExp(DiamondSheetsParser::NumericAtomExpContext* ctx)
{
	return std::stod(ctx->getText());
}

std::any ExpressionParser::visitAddSubExp(DiamondSheetsParser::AddSubExpContext* ctx)
{
	auto l_any = visit(ctx->expression(0));
	if (!l_any.has_value())
	{
		return std::any();
	}

	auto r_any = visit(ctx->expression(1));
	if (!r_any.has_value())
	{
		return std::any();
	}

	double l = 0;
	if (!strcmp(l_any.type().name(), "bool"))
	{
		l = std::any_cast<bool>(l_any);
	}
	else
	{
		l = std::any_cast<double>(l_any);
	}

	double r = 0;
	if (!strcmp(r_any.type().name(), "bool"))
	{
		r = std::any_cast<bool>(r_any);
	}
	else
	{
		r = std::any_cast<double>(r_any);
	}

	if (ctx->PLUS() != nullptr)
	{
		return l + r;
	}

	return l - r;
}

std::any ExpressionParser::visitMulDivModExp(DiamondSheetsParser::MulDivModExpContext* ctx)
{
	auto l_any = visit(ctx->expression(0));
	if (!l_any.has_value())
	{
		return std::any();
	}

	auto r_any = visit(ctx->expression(1));
	if (!r_any.has_value())
	{
		return std::any();
	}

	double l = 0;
	if (!strcmp(l_any.type().name(), "bool"))
	{
		l = std::any_cast<bool>(l_any);
	}
	else
	{
		l = std::any_cast<double>(l_any);
	}

	double r = 0;
	if (!strcmp(r_any.type().name(), "bool"))
	{
		r = std::any_cast<bool>(r_any);
	}
	else
	{
		r = std::any_cast<double>(r_any);
	}

	if (ctx->MULTIPLY() != nullptr)
	{
		return l * r;
	}

	if (ctx->DIVIDE() != nullptr)
	{
		if (r == 0) return std::any();
		return l / r;
	}

	if (ctx->INTDIV() != nullptr)
	{
		if (r == 0) return std::any();
		return (double)((int)(l / r));
	}

	return std::fmod(l, r);
}

std::any ExpressionParser::visitParenthesisExp(DiamondSheetsParser::ParenthesisExpContext* ctx)
{
	return visit(ctx->expression());
}

std::any ExpressionParser::visitPowerExp(DiamondSheetsParser::PowerExpContext* ctx)
{
	auto l_any = visit(ctx->expression(0));
	if (!l_any.has_value())
	{
		return std::any();
	}

	auto r_any = visit(ctx->expression(1));
	if (!r_any.has_value())
	{
		return std::any();
	}

	double l = 0;
	if (!strcmp(l_any.type().name(), "bool"))
	{
		l = std::any_cast<bool>(l_any);
	}
	else
	{
		l = std::any_cast<double>(l_any);
	}

	double r = 0;
	if (!strcmp(r_any.type().name(), "bool"))
	{
		r = std::any_cast<bool>(r_any);
	}
	else
	{
		r = std::any_cast<double>(r_any);
	}

	return pow(l, r);
}

std::any ExpressionParser::visitCompExp(DiamondSheetsParser::CompExpContext* ctx)
{
	auto l_any = visit(ctx->expression(0));
	if (!l_any.has_value())
	{
		return std::any();
	}

	auto r_any = visit(ctx->expression(1));
	if (!r_any.has_value())
	{
		return std::any();
	}

	double l = 0;
	if (!strcmp(l_any.type().name(), "bool"))
	{
		l = std::any_cast<bool>(l_any);
	}
	else
	{
		l = std::any_cast<double>(l_any);
	}

	double r = 0;
	if (!strcmp(r_any.type().name(), "bool"))
	{
		r = std::any_cast<bool>(r_any);
	}
	else
	{
		r = std::any_cast<double>(r_any);
	}

	if (ctx->LCOMP() != nullptr)
	{
		return l < r;
	}

	if (ctx->RCOMP() != nullptr)
	{
		return l > r;
	}

	if (ctx->EQCOMP() != nullptr)
	{
		return l == r;
	}

	if (ctx->NEQCOMP() != nullptr)
	{
		return l != r;
	}

	if (ctx->LEQCOMP() != nullptr)
	{
		return l <= r;
	}

	return l >= r;
}

std::any ExpressionParser::visitCellIdAtomExp(DiamondSheetsParser::CellIdAtomExpContext* ctx)
{
	auto cellId = To10Base(ctx->getText());
	QString value = _gridData->operator[](cellId[0])[cellId[1]].getValue();

	if (value == nullptr)
		return (double)0;

	if (value == "#ПОМИЛКА")
		return std::any();

	if (value == "ПРАВДА")
		return (double)1;

	if (value == "НЕПРАВДА")
		return (double)0;

	for (auto& c : value)
	{
		if (!c.isDigit()) return std::any();
	}

	return std::stod(value.toStdString());
}

std::vector<int> ExpressionParser::To10Base(std::string cellId)
{
	int numberStart = -1;
	int columnId = 0;

	for (int i = 0; i < cellId.size(); i++)
	{
		if (std::isdigit(cellId[i]))
		{
			numberStart = i;
			break;
		}

		columnId = columnId * 26 + cellId[i] - 'A';
	}

	int rowId = std::atoi(cellId.substr(numberStart, cellId.size() - numberStart).c_str()) - 1;

	return { rowId, columnId };
}
