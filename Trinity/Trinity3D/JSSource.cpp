#include "JSSource.h"

JSSource::JSSource(std::string path) {

    std::ifstream scriptFile(path);
    std::string script((std::istreambuf_iterator<char>(scriptFile)),
        std::istreambuf_iterator<char>());

    const char* source = script.c_str();
    size_t size = strlen(source) + 1;
    wchar_t* destination = new wchar_t[size];
    mbstowcs(destination, source, size);
    src = destination;
    len = script.length();

}

wchar_t* JSSource::GetSource() {

    return src;

}

int JSSource::GetLen() {

    return len;

}