#include "TrinityGlobal.h"

SceneGraph* TrinityGlobal::CurrentScene = nullptr;
Node3D* TrinityGlobal::ActiveNode = nullptr;
MonoRT* TrinityGlobal::Mono = nullptr;
MonoDLL* TrinityGlobal::MonoGame = nullptr;
std::vector<ClassMono*> TrinityGlobal::MonoClasses;