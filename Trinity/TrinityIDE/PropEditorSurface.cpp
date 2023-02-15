#include "PropEditorSurface.h"

#include "qlabel.h"
#include "qpushbutton.h"
#include "Node3D.h"
#include "ConsoleOutputWidget.h"
#include "qlineedit.h"
#include "ScriptObject.h"
#include "ZClassNode.h"
#include "NodeEditorWidget.h"


PropEditorSurface::PropEditorSurface(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setMouseTracking(true);
	//acceptDrops();
	setAcceptDrops(true);

}

std::string get_filename_without_extension(const std::string& path)
{
	// Find the position of the last directory separator character
	size_t last_slash_pos = path.find_last_of("/\\");

	// Extract the filename (including extension) from the path
	std::string filename = path.substr(last_slash_pos + 1);

	// Find the position of the last dot character in the filename
	size_t last_dot_pos = filename.find_last_of('.');

	if (last_dot_pos != std::string::npos)
	{
		// If there is a dot, remove everything after it
		filename = filename.substr(0, last_dot_pos);
	}

	return filename;
}

PropEditorSurface::~PropEditorSurface()
{}

void PropEditorSurface::SetNode(Node3D* node)
{

	t_Node = node;

	edit_y = 5;
	
	std::string name = "Node: ";

	auto name_lab = new QLabel(name.c_str(), this);
	name_lab->setGeometry(5, edit_y, 100, 20);

	auto name_edit = new QLineEdit(node->GetName().c_str(), this);
	name_edit->setGeometry(80, edit_y, 250, 20);

	connect(name_edit, &QLineEdit::textChanged, [=](const QString& text) {
		t_Node->SetName(text.toStdString().c_str());
	});

	edit_y += 30;
	name_lab->setParent(this);


//	for (int i = 0; i < 50; i++) {
		auto pe = AddVec3Editor("Position", node->GetPositionPtr());
		auto re = AddVec3Editor("Rotation", node->GetRotationEularPtr());
		auto se = AddVec3Editor("Scale", node->GetScalePtr());
		re->is_NodeRot = t_Node;
		pos = pe;
		rot = re;
		scale = se;

		auto scripts = t_Node->GetScripts();

		for (int i = 0; i < scripts.size(); i++) {

			auto s = scripts[i];

			auto name = s->mClsName;

			auto name_lab = new QLabel(name.c_str(), this);
			name_lab->setGeometry(5, edit_y, 100, 20);
			edit_y += 25;

			auto vars = scripts[i]->GetVars();

			for (int v = 0; v < vars.size(); v++)
			{




				auto var = vars[v];

				switch (var->GetTypeInt())
				{
				case 0:
				{
					int iv = var->GetIntVal();

					auto v_lab = new QLabel(var->GetName().c_str(), this);
					v_lab->setGeometry(5, edit_y, 100, 20);

					auto v_edit = new QSpinBox(this);
					v_edit->setGeometry(80, edit_y, 100, 20);
					edit_y += 25;

					v_edit->setValue(iv);

					//if (ImGui::DragInt(var->GetName().c_str(), &iv))
					//{
					intEdit* ie = new intEdit(v_edit, var);
					ints.push_back(ie);
					var->SetInt(iv);
				}
					break;
				case 1:
				{
					float fv = var->GetFloatVal();

					auto v_lab = new QLabel(var->GetName().c_str(), this);
					v_lab->setGeometry(5, edit_y, 100, 20);

					auto v_edit = new QDoubleSpinBox(this);
					v_edit->setGeometry(80, edit_y, 100, 20);
					edit_y +=25;

					v_edit->setValue(fv);

					//if (ImGui::DragFloat(var->GetName().c_str(), &fv))
					//{
					floatEdit* fe = new floatEdit(v_edit, var);
					floats.push_back(fe);
					var->SetFloat(fv);
					break;
				}
				case 2:
				{

					std::string sv = var->GetStringVal();

					auto v_lab = new QLabel(var->GetName().c_str(), this);
					v_lab->setGeometry(5, edit_y, 100, 20);

					auto v_edit = new QLineEdit(sv.c_str(), this);
					v_edit->setGeometry(80, edit_y, 250, 20);
					edit_y +=25;

					v_edit->setText(sv.c_str());

					stringEdit* se = new stringEdit(v_edit, var);
					strings.push_back(se);




				}
				break;
				case 8:
				{
					//bool editor
					bool bv = var->GetBoolVal();

					auto v_lab = new QLabel(var->GetName().c_str(), this);
					v_lab->setGeometry(5, edit_y, 100, 20);

					auto v_edit = new QCheckBox(this);
					v_edit->setGeometry(80, edit_y, 100, 20);
					edit_y += 25;
					v_edit->setChecked(bv);
					boolEdit* be = new boolEdit(v_edit, var);
					bools.push_back(be);

					int v = 1;
				}
					break;
				
				}







				}
			}

	//adjustSize();
	return;


	QWidget* parent_widget =this; // Get the parent widget
	QLayout* layout_to_remove = parent_widget->layout(); // Get the layout to remove
//	QLayoutItem* layout_item = nullptr;

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

vec3Edit* PropEditorSurface::AddVec3Editor(std::string name,float3* cur) {


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

	

	vec3Edit* c = new vec3Edit(name.c_str(), x_spinbox, y_spinbox, z_spinbox,cur);

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

void reset(vec3Edit* edit, float3 cur) {
	edit->x->setValue(cur.x);
	edit->y->setValue(cur.y);
	edit->z->setValue(cur.z);
}

void PropEditorSurface::ReSet() {

	reset(pos, t_Node->GetPosition());
	reset(rot, t_Node->GetRotationEular());
	reset(scale, t_Node->GetScale());

}

void PropEditorSurface::dropEvent(QDropEvent* event)
{
	if (event->mimeData()->hasText()) {

		if (event->mimeData()->property("type").toString() == QString("script"))
		{
			//	event->acceptProposedAction();

			//setText(event->mimeData()->text());
			event->acceptProposedAction();
			std::string sc_path = event->mimeData()->text().toStdString();
			int a = 5;

			auto node = TrinityGlobal::ActiveNode;

			auto s_name = get_filename_without_extension(sc_path);


			int vvv = 5;


			node->AddScript(sc_path, s_name);
			NodeEditorWidget::sThis->SetNode(t_Node);
			//SetNode(t_Node);
			;
			//	auto scene = TrinityGlobal::CurrentScene;

			//	auto node = scene->ReadNodeFromFile(std::string(event->mimeData()->text().toStdString()));

			//	scene->AddNode(node);

		}

	}
}