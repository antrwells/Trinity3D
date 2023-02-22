#pragma once

#include <QWidget>
#include "ui_MaterialEditorWidget.h"
#include "DockManager.h"
#include "qscrollbar.h"
#include "DirCollection.h"
#include "qmenu"
#include <vector>
#include "ImportMediaForm.h"
#include "qmimedata.h"
#include <stack>
#include "Material.h"
#include "TrinityGlobal.h"
#include "qlabel.h"
#include "qspinbox.h"



struct vec3Ed
{
	std::string name;
	QDoubleSpinBox* x, * y, * z;
	float3* real_val;
	Node3D* is_NodeRot = nullptr;
	Material* mat;
	//ZContextVar* var = nullptr;
	bool block = false;
	vec3Ed()
	{

	}
	vec3Ed(const std::string& name, QDoubleSpinBox* x, QDoubleSpinBox* y, QDoubleSpinBox* z, float3* real) :
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
		
	

		//mEditMat->SaveMaterial(mEditMat->GetPath());
		//TrinityGlobal::CurrentScene->ReloadMaterials();
		
		real_val[0] = float3(x->value(), y->value(), z->value());
		mat->SaveMaterial(mat->GetPath());
		TrinityGlobal::CurrentScene->ReloadMaterials();

		//MaterialEditorWidget::mThis->UpdateMaterials();
//		if (is_NodeRot != nullptr) {

		//	if (!block) {
			//	is_NodeRot->SetRotationEular(real_val[0]);
	//		}

		//}
	};
};

class MaterialEditorWidget : public ads::CDockWidget
{
	Q_OBJECT

public:
	MaterialEditorWidget(QWidget *parent = nullptr);
	~MaterialEditorWidget();
	void SetMaterial(Material* mat);
	vec3Ed* AddVec3Editor(std::string name, float3* cur);
	
	static MaterialEditorWidget* mThis;
protected:
	virtual void paintEvent(QPaintEvent* event);
	void dragEnterEvent(QDragEnterEvent* event)
	{
		if (event->mimeData()->hasText()) {
			if (event->mimeData()->property("type").toString() == QString("texture"))
			{
				int a = 55;
				event->acceptProposedAction();

			}

		}
	}

	void dragMoveEvent(QDragMoveEvent* event)
	{
		if (event->mimeData()->hasText()) {
			if (event->mimeData()->property("type").toString() == QString("texture"))
			{
				int a = 55;
				
				QPoint globalPos = QCursor::pos();

				// Map global position to local position of widget
				QPoint localPos = mapFromGlobal(globalPos);
				img_Over = -1;
				if (localPos.x() > 10 && localPos.y() > 35 && localPos.x() < 10 + 128 && localPos.y() < 35 + 128) {
					event->acceptProposedAction();
					img_Over = 0;
				}
				if (localPos.x() > 10 && localPos.y() > 35 && localPos.x() < 10 + 128 && localPos.y() < 35 + 128) {
					event->acceptProposedAction();
					img_Over = 0;
				}if (localPos.x() > 10 && localPos.y() > 205 && localPos.x() < 10 + 128 && localPos.y() < 205 + 128) {
					event->acceptProposedAction();
					img_Over = 1;
				}
				if (localPos.x() > 10 && localPos.y() > 375 && localPos.x() < 10 + 128 && localPos.y() < 375 + 128) {
					event->acceptProposedAction();
					img_Over = 2;
				}

			}
		}
	}

	void dropEvent(QDropEvent* event)
	{
		if (event->mimeData()->hasText()) {
			if (event->mimeData()->property("type").toString() == QString("texture"))
			{
				int a = 55;
				event->acceptProposedAction();

				auto path = event->mimeData()->text().toStdString();
				if (img_Over == 0)
				{
					
					auto tex = new Texture2D(event->mimeData()->text().toStdString().c_str());

					QPixmap pix(tex->GetPath().c_str());
					mEditMat->SetColorMap(tex);
					img_Color->setPixmap(pix.scaled(128, 128));
					mEditMat->SaveMaterial(mEditMat->GetPath());
					TrinityGlobal::CurrentScene->ReloadMaterials();

				}
				if (img_Over == 1) {
					auto tex = new Texture2D(event->mimeData()->text().toStdString().c_str());

					QPixmap pix(tex->GetPath().c_str());
					mEditMat->SetNormalMap(tex);
					img_Norm->setPixmap(pix.scaled(128, 128));
					mEditMat->SaveMaterial(mEditMat->GetPath());
					TrinityGlobal::CurrentScene->ReloadMaterials();
				}
				if (img_Over == 2)
				{
					auto tex = new Texture2D(event->mimeData()->text().toStdString().c_str());

					QPixmap pix(tex->GetPath().c_str());
					mEditMat->SetSpecularMap(tex);
					img_Spec->setPixmap(pix.scaled(128, 128));
					mEditMat->SaveMaterial(mEditMat->GetPath());
					TrinityGlobal::CurrentScene->ReloadMaterials();
				}
				img_Over = -1;


			}
			
		}
	}
	void resizeEvent(QResizeEvent* event) override;
private:
	Ui::MaterialEditorWidgetClass ui;
	Material* mEditMat = nullptr;
	QLabel* img_Color, * img_Norm, * img_Spec;
	int img_Over = -1;
	vec3Ed* ldiff, * lspec;
	int edit_y = 25;
};

