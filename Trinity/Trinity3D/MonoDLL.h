#pragma once
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/mono-config.h>
#include <mono/metadata/mono-debug.h>
#include <mono/metadata/image.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/class.h>
#include <mono/metadata/metadata.h>
#include <mono/metadata/object.h>
#include <mono/metadata/reflection.h>
#include <mono/metadata/row-indexes.h>
#include <mono/metadata/tokentype.h>
#include <mono/metadata/sgen-bridge.h>
#include <string>

#include <iostream>
#include <fstream>
#include <vector>

class ClassMono;

class MonoDLL
{
public:
	MonoDLL(MonoAssembly* assembly);
	ClassMono* GetClass(std::string n_space,std::string name);
	std::vector<ClassMono*> GetClasses();


private:

	MonoAssembly* m_assembly;
	MonoImage* m_image;
};

