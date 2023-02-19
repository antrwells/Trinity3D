#include "ImportMediaForm.h"
#include <QVBoxLayout>
#include "TrinityGlobal.h"
#include "Importer.h"
#include "qpushbutton.h"
#include "ContentBrowserWidget.h"
#include <filesystem>
#include <iostream>
Import3DForm::Import3DForm(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowTitle("Import 3D");

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* layout = new QVBoxLayout(centralWidget);
   
    importActor = new QCheckBox("Import Animated Actor", centralWidget);
    layout->addWidget(importActor);
  
    importMaterials = new QCheckBox("Import Materials", centralWidget);
    layout->addWidget(importMaterials);
    importMaterials->setChecked(true);

    QHBoxLayout* b_lo = new QHBoxLayout(centralWidget);

    QPushButton* import = new QPushButton("Import", centralWidget);
    b_lo->addWidget(import);

    QPushButton* cancel = new QPushButton("Cancel", centralWidget);
    b_lo->addWidget(cancel);

    layout->addLayout(b_lo);

    connect(cancel, &QPushButton::clicked, this, &Import3DForm::onCancel);
    connect(import, &QPushButton::clicked, this, &Import3DForm::onImport);

    //setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);


    /*
    * 
    QPushButton* button1 = new QPushButton("Button 1", centralWidget);
    layout->addWidget(button1);

    QPushButton* button2 = new QPushButton("Button 2", centralWidget);
    layout->addWidget(button2);

    QPushButton* button3 = new QPushButton("Button 3", centralWidget);
    layout->addWidget(button3);
    */

}


Import3DForm::~Import3DForm()
{}


void Import3DForm::onCancel() {

    close();

}

void Import3DForm::onImport() {

    auto imp_actor = importActor->isChecked();
    auto imp_mats = importMaterials->isChecked();

    if (!imp_actor) {

        auto np = mPath;

        std::string originalFileName = np;
        std::string newFileName;

        // Find the position of the dot in the original file name
        size_t dotPos = originalFileName.find_last_of(".");

        // Check if a dot was found
        if (dotPos != std::string::npos)
        {
            // Replace the extension with ".vmesh"
            newFileName = originalFileName.substr(0, dotPos) + ".vmesh";
        }
        else
        {
            // No extension found, add ".vmesh" to the end of the file name
            newFileName = originalFileName + ".vmesh";
        }

        auto scene = TrinityGlobal::CurrentScene;

        Importer* imp = new Importer;

        auto node = imp->ImportEntity(mPath.c_str());

        std::string fn = ContentBrowserWidget::mCurrentPath;

        std::string originalFilePath = newFileName;
        

        // Extract the file name and extension from the original file path
        newFileName = std::filesystem::path(originalFilePath).filename().string();

        newFileName = fn + newFileName;

        node->SaveMaterials("c:\\content\\materials\\");

        scene->SaveNodeToFile(newFileName,node);

        ContentBrowserWidget::mThis->Reload();

    }
  
    close();



}