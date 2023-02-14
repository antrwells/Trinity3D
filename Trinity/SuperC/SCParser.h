#pragma once
#include "Tokenizer.h"
#include <memory>
#include "AST.h"
#include <vector>


enum class LineType {
    ClassDef,
    FunctionDef,
    Statement
};

class SCParser {
public:
    SCParser(std::vector<CToken> token)
    {
        tokens = token;
    }
     ASTModule* Parse();

     LineType decideLineType();

     CToken getCurrentToken()
     {
         return tokens[m_TokenIndex];
     }

private:
//    CTokenizer* m_Toker;
    std::vector<CToken> tokens;
    int m_TokenIndex = 0;
};
