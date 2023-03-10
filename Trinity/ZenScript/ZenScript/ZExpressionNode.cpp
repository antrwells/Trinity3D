#include "ZExpressionNode.h"
#include "ZScriptContext.h"
#include "ZContextScope.h"
#include "ZClassNode.h"
#include "ZStatementNode.h"
#include "ZClassStatementNode.h"
#include "ZContextVar.h"
#include "ZNewNode.h"
#include "ZEnumNode.h"
void ZExpressionNode::SetExpression(Expression expr) {

	//mElements.push_back(element);


    

	mExpression = expr;

}

ZContextVar* ZExpressionNode::Exec(const std::vector<ZContextVar*>& params)
{
	return mExpression.Evaluate(ZExpressionNode::RecvType);

	return nullptr;
}



ZContextVar* GetVar(size_t name1, size_t name2) {
    ZContextVar* var = nullptr;

    if (ZScriptContext::CurrentContext->IsEnum(name1)) {

        auto en = ZScriptContext::CurrentContext->GetEnum(name1);

        auto ri = VMakeInt(en->GetHashOptionIndex(name2));
        return ri;

        int a = 5;
    }

    if (ZScriptContext::CurrentContext->IsStaticClass(name1))
    {
        auto scls = ZScriptContext::CurrentContext->GetStaticClass(name1);
        var = scls->FindVar(name2);

    }
    else {

        var = ZScriptContext::CurrentContext->GetScope()->FindVar(name1);
        if (name2 != 0)
        {
            auto cls = var->GetClassVal();
            var = cls->FindVar(name2);
        }

    }
    return var;
}

VarType ZExpressionNode::RecvType = VarType::VarVoid;

int precedence(ExprOperatorType op) {

    if (op == OpUMinus)
        return 3;
    
    if (op == OpPlus || op == OpMinus)
        return 5;
    if (op == OpMultiply || op == OpDivide)
        return 6;
    if (op == OpGreater || op == OpLess)
        return 8;
    if (op == OpEquals || op == OpNot)
        return 9;
    if (op == OpAnd)
        return 13;
    if (op == OpOr)
        return 14;
    

    return 0;
}

int applyOpInt(int a, int b, ExprOperatorType op) {
    switch (op) {
       case OpPlus: return a + b;
    case OpMinus: return a - b;
    case OpMultiply: return a * b;
    case OpDivide: return a / b;
    case OpGreater: return a > b ? 1 : 0;
    case OpLess: return a < b ? 1 : 0;
    case OpEquals: return a == b ? 1 : 0;
    case OpNot: return a != b ? 1 : 0;
    case OpAnd:
    {
        bool res = ((a >= 1) && (b >= 1));
        if (res) return 1;
        return 0;
        break;
    }
    case OpOr:
    {
        bool res = ((a >= 1)) || (b >= 1);
        if (res) return 1;
        return 0;
        break;
    }

    }
    int bbb = 5;
}

float applyOpFloat(float a, float b, ExprOperatorType op) {
    switch (op) {
    case OpPlus: return a + b;
    case OpMinus: return a - b;
    case OpMultiply: return a * b;
    case OpDivide: return a / b;
    case OpGreater: return a > b ? 1.0f : 0.0f;
    case OpLess: return a < b ? 1.0f : 0.0f;
    case OpEquals: return a == b ? 1.0f : 0.0f;
    case OpNot: return a != b ? 1.0f : 0.0f;
    case OpAnd:
    {
        bool res = ((a >= 1) && (b >= 1));
        if (res) return 1.0f;
        return 0.0f;
        break;
    }
    case OpOr:
    {
        bool res = ((a >= 1)) || (b >= 1);
        if (res) return 1.0f;
        return 0.0f;
        break;
    }

    }
    return 0.0f;
    //int bbb = 5;
}


int evaluateInt(std::vector<ExpressionElement> mElements) {

    std::stack<int> values;
    std::stack<ExprOperatorType> ops;

    for (int i = 0; i < mElements.size(); i++) {

        auto tok = mElements[i];

        if (tok.mOp == OpUMinus) {
            values.push(-mElements[i + 1].mValInt);
            i++;
            continue;
        };



        if (tok.mOp == ExprOperatorType::OpLeftBrace)
        {
            ops.push(tok.mOp);

        }
        else if (tok.mType == EInt || tok.mType == EFloat || tok.mType == EVar || tok.mType == EStatement || tok.mType == EClassStatement || tok.mType == ETrue || tok.mType == EFalse)
        {
            //int val = 0;
            if (tok.mType == EInt) {
                values.push(tok.mValInt);
            }
            else if (tok.mType == EFloat) {
                values.push((int)tok.mValFloat);
            }
            else if (tok.mType == ETrue)
            {
                values.push((int)1);
            }
            else if (tok.mType == EFalse) {
                values.push((int)0);
            }
            else if (tok.mType == EClassStatement)
            {
                auto res = tok.mClassStatement->Exec({});

                switch (res->GetType()) {
                case VarType::VarInteger:
                    values.push(res->GetIntVal());
                    break;
                case VarType::VarFloat:
                    values.push((int)res->GetFloatVal());
                    break;
                case VarType::VarBool:
                    
                    values.push(res->GetIntVal());

                    break;
                }
                int aa = 5;
            }
            else if (tok.mType == EStatement)
            {
                auto res = tok.mStatement->Exec(std::vector<ZContextVar*>());

                switch (res->GetType()) {
                case VarType::VarInteger:
                    values.push(res->GetIntVal());
                    break;
                case VarType::VarFloat:
                    values.push((int)res->GetFloatVal());
                    break;
                case VarType::VarBool:
                    values.push(res->GetIntVal());
                    break;
                
                }

                //values.push(res->GetIntVal());


            }
            else if (tok.mType == EVar)
            {
                int depth = 0;
                auto var = GetVar(tok.mNameHash[0], tok.mNameHash[1]);
                if (var != nullptr) {
                    switch (var->GetType()) {
                    case VarType::VarExpr:
                        values.push((int)var->GetExpr()->Exec({})->GetIntVal());
                        break;
                    case VarType::VarFloat:
                        if (var->GetArray()) {
                            auto ip = tok.mAccess->Exec({})->GetIntVal();
                            float* f = (float*)var->GetMem(ip * sizeof(float));
                            values.push((int)f[0]);
                        }
                        else {
                            values.push((int)var->GetFloatVal());
                        }
                        break;
                    case VarType::VarInteger:

                        if (var->GetArray()) {
                            auto ip = tok.mAccess->Exec({})->GetIntVal();
                            int* f = (int*)var->GetMem(ip * sizeof(int));
                            values.push(f[0]);

                        }
                        else {
                            values.push(var->GetIntVal());
                        }
                        break;
                    case VarType::VarBool:
                        values.push(var->GetIntVal());
                        break;
                    case VarType::VarVar:

                        switch (var->GetCurrentType()) {
                        case VarInteger:
                            values.push(var->GetIntVal());
                            break;
                        case VarFloat:
                            values.push((int)var->GetFloatVal());
                            break;
                        }

                        break;
                    }
                }



                int a = 5;
                /*
                for (int i = 0; i < 16; i++)
                {
                    if (tok.mNameHash[i] != 0)
                    {
                        depth++;
                    }
                    else {
                        break;
                    }
                }

                if (depth > 1)
                {
                    if (ZScriptContext::CurrentContext->IsEnum(tok.mNameHash[0])) {
                        auto e = ZScriptContext::CurrentContext->GetEnum(tok.mNameHash[0]);
                        values.push(e->GetHashOptionIndex(tok.mNameHash[1]));

                    }else 
                    if (ZScriptContext::CurrentContext->IsStaticClass(tok.mNameHash[0])) {

                        auto scls = ZScriptContext::CurrentContext->GetStaticClass(tok.mNameHash[0]);

                        auto gv = scls->FindVar(tok.mNameHash[1]);

                        switch (gv->GetType()) {
                        case VarType::VarExpr:
                            values.push((int)gv->GetExpr()->Exec({}));
                            break;
                        case VarType::VarFloat:
                            values.push((int)gv->GetFloatVal());
                            break;
                        case VarType::VarInteger:
                            values.push(gv->GetIntVal());
                            break;
                        case VarType::VarBool:
                            values.push(gv->GetIntVal());
                            break;
                        case VarType::VarVar:

                            switch (gv->GetCurrentType()) {
                            case VarInteger:
                                values.push(gv->GetIntVal());
                                break;
                            case VarFloat:
                                values.push((int)gv->GetFloatVal());
                                break;
                            }

                            break;
                        }

                        //values.push(gv->GetIntVal());

                    }
                    else {

                        auto cls = ZScriptContext::CurrentContext->GetScope()->FindVar(tok.mNameHash[0]);
                        auto av = cls->GetClassVal()->FindVar(tok.mNameHash[1]);

                        switch (av->GetType()) {
                        case VarType::VarExpr:
                            values.push((int)av->GetExpr()->Exec({}));
                            break;
                        case VarType::VarFloat:
                            values.push((int)av->GetFloatVal());
                            break;
                        case VarType::VarInteger:
                            values.push(av->GetIntVal());
                            break;
                        case VarType::VarBool:
                            values.push(av->GetIntVal());
                            break;
                        case VarType::VarVar:

                            switch (av->GetCurrentType()) {
                            case VarInteger:
                                values.push(av->GetIntVal());
                                break;
                            case VarFloat:
                                values.push((int)av->GetFloatVal());
                                break;
                            }

                            break;
                        }

                        //---
                      
                    }//values.push(333);
                
                }
                else {
                    auto evar = ZScriptContext::CurrentContext->GetScope()->FindVar(tok.mNameHash[0]);
                    switch (evar->GetType()) {
                    case VarType::VarExpr:
                        values.push((int)evar->GetExpr()->Exec({})->GetIntVal());
                        break;
                    case VarType::VarFloat:
                        values.push((int)evar->GetFloatVal());
                        break;
                    case VarType::VarInteger:
                        values.push(evar->GetIntVal());
                        break;
                    case VarType::VarBool:
                        values.push(evar->GetIntVal());
                        break;
                    case VarType::VarVar:

                        switch (evar->GetCurrentType()) {
                        case VarInteger:
                            values.push(evar->GetIntVal());
                            break;
                        case VarFloat:
                            values.push((int)evar->GetFloatVal());
                            break;
                        }

                        break;
                    }
                }
                */
            }
        }
        else if (tok.mOp == OpRightBrace)
        {
            while (!ops.empty() && ops.top()!=OpLeftBrace)
            {
      
                int val2 = values.top();
                values.pop();

                if (values.size() == 0) {
                    //if()
                }

                int val1 = values.top();
                values.pop();

                ExprOperatorType op = ops.top();
                ops.pop();

                values.push(applyOpInt(val1, val2, op));

            }

            if (!ops.empty()) {
                ops.pop();
            }

        }
        else {

            while (!ops.empty() && precedence(ops.top())
                >= precedence(tok.mOp)) {
                int val2 = values.top();
                values.pop();

                int val1 = 0;
                if (values.size() == 0) {

                }
                else {
                    val1 = values.top();
                    values.pop();
                }
                ExprOperatorType op = ops.top();
                ops.pop();

                values.push(applyOpInt(val1, val2, op));
            }

            ops.push(tok.mOp);

        }

        //if(tok.mType == ExprElementType::


    }

    while (!ops.empty()) {
        int val2 = values.top();
        values.pop();

        if (values.size() == 0)
        {
            if (ops.top() == OpMinus) {
                values.push(-val2);
                ops.pop();
                continue;
            }
            int aa = 5;
        }

        int val1 = values.top();
        values.pop();

        ExprOperatorType op = ops.top();
        ops.pop();

        values.push(applyOpInt(val1, val2, op));
    }

    return values.top();

}

float GetValue(ExpressionElement tok)
{
    if (tok.mType == EInt) {
        //values.push((float)tok.mValInt);
        return (float)tok.mValInt;
    }
    else if (tok.mType == EFloat) {
        //values.push(tok.mValFloat);
        return tok.mValFloat;
    }
    else if (tok.mType == EClassStatement)
    {
        auto res = tok.mClassStatement->Exec({});

        switch (res->GetType()) {
        case VarType::VarInteger:
            //values.push((float)res->GetIntVal());
            return (float)res->GetIntVal();
            break;
        case VarType::VarFloat:
            //values.push(res->GetFloatVal());
            return res->GetFloatVal();

            break;
        }
        int aa = 5;
    }
    else if (tok.mType == EStatement)
    {
        auto res = tok.mStatement->Exec(std::vector<ZContextVar*>());

        switch (res->GetType()) {
        case VarType::VarInteger:

            //values.push((float)res->GetIntVal());
            return (float)res->GetIntVal();
            break;
        case VarType::VarFloat:
            //values.push(res->GetFloatVal());
            return res->GetFloatVal();
            break;
        }

        //values.push(res->GetIntVal());


    }
    else if (tok.mType == EVar)
    {
   
        int depth = 0;
        auto var = GetVar(tok.mNameHash[0], tok.mNameHash[1]);
        switch (var->GetType()) {
        case VarType::VarExpr:

            return var->GetExpr()->Exec({})->GetFloatVal();
            break;
        case VarType::VarFloat:

            if (var->GetArray()) {
                auto ip = tok.mAccess->Exec({})->GetIntVal();
                float* f = (float*)var->GetMem(ip * sizeof(float));
                return (float)f[0];
            }

            return var->GetFloatVal();

            break;
        case VarType::VarInteger:
            if (var->GetArray()) {
                auto ip = tok.mAccess->Exec({})->GetIntVal();
                int* f = (int*)var->GetMem(ip * sizeof(int));
                return (float)f[0];
            }
            return (float)var->GetIntVal();
            break;

        case VarType::VarBool:
            return (float)var->GetIntVal();

            break;

        case VarType::VarVar:

            switch (var->GetCurrentType()) {
            case VarInteger:
                return (float)var->GetIntVal();
                break;
            case VarFloat:
                return (float)var->GetFloatVal();
                break;
            }

            break;
        }

        
    }
    return 0.0f;
}


float evaluateFloat(std::vector<ExpressionElement> mElements) {

    std::stack<float> values;
    std::stack<ExprOperatorType> ops;

    for (int i = 0; i < mElements.size(); i++) {

        auto tok = mElements[i];


        if (tok.mOp == OpUMinus) {
            
            auto nx = mElements[i + 1];
            
            values.push(-GetValue(nx));
            //values.push(-mElements[i + 1].mValFloat);

            i++;
            continue;
        };


        if (tok.mOp == ExprOperatorType::OpLeftBrace)
        {
            ops.push(tok.mOp);

        }
        else if (tok.mType == EInt || tok.mType == EFloat || tok.mType == EVar || tok.mType == EStatement || tok.mType == EClassStatement)
        {
            //int val = 0;
            values.push(GetValue(tok));
        }
        else if (tok.mOp == OpRightBrace)
        {
            while (!ops.empty() && ops.top() != OpLeftBrace)
            {

                float val2 = values.top();
                values.pop();

                float val1 = values.top();
                values.pop();

                ExprOperatorType op = ops.top();
                ops.pop();

                values.push(applyOpFloat(val1, val2, op));

            }

            if (!ops.empty()) {
                ops.pop();
            }

        }
        else {

            while (!ops.empty() && precedence(ops.top())
                >= precedence(tok.mOp)) {
                float val2 = values.top();
values.pop();

float val1 = 0;
if (values.size() == 0) {

}
else {
    val1 = values.top();
    values.pop();
}


ExprOperatorType op = ops.top();
ops.pop();

values.push(applyOpFloat(val1, val2, op));
            }

            ops.push(tok.mOp);

        }

        //if(tok.mType == ExprElementType::


    }

    while (!ops.empty()) {
        float val2 = values.top();
        values.pop();

        float val1 = values.top();
        values.pop();

        ExprOperatorType op = ops.top();
        ops.pop();

        values.push(applyOpFloat(val1, val2, op));
    }

    return values.top();

}

Expression ZExpressionNode::GetExpression() {

    return mExpression;

}


/*
ZContextVar* GetVar(std::string name1,std::string name2) {
    ZContextVar* var = nullptr;
    if (ZScriptContext::CurrentContext->IsStaticClass(name1))
    {
        auto scls = ZScriptContext::CurrentContext->GetStaticClass(name1);
        var = scls->FindVar(name2);

    }
    else {

        var = ZScriptContext::CurrentContext->GetScope()->FindVar(name1);
        if (name2 != "")
        {
            auto cls = var->GetClassVal();
            var = cls->FindVar(name2);
        }

    }
    return var;
}
*/
std::string StringValue(ExpressionElement e)
{

    switch (e.mType) {
    case EStatement:
        return e.mStatement->Exec({})->GetStringVal();
    case EClassStatement:
        return e.mClassStatement->Exec({})->GetStringVal();
    case EVar:
        return GetVar(e.mNameHash[0],e.mNameHash[1])->GetStringVal();
        break;
    case EString:
        return e.mValString;
    }
    return "";
}

bool IsString(ExpressionElement e)
{
    switch (e.mType) {
    case EStatement: {
        auto res = e.mStatement->Exec({});
        if (res->GetType() == VarString)
        {
            return true;
        }
    }
        break;
    case EClassStatement:
    {
        auto ret = e.mClassStatement->GetReturnType();
        if (ret == VarType::VarString)
        {
            return true;
        }
    }
        break;
    case EVar:
    {
        auto vv = GetVar(e.mNameHash[0], e.mNameHash[1]);
        if (vv->GetType() == VarType::VarString)
        {
            return true;
        }
    }
        break;
    case EString:
        return true;
    }
    return false;

}


bool Expression::IsCompare() {

    if (mElements.size() == 3)
    {
        if (mElements[1].mType == EOp)
        {
            if (mElements[1].mOp == OpEquals)
            {

                if (mElements[0].mType == EVar && mElements[2].mType == EVar) {
                    //return true;

                    auto v1 = GetVar(mElements[0].mNameHash[0], mElements[0].mNameHash[1]);
                    auto v2 = GetVar(mElements[2].mNameHash[0], mElements[2].mNameHash[1]);

                    if (v1->GetType() == VarType::VarInstance) {
                        auto c1 = v1->GetClassVal();
                        auto c2 = v2->GetClassVal();

                        auto com1 = c1->FindComparer();
                        auto com2 = c2->FindComparer();

                        if (com1 != nullptr && com2 != nullptr) {

                            return true;

                        }
                    }


                    int b = 5;

                }

            }
        }
    }
    return false;
}

bool Expression::DoesCompare() {

    if (mElements.size() == 3)
    {
        if (mElements[1].mType == EOp)
        {
            if (mElements[1].mOp == OpEquals)
            {

                if (mElements[0].mType == EVar && mElements[2].mType == EVar) {
                    //return true;

                    auto v1 = GetVar(mElements[0].mNameHash[0], mElements[0].mNameHash[1]);
                    auto v2 = GetVar(mElements[2].mNameHash[0], mElements[2].mNameHash[1]);
                    auto c1 = v1->GetClassVal();
                    auto c2 = v2->GetClassVal();

                    auto com1 = c1->FindComparer();
                    auto com2 = c2->FindComparer();

                    if (com1 != nullptr && com2 != nullptr) {

                        switch (com1->GetType()) {
                        case VarType::VarCObj:

                            if (com1->GetCObj() == com2->GetCObj())
                            {
                                return true;
                            }
                            else {
                                return false;
                            }

                            break;
                        }

                        return true;

                    }


                    int b = 5;

                }

            }
        }
    }
    return false;
}

ZContextVar* Expression::Evaluate(VarType recv) {

    int aa = 5;
    if (recv == VarVoid) {
        aa = 5;

    }
    VarType rt = recv;
    ZExpressionNode::RecvType = VarVoid;

    if (mElements.size() == 1)
    {
        if (mElements[0].mType == EVar)
        {

          


            auto var = GetVar(mElements[0].mNameHash[0], mElements[0].mNameHash[1]);
            if (var->GetType() == VarType::VarExpr)
            {
                return var->GetExpr()->Exec({});
            }
            if (var != nullptr) {
                if (var->GetArray()) {
                    
                    switch (var->GetType())
                    {
                    case VarType::VarInteger:
                    {
                        int acc = mElements[0].mAccess->Exec({})->GetIntVal();

                        int* rv = (int*)var->GetMem(acc * sizeof(int));

                        return VMakeInt(rv[0]);
                    }
                        break;
                    case VarType::VarFloat:
                    {
                        int acc = mElements[0].mAccess->Exec({})->GetIntVal();

                        float* rv = (float*)var->GetMem(acc * sizeof(float));

                        return VMakeFloat(rv[0]);
                    }
                        break;
                    }
                    //var->GetMem()
                    int a = 5;

                }
                return var;
            }
            int aa = 5;

        }
        if (mElements[0].mType == ETrue)
        {
            return VMakeInt(1);
        }
        else if (mElements[0].mType == EFalse)
        {
            return VMakeInt(0);
        }

    }

    if (mElements.size() == 3)
    {

        if (IsCompare()) {

            if (DoesCompare()) {

                return VMakeInt(1, false);

            }
            else {
                return VMakeInt(0, false);
            }
            int b = 5;
        }

        if (IsStrings()) {

            if (mElements[1].mType == EOp)
            {
                auto s1 = StringValue(mElements[0]);
                auto s2 = StringValue(mElements[2]);
                if (mElements[1].mOp == OpEquals)
                {
                    int same = 0;
                    bool s = s1 == s2;
                    if (s) {
                        same = 1;
                    }
                    
                    return VMakeInt(same,false);

                    

                }
            }

            int bb = 5;
        }

    }

    if (mElements.size() == 1) {
        if (mElements[0].mType == ENew)
        {

            auto new_cls = mElements[0].mNew->Exec({});
            return VMakeClass(new_cls->GetClassVal(),false);

        }
        if (mElements[0].mType == EInt) {
            return VMakeInt(mElements[0].mValInt);
        }
        if (mElements[0].mType == EFloat)
        {
            return VMakeFloat(mElements[0].mValFloat);
        }
        if (mElements[0].mType == EStatement)
        {

            auto rv = mElements[0].mStatement->Exec({});

            switch (rv->GetType()) {
            case VarInstance:
                return VMakeClass(rv->GetClassVal(),false);
            case VarFloat:
                return VMakeFloat(rv->GetFloatVal(),false);
            case VarInteger:
                return VMakeInt(rv->GetIntVal(),false);
            case VarString:
                return VMakeString(rv->GetStringVal(),false);
            case VarCObj:
                return VMakeC(rv->GetCObj(), rv->GetCompare());
            }

            int a4a = 5;

        }
        else if (mElements[0].mType == EClassStatement)
        {

            auto rv = mElements[0].mClassStatement->Exec({});
            switch (rv->GetType()) {
            case VarInstance:
                return VMakeClass(rv->GetClassVal(),false);
            case VarFloat:
                return VMakeFloat(rv->GetFloatVal(),false);
            case VarInteger:
                return VMakeInt(rv->GetIntVal(),false);
            case VarCObj:
                return VMakeC(rv->GetCObj(),false);
                break;
            case VarString:
                    return VMakeString(rv->GetStringVal(),false);
            }
            int no = 5;
        }
        else if (mElements[0].mType == EVar)
        {

            if (mElements[0].mValName[0] == "anim")
            {
                int bb = 5;
            }
            auto rv = GetVar(mElements[0].mNameHash[0],mElements[0].mNameHash[1]);

            
            switch (rv->GetType()) {
            case VarBool:
            {
                int aa = 5;
                return VMakeInt(rv->GetBoolVal());
            }
                break;
            case VarInstance:
                if (rv->GetCObj() != nullptr) {
                    return VMakeC(rv->GetCObj(),false);
                }

                return VMakeClass(rv->GetClassVal(),false);
            case VarFloat:
                return VMakeFloat(rv->GetFloatVal());
            case VarInteger:
                return VMakeInt(rv->GetIntVal());
            case VarCObj:
                return VMakeC(rv->GetCObj());
                break;
            case VarString:
                return VMakeString(rv->GetStringVal());
                break;
            case VarVar:
                
                switch (rv->GetCurrentType()) {
                case VarInteger:
                    return VMakeInt(rv->GetIntVal(), false);
                    break;
                case VarFloat:
                    return VMakeFloat(rv->GetFloatVal(), false);
                    break;
                case VarString:

                    return VMakeString(rv->GetStringVal(), false);

                    break;
                case VarInstance:

                    return VMakeClass(rv->GetClassVal(), false);

                    break;

                }

                break;
            }

            int aaa = 5;

        }
    }

    if (rt == VarVoid) {

        if (mElements.size() == 0)
        {
            auto ele = mElements[0];

            auto quick_v = GetVar(mElements[0].mNameHash[0],mElements[0].mNameHash[1]);

            if (quick_v != nullptr) {
                return quick_v;
            }

            if (ele.mType == EVar)
            {

                return VMakeFloat(evaluateFloat(mElements));


                int bb = 5;
            }
        }
        else {

            if (mElements[0].mType == EString) {

                return VMakeString(mElements[0].mValString);
            }
            if (GetVar(mElements[0].mNameHash[0], mElements[0].mNameHash[1]) != nullptr) {

                auto vt3 = GetVar(mElements[0].mNameHash[0], mElements[0].mNameHash[1]);
                if (vt3->GetType() == VarVar)
                {

                    if (vt3->GetCurrentType() == VarString)
                    {
                        return VMakeString(vt3->GetStringVal());
                    }

                }

            }


            bool is_float = false;
            for (int i = 0; i < mElements.size(); i++) {

                auto var = GetVar(mElements[i].mNameHash[0],mElements[i].mNameHash[1]);
                if (var != nullptr) {
                    if (var->GetType() == VarCObj)
                    {
                        return VMakeC(var->GetCObj());
                    }
                    if (var->GetType() == VarInstance) {
                        return VMakeClass(var->GetClassVal());
                    }
                    if (var->GetType() == VarFloat) {
                        is_float = true;
                    }

                }
            }
            for (int i = 0; i < mElements.size(); i++)
            {
                if (mElements[i].mType == ExprElementType::EFloat)
                {
                    is_float = true;
                }
                if (GetVar(mElements[i].mNameHash[0], mElements[i].mNameHash[1]) != nullptr) {

                    auto v1 = GetVar(mElements[i].mNameHash[0], mElements[i].mNameHash[1]);
                    int aa = 5;
                    if (v1->GetType() == VarVar)
                    {
                        if (v1->GetCurrentType() == VarFloat)
                        {
                            is_float = true;
                        }
                    }
                }

            }
            if (is_float) {
                return VMakeFloat(evaluateFloat(mElements));
            }
            else {
                return VMakeInt(evaluateInt(mElements));
            }
        }
    }


    switch (rt) {
    case VarInteger:
        return VMakeInt(evaluateInt(mElements));
        break;
    case VarFloat:
        return VMakeFloat(evaluateFloat(mElements));
        break;
    case VarCObj:
    {

        auto var = GetVar(mElements[0].mNameHash[0],mElements[0].mNameHash[1]);

        return VMakeC(var->GetCObj());

        int aa = 5;
    }
        break;
    default:

            

      

        if (IsStrings()) {
            return VMakeString(mElements[0].mValString);
        }


      //  switch(mElements[0].ge)

        auto gt = GetVar(mElements[0].mNameHash[0], mElements[0].mNameHash[1]);

        switch (gt->GetType()) {
        case VarType::VarFloat:

            return VMakeFloat(evaluateFloat(mElements));
            break;
        case VarType::VarInteger:
            return VMakeInt(evaluateInt(mElements));
            break;
        }
        int bb = 0;

        break;

    }

    if (HasOperators() == false)
    {
        if (IsInt()) {

            return VMakeInt(evaluateInt(mElements));

        }
        else if (IsFloat())
        {
            return VMakeFloat(evaluateFloat(mElements));
        }
        else if (IsStrings()) {

            return VMakeString(mElements[0].mValString);

        }
        ZContextVar* var = nullptr;
        if (ZScriptContext::CurrentContext->IsStaticClass(mElements[0].mNameHash[0]))
        {
            auto scls = ZScriptContext::CurrentContext->GetStaticClass(mElements[0].mNameHash[0]);
            var = scls->FindVar(mElements[0].mNameHash[1]);

        }
        else {

            var = ZScriptContext::CurrentContext->GetScope()->FindVar(mElements[0].mNameHash[0]);
        }
        switch (var->GetType()) {

        case VarInteger:
            return VMakeInt(var->GetIntVal());
        case VarFloat:
            return VMakeFloat(var->GetFloatVal());
        case VarString:
            return VMakeString(var->GetStringVal());
        case VarInstance:
            return VMakeClass(var->GetClassVal());
        case VarCObj:
            return VMakeC(var->GetCObj());
            break;
        default:
        {
            int aa = 5;
            break;
        }

        }

        aa = 1;
    }
    else {

        if (IsInt()) {

            return VMakeInt(evaluateInt(mElements));

        }
        else if (IsFloat())
        {
            return VMakeFloat(evaluateFloat(mElements));
        }
        else if (IsStrings()) {

            return VMakeString(mElements[0].mValString);

        }
    }
    int cc = 0;

    return nullptr;


    //  goto skip1;
      /*
      if (mElements.size() == 1)
      {
          if (mElements[0].mType == ExprElementType::EStatement) {

              auto vv = mElements[0].mStatement->Exec({});

              return vv;

          }
          if (mElements[0].mType == ExprElementType::EVar)
          {

              auto gvar = ZScriptContext::CurrentContext->GetScope()->FindVar(mElements[0].mValName[0]);

              if (mElements[0].mValName[1] != "")
              {
                  auto vv = gvar->GetClassVal();
    //              ZScriptContext::CurrentContext->PushClass(vv);
                  auto ret_v = vv->FindVar(mElements[0].mValName[1]);
      //            ZScriptContext::CurrentContext->PopClass();
                  return ret_v;

              }
              else {
                  return gvar;
              }
              int b = 0;
          }

      }

      bool is_int = true;
      bool is_string = false;
      bool is_cs = false;
      for (int i = 0; i < mElements.size(); i++) {
          if (mElements[i].mType == EFloat)
          {
              is_int = false;
          }
          if (mElements[i].mType == EClassStatement)
          {
              is_cs = true;
          }
          if (mElements[i].mType == EString)
          {
              is_string = true;
          }
          if (mElements[i].mType == EInt)
          {

              //VString
              //str_val +

          }
          if(mElements[i].mType == EVar)
          {



              auto gvar = ZScriptContext::CurrentContext->GetScope()->FindVar(mElements[i].mValName[0]);
              if (mElements[i].mValName[1] != "")
              {
                  auto cv = gvar->GetClassVal();
                  auto nv = cv->FindVar(mElements[i].mValName[1]);
                  if (nv->GetType() == VarType::VarFloat)
                  {
                      is_int = false;
                  }
                  int aaa = 5;
              }
              else {
                  if (gvar->GetType() == VarType::VarFloat) {
                      is_int = false;
                  }
              }
              // int aa = 5;
             // is_string = true;

          }
      }

      if (is_string) {


          std::string str_val = "";
          for (int i = 0; i < mElements.size(); i++)
          {
              if (mElements[i].mType == ExprElementType::EString)
              {
                  str_val = str_val + mElements[i].mValString;
              }
              if (mElements[i].mType == EVar)
              {
                  auto gvar = ZScriptContext::CurrentContext->GetScope()->FindVar(mElements[i].mValName[0]);
                  int aa = 5;
                  str_val = str_val + gvar->GetStringVal();
              }
          }


          ZContextVar* result = new ZContextVar("expr result", VarType::VarString);
          result->SetString(str_val);
          return result;

      }

      if (!is_int)
      {
          ZContextVar* result = new ZContextVar("expr result", VarType::VarFloat);

          result->SetFloat(evaluateFloat(mElements));
          //        result->SetInt(101);
          int aa = 5;


          return result;
      }
      else if (is_cs == false) {

          ZContextVar* result = new ZContextVar("expr result", VarType::VarInt);

          result->SetInt(evaluateInt(mElements));
          return result;

      }
      else
      {

          //determine type

          for (int i = 0; i < mElements.size(); i++)
          {
              auto ele = mElements[i];
              if (ele.mType == EVar)
              {
                  int depth = 0;
                  for (int i = 0; i < 16; i++)
                  {
                      if (ele.mValName[i] != "")
                      {
                          depth++;
                      }
                  }

                  if (depth > 1)
                  {
                      auto cls = ZScriptContext::CurrentContext->GetScope()->FindVar(ele.mValName[0]);
                      auto av = cls->GetClassVal()->FindVar(ele.mValName[1]);
                      if (av->GetType() == VarType::VarFloat)
                      {
                          ZContextVar* result = new ZContextVar("expr result", VarType::VarFloat);

                          result->SetFloat(evaluateFloat(mElements));
                          return result;
                          //  values.push(av->GetIntVal());
                      }
                      else {
                          //    values.push(av->GetFloatVal());
                      }

                      int aa = 5;
                  }
              }

          }

          if (is_cs) {
              VarType rt = VarType::VarInt;
              //class statements
              for (int i = 0; i < mElements.size(); i++) {

                  if (mElements[i].mType == EClassStatement)
                  {
                      auto t = mElements[i].mClassStatement->GetReturnType();

                      rt = t;

                      int bb = 0;

                  }

              }

              //--


              if (rt == VarType::VarInt)
              {
                  ZContextVar* result = new ZContextVar("expr result", VarType::VarInt);

                  result->SetInt(evaluateInt(mElements));
                  return result;
              }
              if (rt == VarType::VarFloat) {
                  ZContextVar* result = new ZContextVar("expr result", VarType::VarFloat);
                  result->SetFloat(evaluateFloat(mElements));
                  return result;
              }
          }
          return nullptr;
          skip1:


          if (mElements[0].mType == ExprElementType::EString)
          {
              return VMakeString(mElements[0].mValString);
          }

          //        result->SetInt(101);
          int aa = 5;
          ZContextVar* result = new ZContextVar("res", VarType::VarInt);

          result->SetInt(evaluateInt(mElements));

          return result;
          //return result;
          */
};