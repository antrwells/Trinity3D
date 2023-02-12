#include "ClassMethod.h"
#include "ClassMono.h"

ClassMethod::ClassMethod(ClassMono* klass,MonoMethod* method) {

	m_method = method;
	m_class = klass;

}

void ClassMethod::CallNoPars() {

	mono_runtime_invoke(m_method, m_class->GetObject(),nullptr, NULL);

}