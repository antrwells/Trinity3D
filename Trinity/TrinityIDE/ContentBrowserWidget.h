#pragma once

#include <QWidget>
#include "ui_ContentBrowserWidget.h"
#include "DockManager.h"
#include "qscrollbar.h"
#include "DirCollection.h"
#include "qmenu"
#include <vector>
#include "ImportMediaForm.h"
#include "qmimedata.h"
#include <stack>
#include "MaterialEditorWidget.h"
#include "TrinityGlobal.h"

struct ContentItem {

	std::string path;
	std::string name;
	std::string type;
	bool isFolder = false;
	int drawx, drawy;
	QImage icon;

};

class ContentBrowserWidget : public ads::CDockWidget
{
	Q_OBJECT

public:
	ContentBrowserWidget(QWidget *parent = nullptr);
	~ContentBrowserWidget();

	void Browse(std::string path);
	void Back();
	void ImportFile();
	void Refreash();
	void CreateMaterial();

	void Reload();
	static ContentBrowserWidget* mThis;
	static std::string mCurrentPath;

protected:

	void mouseDoubleClickEvent(QMouseEvent* event) override {
		if (event->button() == Qt::LeftButton) {
			if (mCurrentItem != nullptr) {
				//		qDebug() << "Left button double-clicked at (" << event->pos().x() << "," << event->pos().y() << ")";
				if (mCurrentItem->type == "vmat")
				{
					int a = 5;
					MaterialEditorWidget* mat_Edit = new MaterialEditorWidget;

					Material* mat = new Material;
					mat->LoadMaterial(mCurrentItem->path);
					mat_Edit->SetMaterial(mat);
					mat_Edit->show();



				}
			}
		}
		QWidget::mouseDoubleClickEvent(event);
	}
	virtual void resizeEvent(QResizeEvent* event);
	virtual void paintEvent(QPaintEvent* event);
	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	//bool eventFilter(QObject* obj, QEvent* event) override;
	void dragEnterEvent(QDragEnterEvent* event)
	{
		if (event->mimeData()->hasText()) {
			
		}
		event->acceptProposedAction();
	}

	void dragMoveEvent(QDragMoveEvent* event)
	{
		if (event->mimeData()->hasText()) {
			event->acceptProposedAction();
		}
		event->acceptProposedAction();
	}

	void dropEvent(QDropEvent* event)
	{
		if (event->mimeData()->hasText()) {
			//setText(event->mimeData()->text());
			event->acceptProposedAction();
		}
		event->acceptProposedAction();
	}

	void mouseReleaseEvent(QMouseEvent* event)
	{
		isDrag = false;
		//Q_UNUSED(event)
	}
public slots:
	void updateWidget(int newValue)
	{
		update();
	}

private slots:
	void showContextMenu(const QPoint& pos)
	{
		QMenu contextMenu(tr("Context menu"), this);

		QAction action1("Import Mesh", this);
		connect(&action1, &QAction::triggered, [=] { ImportFile(); });
		contextMenu.addAction(&action1);


		QAction action2("Refreash", this);
		connect(&action2, &QAction::triggered, [=] { Refreash(); });
		contextMenu.addAction(&action2);


		QAction action3("Material", this);
		connect(&action3, &QAction::triggered, [=] { CreateMaterial(); });
		auto crMenu = contextMenu.addMenu("Create");

		crMenu->addAction(&action3);



		contextMenu.exec(mapToGlobal(pos));
	}

private:
	Ui::ContentBrowserWidgetClass ui;
	DirCollection currentDir;
	QImage folderIcon;
	QImage fileIcon;
	QImage file3DIcon;
	QImage file2DIcon;
	QImage fileSoundIcon;
	QImage fileScriptIcon;
	QScrollBar* w_Scrollbar;
	DirEntry* mCurrentEntry = nullptr;
	std::string mCurrentName = "";
	ContentItem* mCurrentItem = nullptr;
	std::vector<ContentItem*> mItems;
	QPoint mousePos;
	QPoint dragStartPos;
	bool isDrag = false;
	std::stack<std::string> mPathStack;
};
