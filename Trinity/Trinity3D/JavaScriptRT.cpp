#include "JavaScriptRT.h"

JavaScriptRT::JavaScriptRT() {


	JsCreateRuntime(JsRuntimeAttributeNone, nullptr, &runtime);
	JsCreateContext(runtime, &context);
	JsSetCurrentContext(context);
	printf("Set up Javascript runtime.\n");

}
void PrintObjectProperties(JsValueRef object) {
	JsValueRef propertyNames;
	JsErrorCode error = JsGetOwnPropertyNames(object, &propertyNames);
	if (error != JsNoError) {
		std::cerr << "Error getting property names" << std::endl;
		return;
	}

	unsigned int propertyCount;
	error = JsGetArrayLength(propertyNames, &propertyCount);
	if (error != JsNoError) {
		std::cerr << "Error getting property count" << std::endl;
		return;
	}

	for (unsigned int i = 0; i < propertyCount; i++) {
		JsValueRef propertyName;
		error = JsGetIndexedProperty(propertyNames, i, &propertyName);
		if (error != JsNoError) {
			std::cerr << "Error getting property name" << std::endl;
			return;
		}

		wchar_t propertyNameStr[100];
		size_t length;
		error = JsStringToPointer(propertyName, &propertyNameStr, &length);
		if (error != JsNoError) {
			std::cerr << "Error converting property name to string" << std::endl;
			return;
		}

		std::wcout << propertyNameStr << std::endl;
	}
}

JSVar* JavaScriptRT::Run(JSSource* src) {

	JsValueRef result;
	JsErrorCode error = JsRunScript(src->GetSource(),JS_SOURCE_CONTEXT_NONE, L"", &result);
	if (error != JsNoError) {
		std::cout << "An error occurred while running the script." << std::endl;
	}
	JsGetGlobalObject(&globalObject);

	return new JSVar(result);
}

JSClass* JavaScriptRT::GetClass(std::string name) {

	std::string className = name;
	std::wstring wClassName(className.begin(), className.end());
	const wchar_t* classNameStr = wClassName.c_str();

	JsPropertyIdRef classNameId;
	JsGetPropertyIdFromName(classNameStr, &classNameId);

	JsValueRef classConstructor;
	JsErrorCode c = JsGetProperty(globalObject,classNameId , &classConstructor);

	JsValueType type;
	if (JsGetValueType(classConstructor, &type) == JsNoError && type == JsFunction) {
		int yep = 1;
	}

	return new JSClass(classConstructor);

}