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
	static SceneGraph* GameScene;
	static Node3D* ActiveNode;

};

