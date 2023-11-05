
// Generated from DiamondSheets.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "DiamondSheetsParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by DiamondSheetsParser.
 */
class  DiamondSheetsListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterNumericAtomExp(DiamondSheetsParser::NumericAtomExpContext *ctx) = 0;
  virtual void exitNumericAtomExp(DiamondSheetsParser::NumericAtomExpContext *ctx) = 0;

  virtual void enterPowerExp(DiamondSheetsParser::PowerExpContext *ctx) = 0;
  virtual void exitPowerExp(DiamondSheetsParser::PowerExpContext *ctx) = 0;

  virtual void enterMulDivExp(DiamondSheetsParser::MulDivExpContext *ctx) = 0;
  virtual void exitMulDivExp(DiamondSheetsParser::MulDivExpContext *ctx) = 0;

  virtual void enterParenthesisExp(DiamondSheetsParser::ParenthesisExpContext *ctx) = 0;
  virtual void exitParenthesisExp(DiamondSheetsParser::ParenthesisExpContext *ctx) = 0;

  virtual void enterIdAtomExp(DiamondSheetsParser::IdAtomExpContext *ctx) = 0;
  virtual void exitIdAtomExp(DiamondSheetsParser::IdAtomExpContext *ctx) = 0;

  virtual void enterAddSubExp(DiamondSheetsParser::AddSubExpContext *ctx) = 0;
  virtual void exitAddSubExp(DiamondSheetsParser::AddSubExpContext *ctx) = 0;

  virtual void enterFunctionExp(DiamondSheetsParser::FunctionExpContext *ctx) = 0;
  virtual void exitFunctionExp(DiamondSheetsParser::FunctionExpContext *ctx) = 0;


};

