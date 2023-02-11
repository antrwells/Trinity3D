#pragma once

#include <QWidget>
#include "ui_ContentBrowserWidget.h"
#include "DockManager.h"
#include "qscrollbar.h"
#include "DirCollection.h"

class ContentBrowserWidget : public ads::CDockWidget
{
	Q_OBJECT

public:
	ContentBrowserWidget(QWidget *parent = nullptr);
	~ContentBrowserWidget();

	void Browse(std::string path);

protected:
	virtual void resizeEvent(QResizeEvent* event);
	virtual void paintEvent(QPaintEvent* event);

public slots:
	void updateWidget(int newValue)
	{
		update();
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
};
