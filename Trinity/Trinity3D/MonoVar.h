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

	MonoVar(void* pointer,bool box = false);
	MonoVar(int val);
	MonoVar(long val);
	MonoVar(MonoObject* obj);
	MonoObject* GetObject();
	int GetInt();
	float GetFloat();
	long GetLong();
	double GetDouble();
	char GetByte();
	short GetShort();
	bool IsBoxed() { return m_isBoxed; }
	void* GetPointer() { return pp; };
private:

	MonoObject* m_box;
	bool m_isBoxed = false;
	void* pp;

};

