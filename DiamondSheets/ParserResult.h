#pragma once

#include <qstring.h>

struct ParserResult
{
	ParserResult(double value, int type = 1) : value(value), type(type) {}
	ParserResult(QString error) : error(error) { type = 0; }

	int type; // 0 - error, 1 - double, 2 - bool
	double value;
	QString error;
};