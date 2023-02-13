#pragma once
#include <ChakraCore.h>
#include <fstream>
#include <iostream>

enum VarType {
	Int,Long,Float,Double,String,Pointer,Class
};

class JSVar
{
public:

	JSVar(JsValueRef ref);
	JSVar(int value);
	JsValueRef GetRef() {
		return j_ref;
	}
	VarType GetType();
	std::string GetString();
	int GetInt();
	float GetFloat();
	double GetDouble();

private:

	JsValueRef j_ref;

};

