
// Generated from DiamondSheets.g4 by ANTLR 4.13.1


#include "DiamondSheetsLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct DiamondSheetsLexerStaticData final {
  DiamondSheetsLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  DiamondSheetsLexerStaticData(const DiamondSheetsLexerStaticData&) = delete;
  DiamondSheetsLexerStaticData(DiamondSheetsLexerStaticData&&) = delete;
  DiamondSheetsLexerStaticData& operator=(const DiamondSheetsLexerStaticData&) = delete;
  DiamondSheetsLexerStaticData& operator=(DiamondSheetsLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag diamondsheetslexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
DiamondSheetsLexerStaticData *diamondsheetslexerLexerStaticData = nullptr;

void diamondsheetslexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (diamondsheetslexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(diamondsheetslexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<DiamondSheetsLexerStaticData>(
    std::vector<std::string>{
      "T__0", "T__1", "T__2", "LETTER", "DIGIT", "MULTIPLY", "DIVIDE", "PLUS", 
      "MINUS", "CELLID", "NAME", "NUMBER", "WS"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "'('", "')'", "'^'", "'*'", "'/'", "'+'", "'-'", "", "", "", "' '"
    },
    std::vector<std::string>{
      "", "", "", "", "MULTIPLY", "DIVIDE", "PLUS", "MINUS", "CELLID", "NAME", 
      "NUMBER", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,11,77,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,1,0,1,0,1,1,1,
  	1,1,2,1,2,1,3,1,3,1,4,1,4,1,5,1,5,1,6,1,6,1,7,1,7,1,8,1,8,1,9,4,9,47,
  	8,9,11,9,12,9,48,1,9,4,9,52,8,9,11,9,12,9,53,1,10,4,10,57,8,10,11,10,
  	12,10,58,1,11,4,11,62,8,11,11,11,12,11,63,1,11,1,11,4,11,68,8,11,11,11,
  	12,11,69,3,11,72,8,11,1,12,1,12,1,12,1,12,0,0,13,1,1,3,2,5,3,7,0,9,0,
  	11,4,13,5,15,6,17,7,19,8,21,9,23,10,25,11,1,0,2,2,0,65,90,97,122,1,0,
  	48,57,80,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,11,1,0,0,0,0,13,1,0,0,
  	0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,21,1,0,0,0,0,23,1,0,0,0,0,
  	25,1,0,0,0,1,27,1,0,0,0,3,29,1,0,0,0,5,31,1,0,0,0,7,33,1,0,0,0,9,35,1,
  	0,0,0,11,37,1,0,0,0,13,39,1,0,0,0,15,41,1,0,0,0,17,43,1,0,0,0,19,46,1,
  	0,0,0,21,56,1,0,0,0,23,61,1,0,0,0,25,73,1,0,0,0,27,28,5,40,0,0,28,2,1,
  	0,0,0,29,30,5,41,0,0,30,4,1,0,0,0,31,32,5,94,0,0,32,6,1,0,0,0,33,34,7,
  	0,0,0,34,8,1,0,0,0,35,36,7,1,0,0,36,10,1,0,0,0,37,38,5,42,0,0,38,12,1,
  	0,0,0,39,40,5,47,0,0,40,14,1,0,0,0,41,42,5,43,0,0,42,16,1,0,0,0,43,44,
  	5,45,0,0,44,18,1,0,0,0,45,47,3,7,3,0,46,45,1,0,0,0,47,48,1,0,0,0,48,46,
  	1,0,0,0,48,49,1,0,0,0,49,51,1,0,0,0,50,52,3,9,4,0,51,50,1,0,0,0,52,53,
  	1,0,0,0,53,51,1,0,0,0,53,54,1,0,0,0,54,20,1,0,0,0,55,57,3,7,3,0,56,55,
  	1,0,0,0,57,58,1,0,0,0,58,56,1,0,0,0,58,59,1,0,0,0,59,22,1,0,0,0,60,62,
  	3,9,4,0,61,60,1,0,0,0,62,63,1,0,0,0,63,61,1,0,0,0,63,64,1,0,0,0,64,71,
  	1,0,0,0,65,67,5,46,0,0,66,68,3,9,4,0,67,66,1,0,0,0,68,69,1,0,0,0,69,67,
  	1,0,0,0,69,70,1,0,0,0,70,72,1,0,0,0,71,65,1,0,0,0,71,72,1,0,0,0,72,24,
  	1,0,0,0,73,74,5,32,0,0,74,75,1,0,0,0,75,76,6,12,0,0,76,26,1,0,0,0,7,0,
  	48,53,58,63,69,71,1,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  diamondsheetslexerLexerStaticData = staticData.release();
}

}

DiamondSheetsLexer::DiamondSheetsLexer(CharStream *input) : Lexer(input) {
  DiamondSheetsLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *diamondsheetslexerLexerStaticData->atn, diamondsheetslexerLexerStaticData->decisionToDFA, diamondsheetslexerLexerStaticData->sharedContextCache);
}

DiamondSheetsLexer::~DiamondSheetsLexer() {
  delete _interpreter;
}

std::string DiamondSheetsLexer::getGrammarFileName() const {
  return "DiamondSheets.g4";
}

const std::vector<std::string>& DiamondSheetsLexer::getRuleNames() const {
  return diamondsheetslexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& DiamondSheetsLexer::getChannelNames() const {
  return diamondsheetslexerLexerStaticData->channelNames;
}

const std::vector<std::string>& DiamondSheetsLexer::getModeNames() const {
  return diamondsheetslexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& DiamondSheetsLexer::getVocabulary() const {
  return diamondsheetslexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView DiamondSheetsLexer::getSerializedATN() const {
  return diamondsheetslexerLexerStaticData->serializedATN;
}

const atn::ATN& DiamondSheetsLexer::getATN() const {
  return *diamondsheetslexerLexerStaticData->atn;
}




void DiamondSheetsLexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  diamondsheetslexerLexerInitialize();
#else
  ::antlr4::internal::call_once(diamondsheetslexerLexerOnceFlag, diamondsheetslexerLexerInitialize);
#endif
}
