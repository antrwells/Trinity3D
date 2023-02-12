#pragma once
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/mono-config.h>
#include <mono/metadata/mono-debug.h>
#include <string>
#include <iostream>
#include <fstream>

class ClassMono;

class ClassMethod
{
public:

	ClassMethod(ClassMono * klass,MonoMethod* method);
	void CallNoPars();

private:

	MonoMethod* m_method;
	ClassMono* m_class;

};

