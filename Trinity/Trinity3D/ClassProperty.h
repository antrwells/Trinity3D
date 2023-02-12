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

enum PropType {
	
	Int32,Int64,Single,Double,Int16,Byte,Array,List,Object


};

std::string PropTypeEnglish(PropType type);

class ClassProperty
{
public:

	ClassProperty(ClassMono* klass, MonoProperty* property);
	int GetInt();
	float GetSingle();
	double GetDouble();
	short GetShort();
	long GetLong();
	char GetByte();
	void SetInt(int value);
	void SetSingle(float value);
	void SetDouble(double value);
	void SetShort(short value);
	void SetLong(long value);
	void SetByte(char value);
	PropType GetType();
	std::string GetName();

private:

	PropType m_type;
	ClassMono* m_class;
	MonoProperty* m_property;

};

