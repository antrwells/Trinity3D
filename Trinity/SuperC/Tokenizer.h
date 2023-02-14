#pragma once
#include <string>
#include "CSource.h"
#include <vector>

    enum class TokenType {
        // keywords
        KW_IF,
        KW_ELSE,
        KW_WHILE,
        KW_FOR,
        KW_DO,
        KW_SWITCH,
        KW_CASE,
        KW_DEFAULT,
        KW_BREAK,
        KW_CONTINUE,
        KW_RETURN,

        // operators
        OP_ASSIGN,
        OP_ADD,
        OP_SUB,
        OP_MUL,
        OP_DIV,
        OP_MOD,
        OP_INC,
        OP_DEC,
        OP_BIT_AND,
        OP_BIT_OR,
        OP_BIT_XOR,
        OP_BIT_NOT,
        OP_AND,
        OP_OR,
        OP_NOT,
        OP_EQ,
        OP_NE,
        OP_LT,
        OP_GT,
        OP_LE,
        OP_GE,

        // punctuation
        PUNC_LPAREN,
        PUNC_RPAREN,
        PUNC_LBRACE,
        PUNC_RBRACE,
        PUNC_LBRACKET,
        PUNC_RBRACKET,
        PUNC_SEMICOLON,
        PUNC_COMMA,

        // literals
        LIT_INTEGER,
        LIT_FLOAT,
        LIT_CHAR,
        LIT_STRING,

        // identifiers
        IDENTIFIER,

        // end of file
        END_OF_FILE
    };


   
class CToken {
public:
    CToken() {};
    CToken(TokenType type, const std::string& lexeme, std::size_t position, std::size_t line, std::size_t column)
        : m_type(type), m_lexeme(lexeme), m_position(position), m_line(line), m_column(column)
    {
    }

    TokenType getType() const { return m_type; }
    std::string getLexeme() const { return m_lexeme; }
    std::size_t getPosition() const { return m_position; }
    std::size_t getLine() const { return m_line; }
    std::size_t getColumn() const { return m_column; }

private:
    TokenType m_type;
    std::string m_lexeme;
    std::size_t m_position;
    std::size_t m_line;
    std::size_t m_column;
};




class CTokenizer {
public:
    CTokenizer(CSource& source);

    CToken getNextToken();
    CToken peekNextToken(int os = 0);
    std::vector<CToken> getTokens() {

        std::vector<CToken> toks;
        while (!m_source.isEOF()) {
            toks.push_back(getNextToken());
        }
        return toks;

    }
   
private:
    CSource& m_source;

    TokenType getTokenTypeForPunctuationOrOperator(const std::string& lexeme);

    void skipWhitespaceAndComments();

    void skipComment();

    CToken nextToken();

    bool isPunctuationOrOperator(const std::string& lexeme) const;

    CToken readPunctuationOrOperator(const std::string& firstChar);
    

    CToken readIdentifierOrKeyword();

    CToken readNumber();

    CToken readStringOrCharLiteral();

    CToken readPunctuationOrOperator();
};

std::string toString(const CToken& token);

