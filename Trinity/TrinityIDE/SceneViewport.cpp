#include "SceneViewport.h"

SceneViewport::SceneViewport(QWidget *parent)
	: QDirect3D12Widget(parent)
{
	ui.setupUi(this);

}

SceneViewport::~SceneViewport()
{}
