#include "ClassMethod.h"
#include "ClassMono.h"
#include "MonoRT.h"

ClassMethod::ClassMethod(ClassMono* klass,MonoMethod* method) {

	m_method = method;
	m_class = klass;

}

MonoVar* ClassMethod::CallNoPars() {

	mono_runtime_invoke(m_method, m_class->GetObject(),nullptr, NULL);
	return nullptr;
}

MonoVar* ClassMethod::Call(std::vector<MonoVar*> vars)
{
	
	std::vector<MonoObject*> arr;

	


	void** dataArray = new void* [vars.size()];
	for (int i = 0; i < vars.size(); i++) {

		if (vars[i]->IsBoxed()) {
			dataArray[i] = vars[i]->GetObject();
		}
		else {
			dataArray[i] = vars[i]->GetPointer();
		}
	}

	return new MonoVar(mono_runtime_invoke(m_method, m_class->GetObject(),dataArray, NULL));
	return nullptr;
}