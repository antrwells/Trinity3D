#pragma once

#include <QMainWindow>
#include "ui_ToolBarWidget.h"
#include <QMouseEvent>
struct toolBar_Button {

	std::string text;
	QImage image;
	int type = 0;
	int x;
	std::function<void()> act = NULL;
};

class ToolBarWidget : public QWidget
{
	Q_OBJECT

public:
	ToolBarWidget(QWidget *parent = nullptr);
	~ToolBarWidget();
	void AddButton(std::string name);
	void AddImageButton(QImage image, std::function<void()> act)
	{

		toolBar_Button* but = new toolBar_Button;

		but->image = image;
		but->text = "";
		
		but->type = 1;
		but->x = next_x;
		but->act = act;
		next_x += 56;
		mButtons.push_back(but);


	}
	void AddSeperator(int x) {

		next_x += x;

	}


protected:
	virtual void paintEvent(QPaintEvent* event);
	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
private:
	Ui::ToolBarWidgetClass ui;
	int next_x = 15;
	std::vector<toolBar_Button*> mButtons;
	QImage buttonImg;
	toolBar_Button* mCurrentButton = nullptr;
};
