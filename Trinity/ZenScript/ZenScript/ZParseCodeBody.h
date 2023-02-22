#pragma once
#include "ZParseNode.h"
#include "ZTokenStream.h"

enum CodeType {

    CodeStatement, CodeAssign, CodeDeclareVars, CodeReturn, CodeFor, CodeSwitch, CodeWhile, CodeGoto, CodeLabel,CodeUnknown,
    CodeEnd,ClassStatement,CodeIf,CodeElseIf,CodeElse,CodeDebug,CodeParseStop,CodeInc,CodeDec,CodeListAdd,CodeListRemove,CodeForEach,CodeMem,
    CodeStartTransient,CodeStopTransient

};

class ZParseCodeBody :
    public ZParseNode
{
public:

    ZParseCodeBody(ZTokenStream* stream);
    ZScriptNode* Parse();
    CodeType PredictType();

private:
};

