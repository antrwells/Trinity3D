#include "MonoRT.h"
#include "MonoDLL.h"

MonoRT* MonoRT::mThis = nullptr;

MonoRT::MonoRT() {

	mono_config_parse(NULL);
	m_domain = mono_jit_init("Trinity_Domain");
    mThis = this;


}

MonoDLL* MonoRT::LoadDll(std::string path) {

    MonoAssembly* assembly = mono_domain_assembly_open(m_domain,path.c_str());
    if (!assembly) {
        printf("Error loading assembly:");
        printf(path.c_str());
        printf("\n");
        return nullptr;
    }
    printf("Loaded dll:");
    printf(path.c_str());
    printf("\n");

    return new MonoDLL(assembly);

}