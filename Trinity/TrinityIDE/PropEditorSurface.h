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
#include "ZContextVar.h"
#include "qlineedit.h"
#include "qcheckbox.h"
#include "ZClassNode.h"
#include "qcombobox.h"



std::string get_filename_without_extension(const std::string& path);


struct scvec3Edit {
	

};

struct comboEdit {

	QComboBox* cb;
	void* val;
	comboEdit(QComboBox* b, void* v) {
		cb = b;
		val = v;
		QObject::connect(b, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
						[this](int value) { changed(value); });
	}
	void changed(int value) {
		//var->SetInt(value);
		int* v = (int*)val;
		v[0] = value;
	}



};

//boolEdit class
struct boolEdit
{
	QCheckBox* ib;
	ZContextVar* var;
	bool* cur = nullptr;
	boolEdit(QCheckBox* b, bool* c) {
		ib = b;
		cur = c;
		QObject::connect(b, &QCheckBox::stateChanged,
			[this](bool value) { changed(value); });
	}
	boolEdit(QCheckBox* b, ZContextVar* v)
	{
		ib = b;
		var = v;
		QObject::connect(b, &QCheckBox::stateChanged,
						[this](bool value) { changed(value); });
	}
	void changed(bool value) {
		if (cur != nullptr) {
			cur[0] = value;
		}
		else {
			var->SetBool(value);
		}
	}
};


struct stringEdit
{
	QLineEdit* ib;
	ZContextVar* var;
	stringEdit(QLineEdit* b, ZContextVar* v)
	{
		ib = b;
		var = v;
		QObject::connect(b, &QLineEdit::textChanged,
						[this](const QString& value) { changed(value); });
	}
	void changed(const QString& value) {
		var->SetString(value.toStdString());
	}
};

struct intEdit
{
	QSpinBox* ib;
	ZContextVar* var;
	intEdit(QSpinBox* b, ZContextVar* v)
	{
		ib = b;
		var = v;
		QObject::connect(b, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
			[this](int value) { changed(value); });
	}
	void changed(int value) {
		var->SetInt(value);
	}
};


struct floatEdit
{
	QDoubleSpinBox* ib;
	ZContextVar* var;
	float* cur = nullptr;
	floatEdit(QDoubleSpinBox* b, float* c) {
		cur = c;
		ib = b;
		QObject::connect(b, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
			[this](double value) { changed(value); });

	}
	floatEdit(QDoubleSpinBox* b, ZContextVar* v)
	{
		ib = b;
		var = v;
		
		QObject::connect(b, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
			[this](double value) { changed(value); });
	}
	void changed(double value) {
		if (cur != nullptr) {
			cur[0] = (float)value;
		}
		else {
			var->SetFloat(value);
		}
	}
};


struct vec3Edit
{
	std::string name;
	QDoubleSpinBox* x, * y, * z;
	float3* real_val;
	Node3D* is_NodeRot = nullptr;
	ZContextVar* var = nullptr;
	bool block = false;
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
		if (var != nullptr) {
			auto i_cls = var->GetClassVal();
			i_cls->FindVar("x")->SetFloat(x->value());
			i_cls->FindVar("y")->SetFloat(y->value());
			i_cls->FindVar("z")->SetFloat(z->value());
			return;
		}
		real_val[0] = float3(x->value(), y->value(), z->value());
		if (is_NodeRot!=nullptr) {

			if (!block) {
				is_NodeRot->SetRotationEular(real_val[0]);
			}
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
	floatEdit* AddFloatEditor(std::string name, float* cur);
	boolEdit* AddBoolEditor(std::string name, bool* cur);
	comboEdit* AddComboEditor(std::string name, void* cur);
	void AddItem(int type,ZContextVar* var);
	int pHeight = 0;
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

	void dropEvent(QDropEvent* event);

private:
	Ui::PropEditorSurfaceClass ui;
	Node3D* t_Node = nullptr;
	int edit_y = 20;
	QSpinBox* pos_X, * pos_Y, * pos_Z;
	QSpinBox* scale_X, * scale_Y, * scale_Z;
	QSpinBox* rot_X,*rot_Y,*rot_Z;
	vec3Edit* pos,* rot,* scale;
	std::vector<intEdit*> ints;
	std::vector<floatEdit*> floats;
	std::vector<stringEdit*> strings;
	std::vector<boolEdit*> bools;
	std::vector<comboEdit*> combos;
	comboEdit* ltype;
	vec3Edit* ldiff,* lspec;
	floatEdit* lrange;

};
