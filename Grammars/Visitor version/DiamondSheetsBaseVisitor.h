
// Generated from DiamondSheets.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "DiamondSheetsVisitor.h"


/**
 * This class provides an empty implementation of DiamondSheetsVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  DiamondSheetsBaseVisitor : public DiamondSheetsVisitor {
public:

  virtual std::any visitNumericAtomExp(DiamondSheetsParser::NumericAtomExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPowerExp(DiamondSheetsParser::PowerExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMulDivExp(DiamondSheetsParser::MulDivExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParenthesisExp(DiamondSheetsParser::ParenthesisExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdAtomExp(DiamondSheetsParser::IdAtomExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAddSubExp(DiamondSheetsParser::AddSubExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionExp(DiamondSheetsParser::FunctionExpContext *ctx) override {
    return visitChildren(ctx);
  }


};

