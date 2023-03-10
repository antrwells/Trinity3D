#include "ZParseCodeBody.h"
#include "ZParseStatement.h"
#include "ZParseVars.h"
#include "ZVarsNode.h"
#include "ZStatementNode.h"
#include "ZCodeBodyNode.h"
#include "ZParseClassStatement.h"
#include "ZClassStatementNode.h"
#include "ZParseAssign.h"
#include "ZParseIf.h"
#include "ZIfnode.h"
#include "ZParseFor.h"
#include "ZForNode.h"
#include "ZParseReturn.h"
#include "ZReturnNode.h"
#include "ZParseWhile.h"
#include "ZWhileNode.h"
#include "ZIncNode.h"
#include "ZScriptContext.h"
#include "ZMethodNode.h"
#include "ZParseForEach.h"
#include "ZForEachNode.h";
#include "ParseListAdd.h"
#include "ZParseStartTransient.h"
#include "ZStartTransientNode.h"
ZParseCodeBody::ZParseCodeBody(ZTokenStream* stream) : ZParseNode(stream) {



}
CodeType ZParseCodeBody::PredictType() {

	int peek_val = 0;
	bool decvar = false;

	int idnum = 0;
	while (!mStream->EOS())
	{

		auto token = mStream->PeekToken(peek_val);

		switch (token.mType) {
		case TokenType::TokenStartTransient:
			return CodeType::CodeStartTransient;
			break;
		case TokenType::TokenLeftArray:
			return CodeType::CodeAssign;
		case TokenType::TokenReturn:
			return CodeType::CodeReturn;
		case TokenType::TokenIf:
			return CodeType::CodeIf;
		case TokenType::TokenElseIf:
			return CodeType::CodeElseIf;
		case TokenType::TokenElse:
			return CodeType::CodeElse;
		case TokenType::TokenFor:
			return CodeType::CodeFor;
		case TokenType::TokenWhile:
			return CodeType::CodeWhile;
		case TokenType::TokenDebugStop:
			return CodeType::CodeDebug;
		case TokenType::TokenIdent:

			if (mStream->PeekToken(peek_val + 1).mType == TokenType::TokenPeriod)
			{

				auto quick = mStream->PeekToken(peek_val + 3);
				
				if (quick.mType == TokenType::TokenLeftPara)
				{
					return CodeType::ClassStatement;
				}
				else {
					if (quick.mType == TokenType::TokenEquals)
					{
						return CodeType::CodeAssign;
					}
				}
				
				//if(mStream->PeekToken(peek_val+3).)


			}

			if (mStream->PeekToken(peek_val+1).mType == TokenType::TokenLeftPara) {
				return CodeType::CodeStatement;
			}

			if (mStream->PeekToken(peek_val + 1).mType == TokenType::TokenEquals) {
				return CodeType::CodeAssign;
			}

			if (mStream->PeekToken(peek_val + 1).mType == TokenType::TokenIdent) {

				return CodeType::CodeDeclareVars;

			}

			break;
		case TokenType::TokenInt:
		case TokenType::TokenFloat:
		case TokenType::TokenString:
		case TokenType::TokenCObj:
		case TokenType::TokenVar:
		case TokenType::TokenBool:
		case TokenType::TokenList:
		case TokenType::TokenMem:
			return CodeType::CodeDeclareVars;
			break;
		case TokenType::TokenListAdd:
			return CodeType::CodeListAdd;
			break;
		case TokenType::TokenListRemove:
			return CodeType::CodeListRemove;
			break;
		case TokenType::TokenForEach:
			return CodeType::CodeForEach;
			break;
		case TokenType::TokenEndOfLine:
		
		
		{int a = 5;

		}break;
		case TokenType::TokenEnd:
			return CodeType::CodeEnd;
		default:
			int bb = 5;
			break;
		}
		peek_val++;

	}

	return CodeType::CodeUnknown;


}

/*
CodeType ZParseCodeBody::PredictType() {

	//auto token = mStream->NextToken();


	int peek_val = 0;
	bool decvar = false;

	while (!mStream->EOS())
	{

		auto token = mStream->PeekToken(peek_val);
		if (token.mText == "Vec3")
		{
			int vv = 2;
		}
		int ee = 1;

		switch (token.mType) {
		case TokenType::TokenInc:
			return CodeType::CodeInc;
			break;
		case TokenType::TokenDec:
			return CodeType::CodeDec;
			break;
		case TokenType::TokenParseStop:
			return CodeType::CodeParseStop;
			break;
		case TokenType::TokenDebugStop:
			return CodeType::CodeDebug;
			break;
		case TokenType::TokenWhile:
			return CodeType::CodeWhile;
		case TokenType::TokenReturn:
			return CodeType::CodeReturn;
		case TokenType::TokenFor:
			return CodeType::CodeFor;

			break;
		case TokenType::TokenIf:

			return CodeType::CodeIf;

		case TokenType::TokenPeriod:

			if (mStream->FindInLine(TokenType::TokenLeftPara,peek_val))
			{
				return CodeType::ClassStatement;
			}
			break;
		case TokenType::TokenIdent:

			if (mStream->PeekToken(1).mType == TokenType::TokenInc)
			{
				return CodeType::CodeInc;
			}
			if (mStream->PeekToken(1).mType == TokenType::TokenDec)
			{
				return CodeType::CodeDec;
			}

			if (mStream->FindInLine(TokenType::TokenPeriod,peek_val))
			{
				peek_val++;
				continue;
			}

			if (mStream->FindInLine(TokenType::TokenEquals,peek_val))
			{
				auto cv = ZScriptContext::CurrentContext->FindClass(token.mText);
				//int cvv = 2;
				if (cv != nullptr) {
					return CodeType::CodeDeclareVars;
				}
				

				if (mStream->FindInLine(TokenType::TokenNew,peek_val))
				{

					return CodeType::CodeDeclareVars;
				}
				return CodeType::CodeAssign;
			}
			else {
				return CodeType::CodeStatement;
			}

			break;

		case TokenType::TokenString:
		case TokenType::TokenInt:
		case TokenType::TokenFloat:
			return CodeType::CodeDeclareVars;
			break;

		case TokenType::TokenLeftPara:

			return CodeType::CodeStatement;

			break;
		case TokenType::TokenEnd:
		case TokenType::TokenElse:
		case TokenType::TokenElseIf:

			return CodeType::CodeEnd;

			break;
		case TokenType::TokenEquals:

			return CodeType::CodeAssign;

			break;
		}

		peek_val++;

	}

	int aa = 5;

	return CodeType::CodeUnknown;

}
*/

ZScriptNode* ZParseCodeBody::Parse() {

	//auto tok = mStream->NextToken();

	auto codebody = new ZCodeBodyNode;

	Token tk(TokenType::EndOfFile, "");

	bool next_Debug = false;

	while (!mStream->EOS()) {

		auto code_type = PredictType();
		auto vv = mStream->PeekToken(0);
		ZParseStatement* parse_statement = nullptr;
		ZStatementNode* statement_node = nullptr;
		ZParseVars* parse_vars = nullptr;
		ZVarsNode* vars_node = nullptr;
		ZParseClassStatement* parse_clsstatement = nullptr;
		ZClassStatementNode* clsstatement_node = nullptr;
		Token ct(TokenType::TokenVoid, "");
		int e = 0;

		switch (code_type) {
		case CodeType::CodeStartTransient:
		{
			auto parse_start = new ZParseStartTransient(mStream);
			auto start_node = parse_start->Parse();
			codebody->AddNode(start_node);
		}
			break;
		case CodeType::CodeInc:

		{
			auto t = mStream->NextToken();
			ZIncNode* inc_node = new ZIncNode;
			inc_node->SetVarName(t.mText);
			codebody->AddNode(inc_node);
			mStream->NextToken();
			int aa = 5;
		}
		break;
		case CodeType::CodeDec:

		{
			auto t = mStream->NextToken();
			ZIncNode* inc_node = new ZIncNode;
			inc_node->SetVarName(t.mText);
			codebody->AddNode(inc_node);
			inc_node->SetNegative();
			mStream->NextToken();

		}
		break;
		case CodeType::CodeParseStop:

		{
			mStream->NextToken();
			int stop_here = 1;
		}

		break;
		case CodeType::CodeDebug:
			next_Debug = true;
			{
				auto cc = mStream->NextToken();
				mStream->NextToken();
			}
			break;
		case CodeType::CodeWhile:
		{

			auto parse_while = new ZParseWhile(mStream);
			auto while_node = (ZWhileNode*)parse_while->Parse();
			if (next_Debug) {
				while_node->SetDebug(true);
				next_Debug = false;
			}
			codebody->AddNode(while_node);
			if (mStream->PeekToken(0).mType == TokenType::TokenEnd)
			{
				mStream->NextToken();
			}
		}


		break;
		case CodeType::CodeReturn:
		{
			auto parse_ret = new ZParseReturn(mStream);
			auto ret_node = (ZReturnNode*)parse_ret->Parse();
			ret_node->SetReturn(true);
			codebody->AddNode(ret_node);
			ret_node->SetReturnType(ZMethodNode::mCurrentNode->GetReturnType());
			int z = 0;
		}
		break;
		case CodeType::CodeFor:
		{

			auto parse_for = new ZParseFor(mStream);
			auto for_node = (ZForNode*)parse_for->Parse();
			if (next_Debug) {
				for_node->SetDebug(true);
				next_Debug = false;
			}
			codebody->AddNode(for_node);
			if (mStream->PeekToken(0).mType == TokenType::TokenEnd)
			{
				int cc = 5;
				mStream->NextToken();
			}

		}

		break;
		case CodeType::CodeIf:
		{

			auto parse_if = new ZParseIf(mStream);
			auto if_node = parse_if->Parse();
			if (next_Debug) {
				if_node->SetDebug(true);
				next_Debug = false;

			}
			codebody->AddNode(if_node);

		}

		break;
		case CodeType::CodeAssign:
		{
			auto tok = mStream->NextToken();
			int aa = 5;


			if (mStream->PeekToken(0).mType == TokenType::TokenEquals)
			{
				mStream->Back();
			}
			auto parse_ass = new ZParseAssign(mStream);
			auto parse_node = parse_ass->Parse();
			if (next_Debug) {
				parse_node->SetDebug(true);
				next_Debug = false;
			}
			codebody->AddNode(parse_node);

		}

		break;
		case CodeType::ClassStatement:

			e = 1;
			parse_clsstatement = new ZParseClassStatement(mStream);
			clsstatement_node = (ZClassStatementNode*)parse_clsstatement->Parse();
			if (next_Debug) {
				clsstatement_node->SetDebug(true);
				next_Debug = false;
			}
			codebody->AddNode(clsstatement_node);

			break;
		case CodeType::CodeEnd:
		case CodeType::CodeElse:

			if (mStream->PeekToken(0).mType == TokenType::TokenEnd || TokenType::TokenElseIf)
			{
				mStream->NextToken();
				return codebody;
			}
			ct = mStream->NextToken();
			if (ct.mType != TokenType::TokenEnd)
			{
				ct = mStream->NextToken();
			}
			mStream->AssertNextToken(TokenType::TokenEndOfLine);
			return codebody;

			break;
		case CodeType::CodeMem:
		case CodeType::CodeDeclareVars:

			if (mStream->PeekToken(0).mType == TokenType::TokenEndOfLine) {
				mStream->NextToken();
			}
			parse_vars = new ZParseVars(mStream);
			vars_node = (ZVarsNode*)parse_vars->Parse();
			if (next_Debug) {
				vars_node->SetDebug(true);
				next_Debug = false;
			}
			codebody->AddNode(vars_node);

			//tk = mStream->NextToken();
			vars_node->SetCodeOwner(codebody);

			e = 1;

			break;
		case CodeType::CodeStatement:

		{
			parse_statement = new ZParseStatement(mStream);

			statement_node = (ZStatementNode*)parse_statement->Parse();
			if (next_Debug) {
				statement_node->SetDebug(true);
				next_Debug = false;
			}
			codebody->AddNode(statement_node);

			auto tt = mStream->NextToken();
			if (tt.mType == TokenType::TokenEnd) {
				mStream->Back();
				mStream->Back();
			}
			if (tt.mType == TokenType::TokenEndOfLine) {
				mStream->Back();
			}

			auto next_tok = mStream->AssertNextToken(TokenType::TokenEndOfLine);
		}
			break;
		case CodeType::CodeListAdd:
		{
			auto parse_listadd = new ZParseListAdd(mStream);
			auto listadd_node = parse_listadd->Parse();
			codebody->AddNode((ZScriptNode*)listadd_node);

			if (mStream->PeekToken(0).mType == TokenType::TokenEndOfLine)
			{
				mStream->NextToken();
			}

		}
			break;
		case CodeType::CodeForEach:
		{


			auto parse_foreach = new ZParseForEach(mStream);
			auto foreach_node = (ZForEachNode*)parse_foreach->Parse();

			if (next_Debug) {
				foreach_node->SetDebug(true);
				next_Debug = false;
			}

			codebody->AddNode(foreach_node);
		}

			break;

		}

		int bb = 5;

	}

	int aa = 5;

	return codebody;
	return nullptr;

}