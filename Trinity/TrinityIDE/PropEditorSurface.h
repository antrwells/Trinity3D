#pragma once
#include <QVBoxLayout>

#include <QWidget>
#include "ui_PropEditorSurface.h"
#include "Node3D.h"
#include "qspinbox.h"
#include <string>

struct vec3Edit
{
	std::string name;
	QDoubleSpinBox* x, * y, * z;
};

class PropEditorSurface : public QWidget
{
	Q_OBJECT

public:
	PropEditorSurface(QWidget *parent = nullptr);
	~PropEditorSurface();
	void SetNode(Node3D* node);
	void ReSet();
	vec3Edit AddVec3Editor(std::string name,float3 cur);
private:
	Ui::PropEditorSurfaceClass ui;
	Node3D* t_Node;
	int edit_y = 20;
	QSpinBox* pos_X, * pos_Y, * pos_Z;
	QSpinBox* scale_X, * scale_Y, * scale_Z;
	QSpinBox* rot_X,*rot_Y,*rot_Z;
	vec3Edit pos, rot, scale;

};
