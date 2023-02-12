#include "MonoDLL.h"
#include "ClassMono.h"

MonoDLL::MonoDLL(MonoAssembly* assembly) {

	m_assembly = assembly;
	m_image = mono_assembly_get_image(assembly);

}

ClassMono* MonoDLL::GetClass(std::string n_space,std::string name) {

    MonoClass* klass = mono_class_from_name(m_image, "TestLib", "Class1");
    if (!klass) {
        printf("Error getting class:");
        printf(name.c_str());
        printf("\n");
        return nullptr;
    }

    printf("Got Class:");
    printf(name.c_str());
    printf("\n");

    return new ClassMono(klass);

}
