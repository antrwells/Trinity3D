#include "PropEditor.h"
#include <QVBoxLayout>
#include "qlabel.h"
#include "qpushbutton.h"
#include "Node3D.h"
PropEditor::PropEditor(QWidget *parent)
	: QScrollArea(parent)
{
	ui.setupUi(this);
	QWidget* centralWidget = new QWidget;




	


	
	//dockWidget->setWidget(centralWidget);
}

PropEditor::~PropEditor()
{}

void PropEditor::SetNode(Node3D* node) {

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