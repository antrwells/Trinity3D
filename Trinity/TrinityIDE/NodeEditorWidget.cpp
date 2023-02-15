#include "NodeEditorWidget.h"
#include "qpushbutton.h"
#include "qlabel.h"
#include "qnumeric.h"
#include "qvector3d.h"
#include "qvector4d.h"
#include "qvector.h"
#include "Node3D.h"
#include "NodeEntity.h"
#include "NodeLight.h"
#include <QVBoxLayout>
#include "NodeCamera.h"


NodeEditorWidget::NodeEditorWidget(QWidget *parent)
	: CDockWidget("Node Editor",parent)
{
//	ui.setupUi(this);
	QPalette myPal;
	sThis = this;
	w_Prop = new PropEditor(this);
	w_Prop->setGeometry(0, 0, width(), height());
//	setAutoFillBackground(true);
// 	   set
// 
	//setPalette(myPal);
	//setAcceptDrops(true);
	setAcceptDrops(true);
}

NodeEditorWidget::~NodeEditorWidget()
{}

void NodeEditorWidget::SetNode(Node3D* node) {


	std::string name = "Node:" + std::string(node->GetName());// +"\n";

	w_Prop->SetNode(node);
	//update();
	//w_Prop->resize(width(), height());
	mEditNode = node;
	


}

void NodeEditorWidget::ReSet() {

//	SetNode(mEditNode);
	w_Prop->ReSet();

}

void NodeEditorWidget::resizeEvent(QResizeEvent* event)
{
	QSize size = event->size();
	int width = size.width();
	int height = size.height();
	w_Prop->resize(width, height);

//	w_Prop->layout()->setSpacing(5);

	// Perform actions based on the new size of the widget
	// ...

	// Don't forget to call the base implementation
	QWidget::resizeEvent(event);
}

NodeEditorWidget* NodeEditorWidget::sThis = nullptr;