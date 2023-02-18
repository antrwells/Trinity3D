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
#include "qlabel.h"

class MaterialEditorWidget : public ads::CDockWidget
{
	Q_OBJECT

public:
	MaterialEditorWidget(QWidget *parent = nullptr);
	~MaterialEditorWidget();
	void SetMaterial(Material* mat);
protected:
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


				}
				if (img_Over == 1) {
					auto tex = new Texture2D(event->mimeData()->text().toStdString().c_str());

					QPixmap pix(tex->GetPath().c_str());
					mEditMat->SetNormalMap(tex);
					img_Norm->setPixmap(pix.scaled(128, 128));
				}
				if (img_Over == 2)
				{
					auto tex = new Texture2D(event->mimeData()->text().toStdString().c_str());

					QPixmap pix(tex->GetPath().c_str());
					mEditMat->SetSpecularMap(tex);
					img_Spec->setPixmap(pix.scaled(128, 128));
				}
				img_Over = -1;


			}
			
		}
	}

private:
	Ui::MaterialEditorWidgetClass ui;
	Material* mEditMat = nullptr;
	QLabel* img_Color, * img_Norm, * img_Spec;
	int img_Over = -1;

};

