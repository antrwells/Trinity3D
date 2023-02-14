#include "pch.h"
#include "CSource.h"
CSource::CSource(const std::string& sourceCode)
    : m_sourceCode(sourceCode), m_position(0)
{
}

CSource::CSource(const char* filePath)
    : m_position(0)
{
    std::ifstream fileStream(filePath);
    if (!fileStream.is_open()) {
        throw std::runtime_error("Failed to open file");
    }
    std::stringstream buffer;
    buffer << fileStream.rdbuf();
    m_sourceCode = buffer.str();
}

char CSource::peek(std::size_t offset) const
{
    if (m_position + offset >= m_sourceCode.length()) {
        return '\0';
    }
    return m_sourceCode[m_position + offset];
}
char CSource::next()
{
    if (m_position >= m_sourceCode.size()) {
        return '\0';
    }
    return m_sourceCode[m_position++];
}

void CSource::reset()
{
    m_position = 0;
}

std::size_t CSource::getCurrentPosition() const
{
    return m_position;
}

std::size_t CSource::getSourceLength() const
{
    return m_sourceCode.size();
}

std::string CSource::getSubstring(std::size_t start, std::size_t length) const
{
    return m_sourceCode.substr(start, length);
}

void CSource::skipWhitespace()
{
    while (m_position < m_sourceCode.size()) {
        char c = m_sourceCode[m_position];
        if (c != ' ' && c != '\t' && c != '\n' && c != '\r') {
            break;
        }
        ++m_position;
    }
}

std::string CSource::readToken()
{
    std::string token;
    skipWhitespace();
    while (m_position < m_sourceCode.size()) {
        char c = m_sourceCode[m_position];
        if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
            break;
        }
        token += c;
        ++m_position;
    }
    return token;
}

std::size_t CSource::getCurrentLine() const
{
    return getCurrentLineAndColumn().first;
}

std::size_t CSource::getCurrentColumn() const
{
    return getCurrentLineAndColumn().second;
}

std::string CSource::readCharacters(std::size_t count)
{
    std::string characters;
    for (std::size_t i = 0; i < count; ++i) {
        char c = peek();
        if (c == '\0') {
            break;
        }
        characters += next();
    }
    return characters;
}

bool CSource::isEOF() const
{
    return m_position >= m_sourceCode.size();
}
std::pair<std::size_t, std::size_t> CSource::getCurrentLineAndColumn() const
{
    std::size_t line = 1;
    std::size_t column = 1;
    for (std::size_t i = 0; i < m_position; ++i) {
        if (m_sourceCode[i] == '\n') {
            ++line;
            column = 1;
        }
        else {
            ++column;
        }
    }
    return std::make_pair(line, column);
}


void CSource::skipComment()
{
    char c = next();
    char nextChar = peek();
    if (c == '/' && nextChar == '/') { // Single-line comment
        while (next() != '\n' && !isEOF()) {
            // Do nothing
        }
    }
    else if (c == '/' && nextChar == '*') { // Multi-line comment
        next(); // consume the '*'
        while (true) {
            c = next();
            nextChar = peek();
            if (c == '*' && nextChar == '/') {
                next(); // consume the '/'
                break;
            }
            if (isEOF()) {
                throw std::runtime_error("Unterminated comment");
            }
        }
    }
    else {
        throw std::runtime_error("Invalid comment");
    }
}