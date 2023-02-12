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

class MonoDLL
{
public:
	MonoDLL(MonoAssembly* assembly);
	ClassMono* GetClass(std::string n_space,std::string name);

private:

	MonoAssembly* m_assembly;
	MonoImage* m_image;
};

