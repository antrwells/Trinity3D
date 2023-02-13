#pragma once
#include "ChakraCore.h"
#include <fstream>
#include <iostream>
#include <string>
#include "JSVar.h"
#include "JSSource.h"
#include "JSClass.h"
class JavaScriptRT
{
public:

	JavaScriptRT();
	JSVar* Run(JSSource* src);
	JSClass* GetClass(std::string name);

private:

	JsRuntimeHandle runtime;
	JsContextRef context;
	JsValueRef globalObject;
};

