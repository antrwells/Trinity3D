#pragma once

#include <QMainWindow>
#include "ui_ImportMediaForm.h"
#include "qcheckbox.h"

class Import3DForm : public QMainWindow
{
	Q_OBJECT

public:
	Import3DForm(QWidget *parent = nullptr);
	~Import3DForm();
	void SetPath(std::string path)
	{
		mPath = path;
	}
	QCheckBox* importActor;
	QCheckBox* importMaterials;
private slots:
	void onCancel();
	void onImport();


protected:
	Ui::ImportMediaFormClass ui;
	std::string mPath;

};
