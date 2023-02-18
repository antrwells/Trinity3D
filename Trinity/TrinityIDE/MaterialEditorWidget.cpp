#include "MaterialEditorWidget.h"

MaterialEditorWidget::MaterialEditorWidget(QWidget *parent)
	: CDockWidget("Material Editor",parent)
{
	ui.setupUi(this);
	resize(800, 600);
	setWindowTitle("Material Editor");
	setAcceptDrops(true);

	setMouseTracking(true);
}

void MaterialEditorWidget::SetMaterial(Material* mat) {

	mEditMat = mat;
	std::string title = "Material Editor: " + mat->GetPath();
	setWindowTitle(title.c_str());


	auto name = new QLabel("Color Texture", this);
	name->setGeometry(12, 7, 100, 25);

	img_Color = new QLabel(this);
	QPixmap pix;
	pix.load(mat->GetColorMap()->GetPath().c_str());


	img_Color->setGeometry(10, 35, 128, 128);
	img_Color->setPixmap(pix.scaled(128,128));

	auto n_name = new QLabel("Normal Texture", this);
	n_name->setGeometry(12, 180, 100, 25);

	img_Norm = new QLabel(this);
	QPixmap pix_n;
	pix_n.load(mat->GetNormalMap()->GetPath().c_str());

	img_Norm->setGeometry(10, 205, 128, 128);
	img_Norm->setPixmap(pix_n.scaled(128,128));

	auto s_name = new QLabel("Specular Texture", this);
	s_name->setGeometry(12, 348, 100, 25);

	img_Spec = new QLabel(this);
	QPixmap pix_s;
	pix_s.load(mat->GetSpecularMap()->GetPath().c_str());

	img_Spec->setGeometry(10, 375, 128, 128);
	img_Spec->setPixmap(pix_s.scaled(128, 128));


}

MaterialEditorWidget::~MaterialEditorWidget()
{}
