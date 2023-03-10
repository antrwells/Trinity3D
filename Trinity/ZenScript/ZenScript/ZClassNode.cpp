#include "ZClassNode.h"
#include "ZMethodNode.h"
#include "ZContextScope.h"
#include "ZVarsNode.h"
#include <assert.h>
#include "ZExpressionNode.h"
#include "ZScriptContext.h"
#include "ZSignatureNode.h"
#include "ZSigParamNode.h"
#include "ZNewNode.h"
#include <unordered_map>
void ZClassNode::SetName(std::string name) {

	std::hash<std::string> hasher;

	mClassName = name;
	mHashName = hasher(name);


}

void ZClassNode::AddMethod(ZMethodNode* node)
{

	mMethods.push_back(node);

}

void ZClassNode::SetMethods(std::vector<ZMethodNode*> methods) {

	mMethods = methods;

}

void ZClassNode::AddMethods(std::vector<ZMethodNode*> methods)
{

	for (int i = 0; i < methods.size(); i++)
	{
		mMethods.push_back(methods[i]);
	}

}

std::vector<ZMethodNode*> ZClassNode::GetMethods() {

	return mMethods;

}

std::string ZClassNode::GetName() {

	return mClassName;

}

void ZClassNode::AddVars(ZVarsNode* node)
{

	mVars.push_back(node);

}

void ZClassNode::CreateScope() {

	mInstanceScope = new ZContextScope("Class:" + mClassName + " Instance");

}

void ZClassNode::PopulateScope() {

	for (int i = 0; i < mVars.size(); i++) {

		auto vars = mVars[i];

		auto names = vars->GetVars();
		auto type = vars->GetType();

		for (int j = 0; j < names.size(); j++)
		{

			ZContextVar* new_var = new ZContextVar(names[j]->name, type,vars->GetBaseType(),names[j]->comparer);

			if (names[j]->new_node != nullptr) {
				new_var->SetClass(names[j]->new_node->Exec(std::vector<ZContextVar*>())->GetClassVal());
			}
			else {
				auto def = names[j]->def;

				if (def == nullptr) {

				}
				else {
					auto def_exp = def->GetExpression();

					if (def_exp.mElements.size() > 0)
					{
						ZExpressionNode::RecvType = type;
						auto res = names[j]->def->Exec({});
						switch (type) {
						case VarType::VarInteger:
							new_var->SetInt(res->GetIntVal());
							break;
						case VarType::VarFloat:
							new_var->SetFloat(res->GetFloatVal());
							break;
						case VarType::VarCObj:
							new_var->SetCObj(res->GetCObj());
							break;
						case VarType::VarString:
							new_var->SetString(res->GetStringVal());
							break;
						case VarType::VarInstance:
							new_var->SetClass(res->GetClassVal());
							break;
						case VarType::VarBool:
							new_var->SetBool(res->GetBoolVal());
							break;
						}

						//new_var->SetInt(names[j]->def->Exec(std::vector<ZContextVar*>())->GetIntVal());
						//TODO
					}
				}
			}
			mInstanceScope->RegisterVar(new_var);
		
		}

	}

}

void ZClassNode::SetVars(std::vector<ZVarsNode*> vars)
{
	mVars = vars;
}

void ZClassNode::AddVars(std::vector<ZVarsNode*> vars)
{

	for (int i = 0; i < vars.size(); i++) {
		mVars.push_back(vars[i]);
	}

}

ZClassNode* ZClassNode::CreateInstance(std::string name, const std::vector<ZContextVar*>& params) {

	ZClassNode* new_cls = new ZClassNode;

	ZClassNode* p_cls = nullptr;
	new_cls->SetName(name);
	new_cls->SetMethods(mMethods);
	new_cls->SetVars(mVars);
	if (this->mInherits != "")
	{
		p_cls = ZScriptContext::CurrentContext->FindClass(this->mInherits);
		int bb = 5;
		new_cls->AddMethods(p_cls->GetMethods());
		new_cls->AddVars(p_cls->GetVarsVec());
	}

	


	


	new_cls->CreateScope();
	new_cls->PopulateScope();
	new_cls->SetBaseName(this->mClassName);
	if (new_cls->FindMethod(mHashName) != nullptr)
	{
		new_cls->CallMethod(mHashName,params);
	}

	return new_cls;

}

ZMethodNode* ZClassNode::FindMethod(size_t hash) {

	for (int i = 0; i < mMethods.size(); i++) {

		if (mMethods[i]->GetHash() == hash)
		{
			return mMethods[i];
		}

	}
	return nullptr;
	assert(false);
	return nullptr;

}

/*
ZMethodNode* ZClassNode::FindMethod(std::string name) {

	for (int i = 0; i < mMethods.size(); i++) {

		if (mMethods[i]->GetName() == name)
		{
			return mMethods[i];
		}

	}
	return nullptr;
	assert(false);
	return nullptr;

}
*/
std::hash<std::string> hasher;


ZContextVar* ZClassNode::CallMethod(size_t hash, const std::vector<ZContextVar*>& params)
{


	auto method = FindMethod(hash);

	auto new_scope = mInstanceScope->Clone();

	auto sig = method->GetSignature();


	std::vector<ZContextVar*> to_rem;
	auto pars = sig->GetParams();

	for (int i = 0; i < pars.size(); i++) {

		auto pa = pars[i];
		ZContextVar* v1 = new ZContextVar(pa->GetName(), pa->GetType(), pa->GetName(), false);
		switch (params[i]->GetType())
		{
		case VarBool:
			v1->SetBool(params[i]->GetBoolVal());
			break;
		case VarInteger:
			v1->SetInt(params[i]->GetIntVal());
			break;
		case VarFloat:
			v1->SetFloat(params[i]->GetFloatVal());
			break;
		case VarInstance:
			v1->SetClass(params[i]->GetClassVal());
			v1->SetBaseID(params[i]->GetBaseID());
			break;
		case VarCObj:
			v1->SetCObj(params[i]->GetCObj());
		case VarString:
			v1->SetString(params[i]->GetStringVal());
			break;
		}
		new_scope->RegisterVar(v1);

		to_rem.push_back(v1);
	}

	//method->SetScope(new_scope);
	//ZScriptContext::CurrentScope = method->GetScope();




	ZScriptContext::CurrentContext->PushScope(new_scope);
	method->SetClassOwner(this);
	ZScriptContext::CurrentContext->PushClass(this);
	auto res = method->Exec({});
	ZScriptContext::CurrentContext->PopClass();
	ZScriptContext::CurrentContext->PopScope();
	for (int i = 0; i < to_rem.size(); i++) {
		new_scope->RemoveVar(to_rem[i]);
	}
	return res;
}



ZContextVar* ZClassNode::CallMethod(std::string name, const std::vector<ZContextVar*>& params)
{

	
	auto method = FindMethod(hasher(name));
	
	auto new_scope = mInstanceScope->Clone();

	auto sig = method->GetSignature();


	std::vector<ZContextVar*> to_rem;
	auto pars = sig->GetParams();

	for (int i = 0; i < pars.size(); i++) {

		auto pa = pars[i];
		ZContextVar* v1 = new ZContextVar(pa->GetName(), pa->GetType(),pa->GetName(),params[i]->GetCompare());
		switch (params[i]->GetType())
		{
		case VarInteger:
			v1->SetInt(params[i]->GetIntVal());
			break;
		case VarFloat:
			v1->SetFloat(params[i]->GetFloatVal());
			break;
		case VarInstance:
			v1->SetClass(params[i]->GetClassVal());
			v1->SetBaseID(params[i]->GetBaseID());
			break;
		case VarCObj:
			v1->SetCObj(params[i]->GetCObj());
		case VarString:
			v1->SetString(params[i]->GetStringVal());
			break;
		}
		new_scope->RegisterVar(v1);

		to_rem.push_back(v1);
	}

	//method->SetScope(new_scope);
	//ZScriptContext::CurrentScope = method->GetScope();




	ZScriptContext::CurrentContext->PushScope(new_scope);
	method->SetClassOwner(this);
	ZScriptContext::CurrentContext->PushClass(this);
	auto res = method->Exec({});
	ZScriptContext::CurrentContext->PopClass();
	ZScriptContext::CurrentContext->PopScope();
	for (int i = 0; i < to_rem.size(); i++) {
		new_scope->RemoveVar(to_rem[i]);
	}
	return res;
}


void ZClassNode::SetBaseName(std::string name) {

	mBaseClassName = name;

}

ZContextVar* ZClassNode::FindVar(std::string name) {

	std::hash<std::string> hasher;
	return mInstanceScope->FindVar(hasher(name));

}
ZContextVar* ZClassNode::FindVar(size_t hash) {

	if (hash == 0) {
		printf("No hash\n");
		exit(1);

	}
	return mInstanceScope->FindVar(hash);

}

void ZClassNode::Bind() {

	//printf("Binding class.");


	for (int i = 0; i < mMethods.size(); i++) {

		mMethods[i]->SetClassOwner(this);
		mMethods[i]->Bind();

	}

}

std::vector<ZContextVar*> ZClassNode::GetVars() {

	return mInstanceScope->GetVars();

}


void ZClassNode::SetExtends(std::string cls)
{

	mInherits = cls;

}
ZMethodNode* ZClassNode::GetMethod(size_t hash) {

	for (int i = 0; i < mMethods.size(); i++)
	{
		if (mMethods[i]->GetHash() == hash) {
			return mMethods[i];
		}
	}
	return nullptr;

}
ZMethodNode* ZClassNode::GetMethod(std::string name) {

	for (int i = 0; i < mMethods.size(); i++)
	{
		if (mMethods[i]->GetName() == name) {
			return mMethods[i];
		}
	}
	return nullptr;

}