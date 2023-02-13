#pragma once
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/mono-config.h>
#include <mono/metadata/mono-debug.h>
#include <string>
#include <iostream>
#include <fstream>
class MonoVar
{
public:

	MonoVar(void* pointer);
	MonoVar(int val);
	MonoVar(MonoObject* obj);
	MonoObject* GetObject();
	int GetInt();
	float GetFloat();
	long GetLong();
	double GetDouble();
	char GetByte();
	short GetShort();


private:

	MonoObject* m_box;

};

