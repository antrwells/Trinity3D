#pragma once
#include "ChakraCore.h"
#include <vector>
#include "JSVar.h"
class JSClass
{
public:

	JSClass() {};
	JSClass(JsValueRef constructor);
	JSClass* CreateInstance(std::vector<JSVar*> pars);
	void SetInstance(JsValueRef inst)
	{
		instance = inst;
	}

	JSVar* GetProperty(std::string name);

private:

	bool base = true;
	JsValueRef construct;
	JsValueRef instance;

};

