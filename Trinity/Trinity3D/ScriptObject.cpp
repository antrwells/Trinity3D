#include "pch.h"
#include "ScriptObject.h"
#include <ZClassNode.h>
#include "ZSource.h"
#include "ZParser.h"
#include "ZTokenizer.h"
#include "ZContextVar.h"
#include "ZProgramNode.h"
#include "ZScriptContext.h"

void ScriptObject::CallInit()
{

	mMainClass->CallMethod("Init", {});

}

void ScriptObject::CallUpdate() {

	mMainClass->CallMethod("Update", {});

}

void ScriptObject::CallUI() {

	mMainClass->CallMethod("UI", {});

}

void ScriptObject::CallRender() {

	mMainClass->CallMethod("Render", {});

}


std::vector<ZContextVar*> ScriptObject::GetVars() {

	return mMainClass->GetVars();


}

void ScriptObject::PushVars() {

	auto vars = mMainClass->GetVars();

	for (int i = 0; i < vars.size(); i++)
	{

		auto v = vars[i];
		
		v->Push();

		

	}



}

void ScriptObject::PopVars() {

	auto vars = mMainClass->GetVars();

	for (int i = 0; i < vars.size(); i++)
	{

		auto v = vars[i];

		v->Pop();



	}


}

ScriptContainer::ScriptContainer(std::string path) {

	
		auto src = new ZSource(path);
		ZTokenizer* toker = new ZTokenizer(src);
		auto stream = toker->Tokenize();
		auto parser = new ZParser(stream);
		mNode = parser->Parse();
		ZScriptContext::CurrentContext->AddNode(mNode);
	

}

ZClassNode* ScriptContainer::GetClass(std::string name) {

	return mNode->GetClass(name);

}