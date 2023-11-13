#include "ExpressionParser.h"
#include <qdebug.h>
#include "qregularexpression.h"

#include "ParserResult.h"

std::any ExpressionParser::visitNumericAtomExp(DiamondSheetsParser::NumericAtomExpContext* ctx)
{
	return ParserResult(std::stod(ctx->getText()));
}

std::any ExpressionParser::visitAddSubExp(DiamondSheetsParser::AddSubExpContext* ctx)
{
	auto l_any = visit(ctx->expression(0));
	if (!l_any.has_value())
		return ParserResult(Cell::errorText);
	auto r_any = visit(ctx->expression(1));
	if (!r_any.has_value())
		return ParserResult(Cell::errorText);

	auto l_result = std::any_cast<ParserResult>(l_any);
	if (l_result.type == 0)
		return l_result;

	double l = l_result.value;

	auto r_result = std::any_cast<ParserResult>(r_any);
	if (r_result.type == 0)
		return r_result;

	double r = r_result.value;

	if (ctx->PLUS() != nullptr)
	{
		return ParserResult(l + r);
	}

	return ParserResult(l - r);
}

std::any ExpressionParser::visitMulDivModExp(DiamondSheetsParser::MulDivModExpContext* ctx)
{
	auto l_any = visit(ctx->expression(0));
	if (!l_any.has_value())
		return ParserResult(Cell::errorText);
	auto r_any = visit(ctx->expression(1));
	if (!r_any.has_value())
		return ParserResult(Cell::errorText);

	auto l_result = std::any_cast<ParserResult>(l_any);
	if (l_result.type == 0)
		return l_result;

	double l = l_result.value;

	auto r_result = std::any_cast<ParserResult>(r_any);
	if (r_result.type == 0)
		return r_result;

	double r = r_result.value;

	if (ctx->MULTIPLY() != nullptr)
	{
		return ParserResult(l * r);
	}

	if (ctx->DIVIDE() != nullptr)
	{
		if (r == 0) return ParserResult(Cell::errorText);
		return ParserResult(l / r);
	}

	if (ctx->INTDIV() != nullptr)
	{
		if (r == 0) return ParserResult(Cell::errorText);
		return ParserResult((int)(l / r));
	}

	return ParserResult(std::fmod(l, r));
}

std::any ExpressionParser::visitParenthesisExp(DiamondSheetsParser::ParenthesisExpContext* ctx)
{
	return std::any_cast<ParserResult>(visit(ctx->expression()));
}

std::any ExpressionParser::visitPowerExp(DiamondSheetsParser::PowerExpContext* ctx)
{
	auto l_any = visit(ctx->expression(0));
	if (!l_any.has_value())
		return ParserResult(Cell::errorText);
	auto r_any = visit(ctx->expression(1));
	if (!r_any.has_value())
		return ParserResult(Cell::errorText);

	auto l_result = std::any_cast<ParserResult>(l_any);
	if (l_result.type == 0)
		return l_result;

	double l = l_result.value;

	auto r_result = std::any_cast<ParserResult>(r_any);
	if (r_result.type == 0)
		return r_result;

	double r = r_result.value;

	return ParserResult(pow(l, r));
}

std::any ExpressionParser::visitCompExp(DiamondSheetsParser::CompExpContext* ctx)
{
	auto l_any = visit(ctx->expression(0));
	if (!l_any.has_value())
		return ParserResult(Cell::errorText);
	auto r_any = visit(ctx->expression(1));
	if (!r_any.has_value())
		return ParserResult(Cell::errorText);

	auto l_result = std::any_cast<ParserResult>(l_any);
	if (l_result.type == 0)
		return l_result;

	double l = l_result.value;

	auto r_result = std::any_cast<ParserResult>(r_any);
	if (r_result.type == 0)
		return r_result;

	double r = r_result.value;

	if (ctx->LCOMP() != nullptr)
	{
		return ParserResult(l < r, 2);
	}

	if (ctx->RCOMP() != nullptr)
	{
		return ParserResult(l > r, 2);
	}

	if (ctx->EQCOMP() != nullptr)
	{
		return ParserResult(l == r, 2);
	}

	if (ctx->NEQCOMP() != nullptr)
	{
		return ParserResult(l != r, 2);
	}

	if (ctx->LEQCOMP() != nullptr)
	{
		return ParserResult(l <= r, 2);
	}

	return ParserResult(l >= r, 2);
}

std::any ExpressionParser::visitCellIdAtomExp(DiamondSheetsParser::CellIdAtomExpContext* ctx)
{
	auto cellId = To10Base(ctx->getText());
	if (cellId[0] < 0 || cellId[0] >= _gridData->size() || cellId[1] < 0 || cellId[1] > _gridData->operator[](0).size())
	{
		return ParserResult(Cell::refErrorText);
	}

	QString value = _gridData->operator[](cellId[0])[cellId[1]]->getValue();

	// If we are not updating cell, than we need to add refs
	if (!isUpdate && !headCell->isReferenced(_gridData->operator[](cellId[0])[cellId[1]]))
	{
		_gridData->operator[](cellId[0])[cellId[1]]->addRef(headCell);
		headCell->addReferenced(_gridData->operator[](cellId[0])[cellId[1]]);
	}

	if (value == nullptr)
		return ParserResult(0);

	if (value == Cell::errorText)
		return ParserResult(Cell::errorText);

	if (value == Cell::refErrorText)
		return ParserResult(Cell::refErrorText);

	if (value == Cell::trueText)
		return ParserResult(1, 2);

	if (value == Cell::falseText)
		return ParserResult(0, 2);

	for (auto& c : value)
	{
		if (!c.isDigit()) return ParserResult(Cell::errorText); // TODO: minus
	}

	return ParserResult(std::stod(value.toStdString()));
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
