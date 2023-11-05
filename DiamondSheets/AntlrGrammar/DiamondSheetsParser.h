
// Generated from DiamondSheets.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  DiamondSheetsParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, MULTIPLY = 4, DIVIDE = 5, INTDIV = 6, 
    MOD = 7, PLUS = 8, MINUS = 9, LCOMP = 10, RCOMP = 11, EQCOMP = 12, NEQCOMP = 13, 
    LEQCOMP = 14, REQCOMP = 15, CELLID = 16, NAME = 17, NUMBER = 18, WS = 19
  };

  enum {
    RuleExpression = 0
  };

  explicit DiamondSheetsParser(antlr4::TokenStream *input);

  DiamondSheetsParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~DiamondSheetsParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class ExpressionContext; 

  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ExpressionContext() = default;
    void copyFrom(ExpressionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  NumericAtomExpContext : public ExpressionContext {
  public:
    NumericAtomExpContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *NUMBER();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PowerExpContext : public ExpressionContext {
  public:
    PowerExpContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  MulDivModExpContext : public ExpressionContext {
  public:
    MulDivModExpContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *MULTIPLY();
    antlr4::tree::TerminalNode *DIVIDE();
    antlr4::tree::TerminalNode *MOD();
    antlr4::tree::TerminalNode *INTDIV();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CellIdAtomExpContext : public ExpressionContext {
  public:
    CellIdAtomExpContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *CELLID();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CompExpContext : public ExpressionContext {
  public:
    CompExpContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *LCOMP();
    antlr4::tree::TerminalNode *RCOMP();
    antlr4::tree::TerminalNode *EQCOMP();
    antlr4::tree::TerminalNode *NEQCOMP();
    antlr4::tree::TerminalNode *LEQCOMP();
    antlr4::tree::TerminalNode *REQCOMP();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ParenthesisExpContext : public ExpressionContext {
  public:
    ParenthesisExpContext(ExpressionContext *ctx);

    ExpressionContext *expression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AddSubExpContext : public ExpressionContext {
  public:
    AddSubExpContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *MINUS();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ExpressionContext* expression();
  ExpressionContext* expression(int precedence);

  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool expressionSempred(ExpressionContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

