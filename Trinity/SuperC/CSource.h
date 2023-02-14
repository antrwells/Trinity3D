#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
class CSource
{
public:
    CSource(const std::string& sourceCode);
    CSource(const char* filePath);
    std::string getSource() {
        return m_sourceCode;
    }
    char peek(std::size_t offset = 0) const;
    char next();
    void reset();
    void skipComment();
    std::size_t getCurrentPosition() const;
    std::size_t getSourceLength() const;
    std::string getSubstring(std::size_t start, std::size_t length) const;
    void skipWhitespace();
    std::string readToken();
    bool isEOF() const;
    std::pair<std::size_t, std::size_t> getCurrentLineAndColumn() const;
    std::size_t getCurrentLine() const;
    std::size_t getCurrentColumn() const;
    std::string readCharacters(std::size_t count);
private:
    std::string m_sourceCode;
    std::size_t m_position;
};

