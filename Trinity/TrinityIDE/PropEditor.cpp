#include "PropEditor.h"
#include <QVBoxLayout>
#include "qlabel.h"
#include "qpushbutton.h"
#include "Node3D.h"
#include <QResizeEvent>
PropEditor::PropEditor(QWidget *parent)
	: QScrollArea(parent)
{
	ui.setupUi(this);
	//QWidget* centralWidget = new QWidget;




	w_PropSurface = new PropEditorSurface();

	//setWidget(w_PropSurface);
	
	//dockWidget->setWidget(centralWidget);
}

PropEditor::~PropEditor()
{}

void PropEditor::ReSet() {

	w_PropSurface->ReSet();

}

void PropEditor::SetNode(Node3D* node) {


	w_PropSurface->setParent(nullptr);

	w_PropSurface = new PropEditorSurface;

	w_PropSurface->SetNode(node);
	
	setWidget(w_PropSurface);
	show();

	//w_PropSurface->adjustSize();

	//show();
    
//	adjustSize();
///	w_PropSurface->adjustSize();
	//adjustSize();

	return;

	QVBoxLayout* layout = new QVBoxLayout;

	//QLabel* label1 = new QLabel("Label 1");
//	QLabel* label2 = new QLabel("Label 2");



	
	std::string name = "Node:" + std::string(node->GetName());

	QLabel* name_l = new QLabel(name.c_str());

	//	QPushButton * button = new QPushButton(name);
	layout->setSpacing(0);
	//label1->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::);

	layout->addWidget(name_l);
	
	//setWidget(layout);


	setLayout(layout);

}


void PropEditor::resizeEvent(QResizeEvent* event)
{
	QSize size = event->size();
	int width = size.width();
	int height = size.height();
	//w_PropSurface->resize(width, height);
	

	//	w_Prop->layout()->setSpacing(5);


		// Perform actions based on the new size of the widget
		// ...

		// Don't forget to call the base implementation
	QWidget::resizeEvent(event);
}
