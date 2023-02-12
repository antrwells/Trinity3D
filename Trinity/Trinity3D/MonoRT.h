#pragma once
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/mono-config.h>
#include <mono/metadata/mono-debug.h>
#include <string>
#include <iostream>
#include <fstream>

class MonoDLL;

class MonoRT
{
public:

	MonoRT();
	MonoDLL* LoadDll(std::string dll);
	static MonoDomain* GetDomain()
	{
		return mThis->GetDom();
	}
	static MonoRT* mThis;
	MonoDomain* GetDom() {
		return m_domain;
	}


private:

	MonoDomain* m_domain;

};

