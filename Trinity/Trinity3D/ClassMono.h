#pragma once
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/mono-config.h>
#include <mono/metadata/mono-debug.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
class ClassMethod;
class ClassProperty;

class ClassMono
{
public:

	ClassMono(MonoClass* klass);
	ClassMono(MonoClass* klass, MonoObject* obj);
	ClassMethod* GetMethod(std::string name,int pars);
	ClassMono* CreateInstance();
	MonoObject* GetObject();
	ClassProperty* GetProperty(std::string name);
	std::vector<ClassProperty*> GetProperties(bool parents);
	std::string GetName();
	std::string GetParentName();

private:

	MonoClass* m_class = nullptr;
	MonoObject* m_instance = nullptr;
};

