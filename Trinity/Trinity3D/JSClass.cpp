#include "JSClass.h"

JSClass::JSClass(JsValueRef constructor) {

	construct = constructor;
	base = true;

}

JSClass* JSClass::CreateInstance(std::vector<JSVar*> vars) {

	JsValueRef instance;

	
	JsValueRef xref;
	JsIntToNumber(10,&xref)
		;
	//JsValueRef y = JsIntToNumber(20);
	JsValueRef args[] = { xref };

	std::cout << "Constructor: " << construct << std::endl;
	std::cout << "Argument count: " << 1 << std::endl;
	std::cout << "Argument: " << xref << std::endl;
	JsErrorCode error = JsCallFunction(construct, &xref, 1, &instance);

	if (error != JsNoError) {
		JsValueRef exception;
		if (JsGetAndClearException(&exception) == JsNoError) {
			// Output exception information here
		}
		else {
			std::cout << "An error occurred while calling the constructor, but no exception information was available." << std::endl;
		}
	}
	else {
		JSClass* res = new JSClass;
		res->SetInstance(instance);
		return res;
	}
	return nullptr;
	//return res;

}

JSVar* JSClass::GetProperty(std::string name) {

	std::string className = name;
	std::wstring wClassName(className.begin(), className.end());
	const wchar_t* classNameStr = wClassName.c_str();

	JsPropertyIdRef classNameId;
	JsGetPropertyIdFromName(classNameStr, &classNameId);

	JsValueRef xProp;
	JsGetProperty(instance,classNameId, &xProp);

	return new JSVar(xProp);

}