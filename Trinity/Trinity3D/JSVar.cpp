#include "JSVar.h"
#include <locale>
#include <codecvt>

JSVar::JSVar(JsValueRef ref) {

	j_ref = ref;

}

JSVar::JSVar(int value) {

	JsIntToNumber(value, &j_ref);

}

VarType JSVar::GetType() {

	JsValueType valueType;
	JsGetValueType(j_ref, &valueType);

	switch (valueType) {
		case JsNumber:
			return Int;
	}


}

std::string JSVar::GetString() {

	JsValueRef stringValue;
	JsConvertValueToString(j_ref, &stringValue);
	const wchar_t* stringData;
	size_t stringLength;
	JsStringToPointer(stringValue, &stringData, &stringLength);

	std::wstring wstring(stringData);

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;
	std::string string = convert.to_bytes(wstring);

	return string;
	//std::string string(charString);
}

int JSVar::GetInt() {

	int value;
	JsNumberToInt(j_ref, &value);
	return value;

}

float JSVar::GetFloat() {

	double v = 0;
	JsNumberToDouble(j_ref, &v);
	return (float)v;
}

double JSVar::GetDouble() {

	double v = 0;
	JsNumberToDouble(j_ref, &v);
	return v;

}