#pragma once
#include "SceneGraph.h"

//class SceneGraph;
class MonoRT;
class MonoDLL;
class ClassMono;

class TrinityGlobal
{
public:

	static SceneGraph* CurrentScene;
	static Node3D* ActiveNode;
	static MonoRT* Mono;
	static MonoDLL* MonoGame;
	static std::vector<ClassMono*> MonoClasses;
};

