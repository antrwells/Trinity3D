#include "ClassProperty.h"
#include "ClassMono.h"


ClassProperty::ClassProperty(ClassMono* klass, MonoProperty* property) {

	m_class = klass;
	m_property = property;

}

int ClassProperty::GetInt() {


	//MonoObject* propertyValue = mono_property_get_value(m_property,m_class->GetObject(), NULL, NULL);
	MonoObject* value = mono_property_get_value(m_property,m_class->GetObject(), NULL, NULL);
	int intValue = *(int*)mono_object_unbox(value);
	return intValue;

}

float ClassProperty::GetSingle() {


	//MonoObject* propertyValue = mono_property_get_value(m_property,m_class->GetObject(), NULL, NULL);
	MonoObject* value = mono_property_get_value(m_property, m_class->GetObject(), NULL, NULL);
	float fValue = *(float*)mono_object_unbox(value);
	return fValue;

}

double ClassProperty::GetDouble() {


	//MonoObject* propertyValue = mono_property_get_value(m_property,m_class->GetObject(), NULL, NULL);
	MonoObject* value = mono_property_get_value(m_property, m_class->GetObject(), NULL, NULL);
	int dValue = *(double*)mono_object_unbox(value);
	return dValue;

}

short ClassProperty::GetShort() {


	//MonoObject* propertyValue = mono_property_get_value(m_property,m_class->GetObject(), NULL, NULL);
	MonoObject* value = mono_property_get_value(m_property, m_class->GetObject(), NULL, NULL);
	int sValue = *(short*)mono_object_unbox(value);
	return sValue;

}

long ClassProperty::GetLong() {


	//MonoObject* propertyValue = mono_property_get_value(m_property,m_class->GetObject(), NULL, NULL);
	MonoObject* value = mono_property_get_value(m_property, m_class->GetObject(), NULL, NULL);
	int lValue = *(long*)mono_object_unbox(value);
	return lValue;

}

char ClassProperty::GetByte() {


	//MonoObject* propertyValue = mono_property_get_value(m_property,m_class->GetObject(), NULL, NULL);
	MonoObject* value = mono_property_get_value(m_property, m_class->GetObject(), NULL, NULL);
	int bValue = *(char*)mono_object_unbox(value);
	return bValue;

}


void ClassProperty::SetInt(int value) {
	//vv = value;
	void* args[1];
	args[0] = &value;
	mono_property_set_value(m_property, m_class->GetObject(), args, nullptr);
}

void ClassProperty::SetSingle(float value) {
	//vv = value;
	void* args[1];
	args[0] = &value;
	mono_property_set_value(m_property, m_class->GetObject(), args, nullptr);
}

void ClassProperty::SetDouble(double value) {
	//vv = value;
	void* args[1];
	args[0] = &value;
	mono_property_set_value(m_property, m_class->GetObject(), args, nullptr);
}


void ClassProperty::SetShort(short value) {
	//vv = value;
	void* args[1];
	args[0] = &value;
	mono_property_set_value(m_property, m_class->GetObject(), args, nullptr);
}

void ClassProperty::SetLong(long value) {
	//vv = value;
	void* args[1];
	args[0] = &value;
	mono_property_set_value(m_property, m_class->GetObject(), args, nullptr);
}

void ClassProperty::SetByte(char value) {
	//vv = value;
	void* args[1];
	args[0] = &value;
	mono_property_set_value(m_property, m_class->GetObject(), args, nullptr);
}

PropType ClassProperty::GetType() {

	MonoMethod* get_method = mono_property_get_get_method(m_property);
	MonoMethodSignature* signature = mono_method_signature(get_method);
	MonoType* type = mono_signature_get_return_type(signature);
	std::string name(mono_type_get_name(type));

	if (name == "System.Int32") {
		return PropType::Int32;
	}
	if (name == "System.Int64")
	{
		return PropType::Int64;
	}

	if (name == "System.Single")
	{
		return PropType::Single;
	}

	if (name == "System.Double")
	{
		return PropType::Double;
	}

	if (name == "System.Int64")
	{
		return PropType::Int64;
	}

	if (name == "System.Int16") {
		return PropType::Int16;
	}

	if (name == "System.Byte")
	{
		return PropType::Byte;
	}
	return PropType::Unknown;
	return PropType::Int32;

}

std::string ClassProperty::GetName() {

	const char* property_name = mono_property_get_name(m_property);
	return std::string(property_name);

}

std::string PropTypeEnglish(PropType type) {

	switch (type) {
	case Int32:
		return "Int32";
	case Int16:
		return "Int16";
	case Single:
		return "Single";
	case Double:
		return "Double";
	case Int64:
		return "Long";
	case Byte:
		return "Byte";

	}
	return "Unknown";

}