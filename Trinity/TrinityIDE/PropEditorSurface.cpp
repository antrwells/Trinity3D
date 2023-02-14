#include "PropEditorSurface.h"

#include "qlabel.h"
#include "qpushbutton.h"
#include "Node3D.h"
#include "ConsoleOutputWidget.h"


PropEditorSurface::PropEditorSurface(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	

}

PropEditorSurface::~PropEditorSurface()
{}

void PropEditorSurface::SetNode(Node3D* node)
{

	t_Node = node;

	edit_y = 5;
	
	std::string name = "Node: " + std::string(node->GetName());


	auto name_lab = new QLabel(name.c_str(), this);
	name_lab->setGeometry(5, edit_y, 100, 20);
	edit_y += 30;
	name_lab->setParent(this);


//	for (int i = 0; i < 50; i++) {
		auto pe = AddVec3Editor("Position", node->GetPosition());
		auto re = AddVec3Editor("Rotation", float3(0, 0, 0));
		auto se = AddVec3Editor("Scale", node->GetScale());
		pos = pe;
		rot = re;
		scale = se;
	adjustSize();
	return;


	QWidget* parent_widget =this; // Get the parent widget
	QLayout* layout_to_remove = parent_widget->layout(); // Get the layout to remove
	QLayoutItem* layout_item = nullptr;

	/*
	if (layout_to_remove != nullptr) {
	
		
		// Take and delete all items in the layout
		while ((layout_item = layout_to_remove->takeAt(0)) != nullptr) {
			delete layout_item->widget();
			delete layout_item;
		}

		// Remove the layout from the parent widget and delete it
		delete layout_to_remove;
		parent_widget->setLayout(nullptr);
	}

	delete layout();
	*/
	//---
	//return;
	adjustSize();

	update();

}
int inf = 0;

vec3Edit PropEditorSurface::AddVec3Editor(std::string name,float3 cur) {


	//auto row = new QHBoxLayout();


	auto name_lab = new QLabel(name.c_str(), this);
	name_lab->setGeometry(5, edit_y, 80, 20);

	auto x_lab = new QLabel("X:",this);

	QDoubleSpinBox* x_spinbox = new QDoubleSpinBox(this);
	x_spinbox->setRange(-10000, 10000);

	x_spinbox->setSingleStep(0.1);

	x_lab->setGeometry(70, edit_y, 40, 20);
	x_spinbox->setGeometry(85, edit_y, 80, 20);
	

	auto y_lab = new QLabel("Y:", this);
	QDoubleSpinBox* y_spinbox = new QDoubleSpinBox(this);
	y_spinbox->setRange(-10000, 10000);


	y_spinbox->setSingleStep(0.1);

	y_lab->setGeometry(170, edit_y, 40, 20);
	y_spinbox->setGeometry(185, edit_y, 80, 20);

	//
	auto z_lab = new QLabel("Z:", this);
	QDoubleSpinBox* z_spinbox = new QDoubleSpinBox(this);
	z_spinbox->setRange(-10000, 10000);


	z_spinbox->setSingleStep(0.1);

	z_lab->setGeometry(270, edit_y, 40, 20);
	z_spinbox->setGeometry(285, edit_y, 80, 20);
	
	edit_y += 25;

//	nlayout->addWidget(x_spinbox);
	//x_spinbox->setValue(cur.x);

	vec3Edit c;
	c.x = x_spinbox;
	c.y = y_spinbox;
	c.z = z_spinbox;


	return c;
	/*
	nlayout->addWidget(new QLabel("Y:"));
	QDoubleSpinBox* y_spinbox = new QDoubleSpinBox();
	y_spinbox->setRange(-1000, 1000);
	y_spinbox->setSingleStep(0.1);
	nlayout->addWidget(y_spinbox);
	y_spinbox->setValue(cur.y);

	nlayout->addWidget(new QLabel("Z:"));
	QDoubleSpinBox* z_spinbox = new QDoubleSpinBox();
	z_spinbox->setRange(-1000, 1000);
	z_spinbox->setSingleStep(0.1);
	nlayout->addWidget(z_spinbox);
	z_spinbox->setValue(cur.z);

	lay->addLayout(nlayout);
	update();
	nlayout->update();
	*/
}

void reset(vec3Edit edit, float3 cur) {
	edit.x->setValue(cur.x);
	edit.y->setValue(cur.y);
	edit.z->setValue(cur.z);
}

void PropEditorSurface::ReSet() {

	reset(pos, t_Node->GetPosition());
	reset(rot ,float3(0,0,0));
	reset(scale, t_Node->GetScale());

}