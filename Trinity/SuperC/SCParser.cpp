#include "pch.h"
#include "SCParser.h"



ASTModule* SCParser::Parse() {

	ASTModule* mod = new ASTModule("SC Module");

    while (getCurrentToken().getType() != TokenType::END_OF_FILE) {
        //auto statement = parseStatement();
        auto lineType = decideLineType();
        
       // mod->AddNode(statement);

    }
    return mod;


}

LineType SCParser::decideLineType() {

   //auto tok = 

    return LineType::Statement;
}