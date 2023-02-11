#pragma once

#include <QMainWindow>
#include "ui_DirectXHost.h"
#include "qwindow.h"

class DirectXHost : public QWindow
{
	Q_OBJECT

public:
	DirectXHost(QWidget *parent = nullptr);
	~DirectXHost();

private:
	Ui::DirectXHostClass ui;
};
