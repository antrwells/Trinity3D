#include "ClassMono.h"
#include "ClassMethod.h"
#include "MonoRT.h"
#include "ClassProperty.h"

ClassMono::ClassMono(MonoClass* klass)
{

	m_class = klass;

}

ClassMono::ClassMono(MonoClass* klass, MonoObject* obj)
{
    m_class = klass;
    m_instance = obj;

}

ClassMethod* ClassMono::GetMethod(std::string name) {
    MonoMethod* method = mono_class_get_method_from_name(m_class,name.c_str(), 0);
    if (!method) {
        printf("Error getting method:");
        printf(name.c_str());
        printf("\n");
        return nullptr;
    }
    printf("Got Method:");
    printf(name.c_str());
    printf("\n");
    return new ClassMethod(this,method);

}

ClassMono* ClassMono::CreateInstance() {

    // Create an instance of the class
    MonoObject* instance = mono_object_new(MonoRT::GetDomain(), m_class);
    mono_runtime_object_init(instance);
    return new ClassMono(m_class, instance);



}

MonoObject* ClassMono::GetObject() {

    return m_instance;

}

ClassProperty* ClassMono::GetProperty(std::string name) {

    MonoProperty* property = mono_class_get_property_from_name(m_class,name.c_str());
   
    return new ClassProperty(this, property);


}

std::vector<ClassProperty*> ClassMono::GetProperties() {

    std::vector<ClassProperty*> list;

    void* iter = NULL;
    MonoProperty* property;

    while ((property = mono_class_get_properties(m_class, &iter))) {

        auto cp = new ClassProperty(this, property);
        list.push_back(cp);

    }

    return list;

}