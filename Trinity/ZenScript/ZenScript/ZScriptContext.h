#pragma once
#include "ZProgramNode.h"
#include <string>
#include <stack>
//#include "DataTypes.h"

#include "ZContextVar.h"
class ZContextScope;
class ZSystemFunctions;
class ZEnumNode;
class ZTransientNode;

class ZScriptContext
{
public:

	ZScriptContext();
	void SetupSystem();
	void AddNode(ZMainNode* node);
	ZClassNode* FindClass(std::string name);
	bool IsStaticClass(std::string name);
	bool IsStaticClass(size_t hash);
	bool IsEnum(size_t name);
	ZEnumNode* GetEnum(size_t name);
	ZClassNode* GetStaticClass(std::string name);
	ZClassNode* GetStaticClass(size_t name);

	ZClassNode* CreateInstance(std::string name,std::string instance_name, const std::vector<ZContextVar*>& params);
	void PushClass(ZClassNode* cls);
	void PopClass();
	ZClassNode* GetClass();
	ZContextVar* CallMethod(std::string name, std::string meth, const std::vector<ZContextVar*>& params);
	ZClassNode* FindInstance(std::string name);
	static ZContextScope* CurrentScope;
	static ZScriptContext* CurrentContext;
	void PushScope(ZContextScope* scope)
	{
		mScope.push(scope);
	}
	void PopScope() {
		mScope.pop();
	}
	ZContextScope* GetScope()
	{
		return mScope.top();
	}
	ZContextVar* RunLine(std::string code);
	void AddTransient(ZTransientNode* node);
	std::vector<ZTransientNode*> GetTransients();
	ZTransientNode* GetTransient(std::string name);
	void LoadLib(std::string name);
	ZSystemFunctions* GetSysFuncs();
private:

	ZSystemFunctions* mSysFuncs;
	std::vector<ZClassNode*> mClasses;
	std::vector<ZClassNode*> mStaticClasses;
	std::stack<ZClassNode*> mClassStack;
	std::vector<ZClassNode*> mInstances;
	std::vector<ZTransientNode*> mTransients;
	std::stack<ZContextScope*> mScope;
	std::vector<ZEnumNode*> mEnums;
	static bool mSysInit;
};

