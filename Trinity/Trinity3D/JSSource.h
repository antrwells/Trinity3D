#pragma once
#include <string>
#include <ChakraCore.h>
#include <fstream>
#include <iostream>

class JSSource
{
public:

	JSSource(std::string path);
	wchar_t* GetSource();
	int GetLen();
private:

	wchar_t* src;
	int len = 0;

};

