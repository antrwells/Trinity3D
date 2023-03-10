#include "ZVarsNode.h"
#include "ZContextVar.h"
#include "ZExpressionNode.h"
#include "ZCodeBodyNode.h"
#include "ZMethodNode.h"
#include "ZNewNode.h"
#include "ZScriptContext.h"
void ZVarsNode::SetType(VarType type) {

	mVarType = type;

}

void ZVarsNode::AddVar(std::string name,bool comparer)
{

	VarPair* pair = new VarPair;
	pair->name = name;
	pair->def = nullptr;
	pair->new_node = nullptr;
	pair->comparer = comparer;
	//mVarNames.push_back(name);
	mVars.push_back(pair);
}

void ZVarsNode::AddVar(std::string name,ZExpressionNode* def,bool compare) {

	VarPair* pair = new VarPair;
	pair->name = name;
	pair->def = def;
	//mVarNames.push_back(name);
	pair->comparer = compare;
	mVars.push_back(pair);
	

}

void ZVarsNode::AddVar(std::string name, ZNewNode* new_node,bool compare) {

	VarPair* pair = new VarPair;
	pair->name = name;
	pair->new_node = new_node;
	pair->comparer = compare;
	mVars.push_back(pair);

}

std::vector<VarPair*> ZVarsNode::GetVars() {

	return mVars;

}

VarType ZVarsNode::GetType() {

	return mVarType;

}

void ZVarsNode::SetBaseType(std::string v) {

	TypeID = v;

}

std::string ZVarsNode::GetBaseType()
{

	return TypeID;

}

ZContextVar* ZVarsNode::Exec(const std::vector<ZContextVar*>& params)
{

	for (int i = 0; i < mVars.size(); i++)
	{

		auto var = mVars[i];
		ZContextVar* new_var = new ZContextVar(var->name, this->mVarType,TypeID,var->comparer);
		new_var->SetExpr(var->def);
		if (mIsArray)
		{
			new_var->SetArray(true);
			int asize = var->def->Exec({})->GetIntVal();
			new_var->SetMemSize(asize * 4);
			int a = 5;
		}
		ZClassNode* cls = nullptr;
		new_var->SetBaseID(TypeID);

		ZExpressionNode::RecvType = mVarType;

		switch (mVarType) {
		case VarMem:
		{
			auto expr = new_var->GetExpr();
			auto res = expr->Exec({});

			new_var->SetMemSize(res->GetIntVal());

			int aa = 5;
		}
			break;
		case VarVar:
			if (var->def != nullptr) {

				auto vt = var->def->Exec({});

				auto vtype = vt->GetType();

				//new_var->SetValue(var->def->Exec({})->GetValue());
				switch (vtype) {
				case VarInteger:
					new_var->SetInt(vt->GetIntVal());
					break;
				case VarFloat:
					new_var->SetFloat(vt->GetFloatVal());
					break;
				case VarString:
					new_var->SetString(vt->GetStringVal());
					break;
				}
				int bb = 5;

			}
			break;
		case VarString:
			if (var->def != nullptr) {

				new_var->SetString(var->def->Exec({})->GetStringVal());
				int cc = 5;
			}
			break;
		case VarInteger:
			if (mIsArray == false) {
				if (var->def != nullptr) {
					new_var->SetInt(var->def->Exec({})->GetIntVal());
				}
			}
			break;
		case VarFloat:
			if (mIsArray == false) {
				if (var->def != nullptr) {
					new_var->SetFloat(var->def->Exec({})->GetFloatVal());
				}
			}
			break;
		case VarBool:
			if (var->def != nullptr) {
				new_var->SetBool(var->def->Exec({})->GetBoolVal());
			}
			break;
		case VarInstance:

			if (var->new_node != nullptr) {
				
				cls = var->new_node->Exec(std::vector<ZContextVar*>())->GetClassVal();
				new_var->SetClass(cls);
			
			}
			else {

				if (var->def != nullptr) {
					auto ge = var->def->Exec({});
					switch (ge->GetType()) {
					case VarType::VarCObj:
						new_var->SetCObj(ge);
						break;
					case VarType::VarInstance:
						new_var->SetClass(ge->GetClassVal());
						break;
					}
				}

			}

			break;
		}
		auto scope = ZScriptContext::CurrentContext->GetScope();//  owner->GetScope();
		scope->RegisterVar(new_var);

	}
	int b = 5;
	return nullptr;
}

void ZVarsNode::SetCodeOwner(ZCodeBodyNode* owner)
{
	mCodeOwner = owner;
}