#pragma once
#include "ZScriptNode.h"
#include <string>


class ZClassNode;

class ZMainNode : ZScriptNode
{
public:


	void AddClass(ZClassNode* node);
	void AddStaticClass(ZClassNode* node);
	std::vector<ZClassNode*> GetClasses();
	std::vector<ZClassNode*> GetStaticClasses();
	ZClassNode* GetClass(std::string name);

private:

	std::vector<ZClassNode*> mClasses;
	std::vector<ZClassNode*> mStaticClasses;

};

