// MonoTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/mono-config.h>
#include <mono/metadata/mono-debug.h>
#include <string>
#include <iostream>
#include <fstream>
#include "MonoRT.h"
#include "MonoDLL.h"
#include "ClassMono.h"
#include "ClassMethod.h"
#include "ClassProperty.h"

int main()

{
    // Initialize the Mono runtime

    MonoRT* rt = new MonoRT;

    MonoDLL* dll = rt->LoadDll("GameNet.dll/GameNet.dll");

    auto classes = dll->GetClasses();

    for (int i = 0; i < classes.size(); i++) {

        printf("Class:");
        printf(classes[i]->GetName().c_str());
        printf("\n");
        printf("Extends:");
        printf(classes[i]->GetParentName().c_str());
        printf("\n");

    }

    auto cls = dll->GetClass("Game", "TestMod");

    auto inst = cls->CreateInstance();

    auto meth = inst->GetMethod("Hey");

    meth->CallNoPars();



    auto prop = inst->GetProperty("MyValue");

    prop->SetInt(355);

    printf("V:%d\n", prop->GetInt());

    printf("Name:");
    printf(prop->GetName().c_str());
    printf("\n");

    printf("Type:");
    printf(PropTypeEnglish(prop->GetType()).c_str());
    printf("\n");

    printf("---------------------\n");
    auto plist = inst->GetProperties(true);
    for (int i = 0; i < plist.size(); i++) {
        auto name = plist[i]->GetName();
        auto type = PropTypeEnglish(plist[i]->GetType());
        printf("Name:");
        printf(name.c_str());
        printf("  Type:");
        printf(type.c_str());
        printf("\n");
    }

    printf("V:%f\n", plist[2]->GetSingle());

    plist[2]->SetSingle(99);

    printf("V:%f\n", plist[2]->GetSingle());

    while (true) {};
    //
    return 1;
    mono_config_parse(NULL);
    MonoDomain* domain = mono_jit_init("MyDomain");

    // Load the pre-compiled .NET DLL
    MonoAssembly* assembly = mono_domain_assembly_open(domain, "TestLib.dll");
    if (!assembly) {
        printf("Error loading assembly\n");
        return 1;
    }

    // Get the class from the assembly
    MonoImage* image = mono_assembly_get_image(assembly);
    MonoClass* klass = mono_class_from_name(image, "TestLib", "Class1");
    if (!klass) {
        printf("Error getting class\n");
        return 1;
    }

    // Get the method from the class
    MonoMethod* method = mono_class_get_method_from_name(klass, "Hey", 0);
    if (!method) {
        printf("Error getting method\n");
        return 1;
    }

    // Create an instance of the class
    MonoObject* instance = mono_object_new(domain, klass);
    mono_runtime_object_init(instance);

    MonoProperty* property = mono_class_get_property_from_name(klass, "MyValue");
    MonoObject* propertyValue = mono_property_get_value(property, instance, NULL, NULL);

    void* params[1];
    MonoObject* value = mono_property_get_value(property,instance, params, NULL);
    int intValue = *(int*)mono_object_unbox(value);

    printf("V:%d\n", intValue);

    // Invoke the method on the instance
    //void* params[3];
    mono_runtime_invoke(method, instance, params, NULL);

     value = mono_property_get_value(property, instance, params, NULL);
    intValue = *(int*)mono_object_unbox(value);

    printf("V2:%d\n", intValue);

    void* iter = NULL;
    while ((property = mono_class_get_properties(klass, &iter))) {
        const char* property_name = mono_property_get_name(property);
        MonoMethod* get_method = mono_property_get_get_method(property);
        MonoMethodSignature* signature = mono_method_signature(get_method);
        MonoType* type = mono_signature_get_return_type(signature);
        printf("P:");
        printf(property_name);
        printf("\n");
        printf("Type:");
        printf(mono_type_get_name(type));
        printf("\n");
    }

    // Clean up the Mono runtime
    mono_jit_cleanup(domain);
    return 0;


    while (true);

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
