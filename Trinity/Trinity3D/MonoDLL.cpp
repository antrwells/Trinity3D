#include "MonoDLL.h"
#include "ClassMono.h"

MonoDLL::MonoDLL(MonoAssembly* assembly) {

	m_assembly = assembly;
	m_image = mono_assembly_get_image(assembly);

}

ClassMono* MonoDLL::GetClass(std::string n_space,std::string name) {

    MonoClass* klass = mono_class_from_name(m_image,n_space.c_str(),name.c_str());
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

//int MONO_TOKEN_TYPE_DEF = 0x02000000;



std::vector<ClassMono*> MonoDLL::GetClasses() {

    std::vector<ClassMono*> list;

	int num_types = mono_image_get_table_rows(m_image, MONO_TABLE_TYPEDEF);

    //MonoClass* iter = mono_image_get_classes(m_image, NULL);
	for (int i = 0; i < num_types; i++) {
		auto cls =  mono_class_get(m_image, i+1 | MONO_TOKEN_TYPE_DEF);
		
		ClassMono* nc = new ClassMono(cls);
		list.push_back(nc);
	}

    return list;

}

