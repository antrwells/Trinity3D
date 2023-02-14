// SuperCTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CSource.h"
#include "SCParser.h"
#include <vector>
#include "Tokenizer.h"

void printTokens(const std::vector<CToken>& tokens)
{
    for (const auto& token : tokens) {
        std::cout << "[" << toString(token) << "]" << std::endl;
    }
}

void testTokenization(const std::string& filename)
{
    // Load the source code from the file
    CSource source(filename);

    // Create a tokenizer object
    CTokenizer *tokenizer = new CTokenizer(source);
    auto str = tokenizer->getTokens();


    // Tokenize the source code
    int ii = 0;
    std::vector<CToken> tokens;
    while (true) {
        CToken token = str[ii];//  tokenizer.getNextToken();
        if (token.getType() == TokenType::END_OF_FILE) {
            break;
        }
        ii++;

        //tokens.push_back(token);
    }
    printf("-----------\n");
    printTokens(str);
//    SCParser parser()
 //   SCParser* parser = new SCParser(toker);
//    auto module = parser.Parse();




}
int main()
{
    std::cout << "Hello World!\n";
    
    CSource src("test/test.sc");
    testTokenization(src.getSource());


    //CTokenizer toker(source);


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
