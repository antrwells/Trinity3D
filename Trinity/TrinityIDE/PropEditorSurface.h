#pragma once

#include "ui_PropEditorSurface.h"
#include <QWidget>
#include "QDirect3D12Widget.h"
#include "qspinbox.h"
#include "Texture2D.h"
#include "SmartDraw.h"
#include "qdrag.h"
#include <QDrag>
#include "qmimedata.h"
#include "TrinityGlobal.h"
#include "SceneGraph.h"
#include "Node3D.h"
#include "VString.h"
#include <string>

std::string get_filename_without_extension(const std::string& path);
struct vec3Edit
{
	std::string name;
	QDoubleSpinBox* x, * y, * z;
	float3* real_val;
	Node3D* is_NodeRot = nullptr;
	vec3Edit()
	{

	}
	vec3Edit(const std::string& name, QDoubleSpinBox* x, QDoubleSpinBox* y, QDoubleSpinBox* z,float3* real) :
		name(name), x(x), y(y), z(z)
	{
		real_val = real;
		x->setValue(real[0].x);
		y->setValue(real[0].y);
		z->setValue(real[0].z);

		QObject::connect(x, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
			[this](double value) { changed(value); });
		QObject::connect(y, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
			[this](double value) { changed(value); });
		QObject::connect(z, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
			[this](double value) { changed(value); });
		


	}


	void changed(double v) {
		//int a = 5;
		real_val[0] = float3(x->value(), y->value(), z->value());
		if (is_NodeRot!=nullptr) {

			is_NodeRot->SetRotationEular(real_val[0]);

		}
	};
};

class PropEditorSurface : public QWidget
{
	Q_OBJECT

public:
	PropEditorSurface(QWidget *parent = nullptr);
	~PropEditorSurface();
	void SetNode(Node3D* node);
	void ReSet();
	vec3Edit* AddVec3Editor(std::string name,float3 *cur);

protected:
	void dragEnterEvent(QDragEnterEvent* event) override
	{
		if (event->mimeData()->hasText()) {
			if (event->mimeData()->property("type").toString() == QString("script"))
			{
				event->acceptProposedAction();
			}
		}
	}

	void dragMoveEvent(QDragMoveEvent* event) override
	{
		if (event->mimeData()->hasText()) {
			if (event->mimeData()->property("type").toString() == QString("script"))
			{
				event->acceptProposedAction();
			}
		}
	}

	void dropEvent(QDropEvent* event)
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


				node->AddScript(sc_path,s_name);
			//	auto scene = TrinityGlobal::CurrentScene;

			//	auto node = scene->ReadNodeFromFile(std::string(event->mimeData()->text().toStdString()));

			//	scene->AddNode(node);

			}

		}
	}

private:
	Ui::PropEditorSurfaceClass ui;
	Node3D* t_Node;
	int edit_y = 20;
	QSpinBox* pos_X, * pos_Y, * pos_Z;
	QSpinBox* scale_X, * scale_Y, * scale_Z;
	QSpinBox* rot_X,*rot_Y,*rot_Z;
	vec3Edit* pos,* rot,* scale;

};
