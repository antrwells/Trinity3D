#include "pch.h"
#include "Tokenizer.h"

CTokenizer::CTokenizer(CSource& source) : m_source(source)
{
}

void CTokenizer::skipWhitespaceAndComments()
{
    while (true) {
        // Skip whitespace
        m_source.skipWhitespace();

        // Check for comments
        if (m_source.peek() == '/' && (m_source.peek(1) == '/' || m_source.peek(1) == '*')) {
            skipComment();
        }
        else {
            break;
        }
    }
}

void CTokenizer::skipComment()
{
    char c = m_source.next();
    char c2 = m_source.next();
    if (c2 == '/') {
        // Single-line comment
        while (!m_source.isEOF() && m_source.peek() != '\n') {
            m_source.next();
        }
        m_source.next(); // consume the newline character
    }
    else if (c2 == '*') {
        // Multi-line comment
        while (true) {
            if (m_source.isEOF()) {
                throw std::runtime_error("Unterminated multi-line comment");
            }
            if (m_source.peek() == '*' && m_source.peek(1) == '/') {
                m_source.next(); // consume the asterisk
                m_source.next(); // consume the slash
                break;
            }
            m_source.next();
        }
    }
    else {
        throw std::runtime_error("Invalid character sequence");
    }
}

CToken CTokenizer::readIdentifierOrKeyword()
{
    std::string lexeme;
    std::size_t position = m_source.getCurrentPosition();
    auto lineAndColumn = m_source.getCurrentLineAndColumn();

    // Read the identifier or keyword
    while (true) {
        char c = m_source.peek();
        if (isalnum(c) || c == '_') {
            lexeme += m_source.next();
        }
        else {
            break;
        }
    }

    // Check if the lexeme is a keyword
    TokenType type;
    if (lexeme == "if") {
        type = TokenType::KW_IF;
    }
    else if (lexeme == "else") {
        type = TokenType::KW_ELSE;
    }
    else if (lexeme == "while") {
        type = TokenType::KW_WHILE;
    }
    else if (lexeme == "for") {
        type = TokenType::KW_FOR;
    }
    else if (lexeme == "do") {
        type = TokenType::KW_DO;
    }
    else if (lexeme == "switch") {
        type = TokenType::KW_SWITCH;
    }
    else if (lexeme == "case") {
        type = TokenType::KW_CASE;
    }
    else if (lexeme == "default") {
        type = TokenType::KW_DEFAULT;
    }
    else if (lexeme == "break") {
        type = TokenType::KW_BREAK;
    }
    else if (lexeme == "continue") {
        type = TokenType::KW_CONTINUE;
    }
    else if (lexeme == "return") {
        type = TokenType::KW_RETURN;
    }
    else {
        type = TokenType::IDENTIFIER;
    }

    return CToken(type, lexeme, position, lineAndColumn.first, lineAndColumn.second);
}
CToken CTokenizer::readNumber()
{
    std::string lexeme;
    std::size_t position = m_source.getCurrentPosition();
    auto lineAndColumn = m_source.getCurrentLineAndColumn();
    bool hasFractionalPart = false;
    bool hasExponentPart = false;

    // Read the integer part
    while (isdigit(m_source.peek())) {
        lexeme += m_source.next();
    }

    // Read the fractional part (if any)
    if (m_source.peek() == '.') {
        lexeme += m_source.next();
        hasFractionalPart = true;
        while (isdigit(m_source.peek())) {
            lexeme += m_source.next();
        }
    }

    // Read the exponent part (if any)
    if (m_source.peek() == 'e' || m_source.peek() == 'E') {
        lexeme += m_source.next();
        hasExponentPart = true;
        if (m_source.peek() == '+' || m_source.peek() == '-') {
            lexeme += m_source.next();
        }
        while (isdigit(m_source.peek())) {
            lexeme += m_source.next();
        }
    }

    TokenType type = hasFractionalPart || hasExponentPart ? TokenType::LIT_FLOAT : TokenType::LIT_INTEGER;

    return CToken(type, lexeme, position, lineAndColumn.first, lineAndColumn.second);
}

CToken CTokenizer::readStringOrCharLiteral()
{
    std::string lexeme;
    std::size_t position = m_source.getCurrentPosition();
    auto lineAndColumn = m_source.getCurrentLineAndColumn();
    char delimiter = m_source.next(); // consume the opening delimiter

    // Read the literal value
    while (m_source.peek() != delimiter) {
        char c = m_source.next();
        if (c == '\\') {
            lexeme += m_source.next(); // consume the escaped character
        }
        else {
            lexeme += c;
        }
    }

    m_source.next(); // consume the closing delimiter

    TokenType type = delimiter == '\'' ? TokenType::LIT_CHAR : TokenType::LIT_STRING;
    return CToken(type, lexeme, position, lineAndColumn.first, lineAndColumn.second);
}

CToken CTokenizer::readPunctuationOrOperator()
{
    std::string lexeme;
    std::size_t position = m_source.getCurrentPosition();
    auto lineAndColumn = m_source.getCurrentLineAndColumn();

    switch (m_source.next()) {
    case '=':
        if (m_source.peek() == '=') {
            m_source.next();
            lexeme = "==";
        }
        else {
            lexeme = "=";
        }
        break;
    case '+':
        if (m_source.peek() == '+') {
            m_source.next();
            lexeme = "++";
        }
        else {
            lexeme = "+";
        }
        break;
    case '-':
        if (m_source.peek() == '-') {
            m_source.next();
            lexeme = "--";
        }
        else {
            lexeme = "-";
        }
        break;
    case '*':
        lexeme = "*";
        break;
    case '/':
        if (m_source.peek() == '/') {
            m_source.skipComment();
            return nextToken();
        }
        else if (m_source.peek() == '*') {
            m_source.skipComment();
            return nextToken();
        }
        else {
            lexeme = "/";
        }
        break;
    case '%':
        lexeme = "%";
        break;
    case '&':
        if (m_source.peek() == '&') {
            m_source.next();
            lexeme = "&&";
        }
        else {
            lexeme = "&";
        }
        break;
    case '|':
        if (m_source.peek() == '|') {
            m_source.next();
            lexeme = "||";
        }
        else {
            lexeme = "|";
        }
        break;
    case '^':
        lexeme = "^";
        break;
    case '~':
        lexeme = "~";
        break;
    case '!':
        if (m_source.peek() == '=') {
            m_source.next();
            lexeme = "!=";
        }
        else {
            lexeme = "!";
        }
        break;
    case '<':
        if (m_source.peek() == '<') {
            m_source.next();
            if (m_source.peek() == '=') {
                m_source.next();
                lexeme = "<<=";
            }
            else {
                lexeme = "<<";
            }
        }
        else if (m_source.peek() == '=') {
            m_source.next();
            lexeme = "<=";
        }
        else {
            lexeme = "<";
        }
        break;
    case '>':
        if (m_source.peek() == '>') {
            m_source.next();
            if (m_source.peek() == '=') {
                m_source.next();
                lexeme = ">>=";
            }
            else {
                lexeme = ">>";
            }
        }
        else if (m_source.peek() == '=') {
            m_source.next();
            lexeme = ">=";
        }
        else {
            lexeme = ">";
        }
        break;
    case '(':
        lexeme = "(";
        break;
    case ')':
        lexeme = ")";
        break;
    case '{':
        lexeme = "{";
        break;
    case '}':
        lexeme = "}";
        break;
    case '[':
        lexeme = "[";
        break;
    case ']':
        lexeme = "]";
        break;
    case ';':
        lexeme = ";";
        break;
    case ',':
        lexeme = ",";
        break;
    default:
        throw std::runtime_error("Invalid punctuation or operator");
    }
    return CToken(getTokenTypeForPunctuationOrOperator(lexeme), lexeme, position, lineAndColumn.first, lineAndColumn.second);
}

TokenType CTokenizer::getTokenTypeForPunctuationOrOperator(const std::string& lexeme)
{
    if (lexeme == "=") {
        return TokenType::OP_ASSIGN;
    }
    else if (lexeme == "+") {
        return TokenType::OP_ADD;
    }
    else if (lexeme == "-") {
        return TokenType::OP_SUB;
    }
    else if (lexeme == "*") {
        return TokenType::OP_MUL;
    }
    else if (lexeme == "/") {
        return TokenType::OP_DIV;
    }
    else if (lexeme == "%") {
        return TokenType::OP_MOD;
    }
    else if (lexeme == "++") {
        return TokenType::OP_INC;
    }
    else if (lexeme == "--") {
        return TokenType::OP_DEC;
    }
    else if (lexeme == "&") {
        return TokenType::OP_BIT_AND;
    }
    else if (lexeme == "|") {
        return TokenType::OP_BIT_OR;
    }
    else if (lexeme == "^") {
        return TokenType::OP_BIT_XOR;
    }
    else if (lexeme == "~") {
        return TokenType::OP_BIT_NOT;
    }
    else if (lexeme == "&&") {
        return TokenType::OP_AND;
    }
    else if (lexeme == "||") {
        return TokenType::OP_OR;
    }
    else if (lexeme == "!") {
        return TokenType::OP_NOT;
    }
    else if (lexeme == "==") {
        return TokenType::OP_EQ;
    }
    else if (lexeme == "!=") {
        return TokenType::OP_NE;
    }
    else if (lexeme == "<") {
        return TokenType::OP_LT;
    }
    else if (lexeme == ">") {
        return TokenType::OP_GT;
    }
    else if (lexeme == "<=") {
        return TokenType::OP_LE;
    }
    else if (lexeme == ">=") {
        return TokenType::OP_GE;
    }
    else if (lexeme == "(") {
        return TokenType::PUNC_LPAREN;
    }
    else if (lexeme == ")") {
        return TokenType::PUNC_RPAREN;
    }
    else if (lexeme == "{") {
        return TokenType::PUNC_LBRACE;
    }
    else if (lexeme == "}") {
        return TokenType::PUNC_RBRACE;
    }
    else if (lexeme == "[") {
        return TokenType::PUNC_LBRACKET;
    }
    else if (lexeme == "]") {
        return TokenType::PUNC_RBRACKET;
    }
    else if (lexeme == ";") {
        return TokenType::PUNC_SEMICOLON;
    }
    else if (lexeme == ",") {
        return TokenType::PUNC_COMMA;
    }
    else {
        throw std::runtime_error("Invalid punctuation or operator");
    }
}

/*
CToken CTokenizer::nextToken()
{
    // Skip whitespace and comments
    skipWhitespaceAndComments();

    // Check if we've reached the end of the source
    if (m_source.isEOF()) {
        return CToken(TokenType::END_OF_FILE, "", m_source.getCurrentPosition(), 0, 0);
    }

    // Check if the next token is a keyword or identifier
    if (std::isalpha(m_source.peek()) || m_source.peek() == '_') {
        return readIdentifierOrKeyword();
    }

    // Check if the next token is a number
    if (std::isdigit(m_source.peek())) {
        return readNumber();
    }

    // Check if the next token is a string or character literal
    if (m_source.peek() == '"' || m_source.peek() == '\'') {
        return readStringOrCharLiteral();
    }

    // Check if the next token is a punctuation or operator symbol
    std::string lexeme;
    lexeme += m_source.next();
    if (isPunctuationOrOperator(lexeme)) {
        return readPunctuationOrOperator(lexeme);
    }
    // If the next character is not a valid token, throw an exception
    throw std::runtime_error("Invalid token");
}
*/

bool CTokenizer::isPunctuationOrOperator(const std::string& lexeme) const
{
    return lexeme == "=" ||
        lexeme == "+" ||
        lexeme == "-" ||
        lexeme == "*" ||
        lexeme == "/" ||
        lexeme == "%" ||
        lexeme == "++" ||
        lexeme == "--" ||
        lexeme == "&" ||
        lexeme == "|" ||
        lexeme == "^" ||
        lexeme == "~" ||
        lexeme == "&&" ||
        lexeme == "||" ||
        lexeme == "!" ||
        lexeme == "==" ||
        lexeme == "!=" ||
        lexeme == "<" ||
        lexeme == ">" ||
        lexeme == "<=" ||
        lexeme == ">=" ||
        lexeme == "(" ||
        lexeme == ")" ||
        lexeme == "{" ||
        lexeme == "}" ||
        lexeme == "[" ||
        lexeme == "]" ||
        lexeme == ";" ||
        lexeme == ",";
}

CToken CTokenizer::readPunctuationOrOperator(const std::string& firstChar)
{
    std::string lexeme = firstChar;

    // Check if the next character is a valid punctuation or operator
    if (!isPunctuationOrOperator(lexeme)) {
        throw std::runtime_error("Invalid token");
    }

    // Return the corresponding token
    TokenType type = getTokenTypeForPunctuationOrOperator(lexeme);
    std::size_t position = m_source.getCurrentPosition() - lexeme.length();
    auto lineAndColumn = m_source.getCurrentLineAndColumn();
    return CToken(type, lexeme, position, lineAndColumn.first, lineAndColumn.second);
}

CToken CTokenizer::nextToken()
{
    // Skip whitespace and comments
    skipWhitespaceAndComments();

    // Check for end of file
    if (m_source.isEOF()) {
        return CToken(TokenType::END_OF_FILE, "", m_source.getCurrentPosition(),
            m_source.getCurrentLineAndColumn().first, m_source.getCurrentLineAndColumn().second);
    }

    // Check for a keyword, identifier, or keyword-like identifier
    if (isalpha(m_source.peek()) || m_source.peek() == '_') {
        return readIdentifierOrKeyword();
    }

    // Check for a number literal
    if (isdigit(m_source.peek()) || (m_source.peek() == '.' && isdigit(m_source.peek(1)))) {
        return readNumber();
    }

    // Check for a string or character literal
    if (m_source.peek() == '\'' || m_source.peek() == '\"') {
        return readStringOrCharLiteral();
    }

    // Check for a punctuation or operator symbol
    std::string firstChar;
    firstChar += m_source.next();
    if (isPunctuationOrOperator(firstChar)) {
        return readPunctuationOrOperator(firstChar);
    }
    else {
        return readPunctuationOrOperator();
    }
}


CToken CTokenizer::peekNextToken(int os) {

    for (int i = 0; i < os; i++) {

    }
    return CToken();

}

CToken CTokenizer::getNextToken()
{
    CToken token;
   // do {
        token = nextToken();
   // } while (token.getType() == TokenType::WHITESPACE || token.getType() == TokenType::UNKNOWN);

    return token;
}

std::string toString(const CToken& token)
{
    std::string typeString;
    switch (token.getType()) {
    case TokenType::KW_IF:
        typeString = "IF";
        break;
    case TokenType::KW_ELSE:
        typeString = "ELSE";
        break;
    case TokenType::KW_WHILE:
        typeString = "WHILE";
        break;
    case TokenType::KW_FOR:
        typeString = "FOR";
        break;
    case TokenType::KW_DO:
        typeString = "DO";
        break;
    case TokenType::KW_SWITCH:
        typeString = "SWITCH";
        break;
    case TokenType::KW_CASE:
        typeString = "CASE";
        break;
    case TokenType::KW_DEFAULT:
        typeString = "DEFAULT";
        break;
    case TokenType::KW_BREAK:
        typeString = "BREAK";
        break;
    case TokenType::KW_CONTINUE:
        typeString = "CONTINUE";
        break;
    case TokenType::KW_RETURN:
        typeString = "RETURN";
        break;
    case TokenType::OP_ASSIGN:
        typeString = "ASSIGN";
        break;
    case TokenType::OP_ADD:
        typeString = "ADD";
        break;
    case TokenType::OP_SUB:
        typeString = "SUB";
        break;
    case TokenType::OP_MUL:
        typeString = "MUL";
        break;
    case TokenType::OP_DIV:
        typeString = "DIV";
        break;
    case TokenType::OP_MOD:
        typeString = "MOD";
        break;
    case TokenType::OP_INC:
        typeString = "INC";
        break;
    case TokenType::OP_DEC:
        typeString = "DEC";
        break;
    case TokenType::OP_BIT_AND:
        typeString = "BIT_AND";
        break;
    case TokenType::OP_BIT_OR:
        typeString = "BIT_OR";
        break;
    case TokenType::OP_BIT_XOR:
        typeString = "BIT_XOR";
        break;
    case TokenType::OP_BIT_NOT:
        typeString = "BIT_NOT";
        break;
    case TokenType::OP_AND:
        typeString = "AND";
        break;
    case TokenType::OP_OR:
        typeString = "OR";
        break;
    case TokenType::OP_NOT:
        typeString = "NOT";
        break;
    case TokenType::OP_EQ:
        typeString = "EQ";
        break;
    case TokenType::OP_NE:
        typeString = "NE";
        break;
    case TokenType::OP_LT:
        typeString = "LT";
        break;
    case TokenType::OP_GT:
        typeString = "GT";
        break;
    case TokenType::OP_LE:
        typeString = "LE";
        break;
    case TokenType::OP_GE:
        typeString = "GE";
        break;
    case TokenType::PUNC_LPAREN:
        typeString = "LPAREN";
        break;
    case TokenType::PUNC_RPAREN:
        typeString = "RPAREN";
        break;
    case TokenType::PUNC_LBRACE:
        typeString = "LBRACE";
        break;
    case TokenType::PUNC_RBRACE:
        typeString = "RBRACE";
        break;
    case TokenType::PUNC_LBRACKET:
        typeString = "LBRACKET";
        break;
    case TokenType::PUNC_RBRACKET:
        typeString = "RBRACKET";
        break;
    case TokenType::PUNC_SEMICOLON:
        typeString = "SEMICOLON";
        break;
       case TokenType::PUNC_COMMA:
            typeString = "COMMA";
            break;
        case TokenType::LIT_INTEGER:
            typeString = "INTEGER";
            break;
        case TokenType::LIT_FLOAT:
            typeString = "FLOAT";
            break;
        case TokenType::LIT_CHAR:
            typeString = "CHAR";
            break;
        case TokenType::LIT_STRING:
            typeString = "STRING";
            break;
        case TokenType::IDENTIFIER:
            typeString = "IDENTIFIER";
            break;
        case TokenType::END_OF_FILE:
            typeString = "END_OF_FILE";
            break;
        default:
            typeString = "INVALID";
            break;
    }

    std::stringstream ss;

    return typeString + "||" + token.getLexeme();
    ss << "Token[type=" << typeString << ", value='" << token.getLexeme() << "', position=" << token.getPosition() << ", line=" << token.getLine() << ", column=" << token.getColumn() << "]";
    return ss.str();
}