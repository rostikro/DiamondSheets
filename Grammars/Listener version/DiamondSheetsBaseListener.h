
// Generated from DiamondSheets.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "DiamondSheetsListener.h"


/**
 * This class provides an empty implementation of DiamondSheetsListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  DiamondSheetsBaseListener : public DiamondSheetsListener {
public:

  virtual void enterNumericAtomExp(DiamondSheetsParser::NumericAtomExpContext * /*ctx*/) override { }
  virtual void exitNumericAtomExp(DiamondSheetsParser::NumericAtomExpContext * /*ctx*/) override { }

  virtual void enterPowerExp(DiamondSheetsParser::PowerExpContext * /*ctx*/) override { }
  virtual void exitPowerExp(DiamondSheetsParser::PowerExpContext * /*ctx*/) override { }

  virtual void enterMulDivExp(DiamondSheetsParser::MulDivExpContext * /*ctx*/) override { }
  virtual void exitMulDivExp(DiamondSheetsParser::MulDivExpContext * /*ctx*/) override { }

  virtual void enterParenthesisExp(DiamondSheetsParser::ParenthesisExpContext * /*ctx*/) override { }
  virtual void exitParenthesisExp(DiamondSheetsParser::ParenthesisExpContext * /*ctx*/) override { }

  virtual void enterIdAtomExp(DiamondSheetsParser::IdAtomExpContext * /*ctx*/) override { }
  virtual void exitIdAtomExp(DiamondSheetsParser::IdAtomExpContext * /*ctx*/) override { }

  virtual void enterAddSubExp(DiamondSheetsParser::AddSubExpContext * /*ctx*/) override { }
  virtual void exitAddSubExp(DiamondSheetsParser::AddSubExpContext * /*ctx*/) override { }

  virtual void enterFunctionExp(DiamondSheetsParser::FunctionExpContext * /*ctx*/) override { }
  virtual void exitFunctionExp(DiamondSheetsParser::FunctionExpContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

