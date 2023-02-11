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

struct ContentItem {

	std::string path;
	std::string name;
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
	void ImportFile();
	void Refreash();

	static std::string mCurrentPath;

protected:
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

		QAction action1("Import", this);
		connect(&action1, &QAction::triggered, [=] { ImportFile(); });
		contextMenu.addAction(&action1);


		QAction action2("Refreash", this);
		connect(&action2, &QAction::triggered, [=] { Refreash(); });
		contextMenu.addAction(&action2);


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
	QPoint dragStartPos;
	bool isDrag = false;
};
