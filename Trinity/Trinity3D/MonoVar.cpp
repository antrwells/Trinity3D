#include "MonoVar.h"
#include "MonoRT.h"

MonoVar::MonoVar(void* p,bool box)
{

	if (box) {
		m_box = mono_value_box(MonoRT::mThis->GetDomain(), mono_get_intptr_class(), p);
		m_isBoxed = true;
	}
	else {
		pp = p;
	}
}
int tv = 0;

MonoVar::MonoVar(int val) {

	tv = val;
	int* v1 = (int*)malloc(4);
	v1[0] = val;

	m_box = mono_value_box(MonoRT::mThis->GetDomain(), mono_get_int32_class(),(void*)v1);
	m_isBoxed = true;
}

MonoVar::MonoVar(long val) {

	tv = val;
	long* v1 = (long*)malloc(sizeof(long));
	v1[0] = val;

	m_box = mono_value_box(MonoRT::mThis->GetDomain(), mono_get_int64_class(), (void*)v1);
	m_isBoxed = true;
}

MonoVar::MonoVar(MonoObject* obj)
{

	m_box = obj;
	m_isBoxed = true;
}

MonoObject* MonoVar::GetObject() {

	return m_box;

}

int MonoVar::GetInt() {

	int bValue = *(int*)mono_object_unbox(m_box);
	return bValue;
}

float MonoVar::GetFloat() {

	float bValue = *(float*)mono_object_unbox(m_box);
	return bValue;
}

double MonoVar::GetDouble() {

	double bValue = *(int*)mono_object_unbox(m_box);
	return bValue;
}
long MonoVar::GetLong() {

	long bValue = *(long*)mono_object_unbox(m_box);
	return bValue;
}
short MonoVar::GetShort() {

	short bValue = *(short*)mono_object_unbox(m_box);
	return bValue;
}


char MonoVar::GetByte() {

	char bValue = *(char*)mono_object_unbox(m_box);
	return bValue;
}