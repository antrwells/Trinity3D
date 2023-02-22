#include "MaterialEditorWidget.h"
#include "DockManager.h"
#include "QPainter.h"
#include "DockArea.h"
#include "qpainterpath.h"
MaterialEditorWidget::MaterialEditorWidget(QWidget *parent)
	: CDockWidget("Material Editor",parent)
{
	ui.setupUi(this);
	//resize(800, 600);
	setWindowTitle("Material Editor");

	setAcceptDrops(true);
//	setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
	setMouseTracking(true);
	
	setAutoFillBackground(true);
	setMinimumSize(400, 580);
	mThis = this;
	//setMinimumSize(200, 200);
	//update();

}

void MaterialEditorWidget::SetMaterial(Material* mat) {

	mEditMat = mat;
	std::string title = "Material Editor: " + mat->GetPath();
	setWindowTitle(title.c_str());


	auto name = new QLabel("Color Texture", this);
	name->setGeometry(12, 7, 100, 25);
	name->setStyleSheet("background-color: #1E1E1E; color: #FFFFFF;");


	img_Color = new QLabel(this);
	QPixmap pix;
	pix.load(mat->GetColorMap()->GetPath().c_str());


	img_Color->setGeometry(10, 35, 128, 128);
	img_Color->setPixmap(pix.scaled(128,128));

	auto n_name = new QLabel("Normal Texture", this);
	n_name->setGeometry(12, 180, 100, 25);
	n_name->setStyleSheet("background-color: #1E1E1E; color: #FFFFFF;");



	img_Norm = new QLabel(this);
	QPixmap pix_n;
	pix_n.load(mat->GetNormalMap()->GetPath().c_str());

	img_Norm->setGeometry(10, 205, 128, 128);
	img_Norm->setPixmap(pix_n.scaled(128,128));

	auto s_name = new QLabel("Specular Texture", this);
	s_name->setGeometry(12, 348, 100, 25);
	s_name->setStyleSheet("background-color: #1E1E1E; color: #FFFFFF;");



	img_Spec = new QLabel(this);
	QPixmap pix_s;
	pix_s.load(mat->GetSpecularMap()->GetPath().c_str());

	img_Spec->setGeometry(10, 375, 128, 128);
	img_Spec->setPixmap(pix_s.scaled(128, 128));

	AddVec3Editor("Diffuse", mat->GetDiffusePtr());
	AddVec3Editor("Specular", mat->GetSpecularPtr());

	auto man = DockArea::mThis->GetManager();

///	man->addDockWidget(ads::OuterDockAreas, this);
	man->addDockWidgetFloating(this);
	update();
	setStyleSheet("background-color: #f0f0f0;");
	update();
}

MaterialEditorWidget::~MaterialEditorWidget()
{}


void MaterialEditorWidget::paintEvent(QPaintEvent* event) {

	CDockWidget::paintEvent(event);

	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing, false);
	p.setRenderHint(QPainter::TextAntialiasing, false);
	p.setRenderHint(QPainter::VerticalSubpixelPositioning, false);

	QPainterPath path;
	path.addRect(QRectF(0, 0, width(), height()));
	p.setPen(QPen(QColor(255, 255, 255), 1));
	//p.setPen(pen);

	p.fillPath(path, QColor(30, 30, 30));
	p.drawPath(path);


}


void MaterialEditorWidget::resizeEvent(QResizeEvent* event) {

	int aa = 5;
	auto siz = event->size();
	int w, h;
	w = siz.width();
	h = siz.height();
	if (w < 400) {
		w = 400;
	}
	if (h < 500) {
		h = 500;
	}
	resize(w, h);
}


vec3Ed* MaterialEditorWidget::AddVec3Editor(std::string name, float3* cur) {


	//auto row = new QHBoxLayout();


	auto name_lab = new QLabel(name.c_str(), this);
	name_lab->setGeometry(210, edit_y, 80, 20);

	name_lab->setStyleSheet("background-color: #1E1E1E; color: #FFFFFF;");


	auto x_lab = new QLabel("X:", this);

	QDoubleSpinBox* x_spinbox = new QDoubleSpinBox(this);
	x_spinbox->setRange(-10000, 10000);

	x_spinbox->setSingleStep(0.1);

	x_lab->setGeometry(275, edit_y, 40, 20);
	x_spinbox->setGeometry(290, edit_y, 80, 20);

	x_lab->setStyleSheet("background-color: #1E1E1E; color: #FFFFFF;");
	x_spinbox->setStyleSheet("background-color: #1E1E1E; color: #FFFFFF;");



	auto y_lab = new QLabel("Y:", this);
	QDoubleSpinBox* y_spinbox = new QDoubleSpinBox(this);
	y_spinbox->setRange(-10000, 10000);


	y_spinbox->setSingleStep(0.1);

	y_lab->setGeometry(375, edit_y, 40, 20);
	y_spinbox->setGeometry(390, edit_y, 80, 20);

	y_lab->setStyleSheet("background-color: #1E1E1E; color: #FFFFFF;");
	y_spinbox->setStyleSheet("background-color: #1E1E1E; color: #FFFFFF;");



	//
	auto z_lab = new QLabel("Z:", this);
	QDoubleSpinBox* z_spinbox = new QDoubleSpinBox(this);
	z_spinbox->setRange(-10000, 10000);


	z_spinbox->setSingleStep(0.1);

	z_lab->setGeometry(475, edit_y, 40, 20);
	z_spinbox->setGeometry(490, edit_y, 80, 20);

	z_lab->setStyleSheet("background-color: #1E1E1E; color: #FFFFFF;");
	z_spinbox->setStyleSheet("background-color: #1E1E1E; color: #FFFFFF;");


	edit_y += 25;

	//	nlayout->addWidget(x_spinbox);
		//x_spinbox->setValue(cur.x);



	vec3Ed* c = new vec3Ed(name.c_str(), x_spinbox, y_spinbox, z_spinbox, cur);
	c->mat = mEditMat;

	return c;
	/*
	nlayout->addWidget(new QLabel("Y:"));
	QDoubleSpinBox* y_spinbox = new QDoubleSpinBox();
	y_spinbox->setRange(-1000, 1000);
	y_spinbox->setSingleStep(0.1);
	nlayout->addWidget(y_spinbox);
	y_spinbox->setValue(cur.y);

	nlayout->addWidget(new QLabel("Z:"));
	QDoubleSpinBox* z_spinbox = new QDoubleSpinBox();
	z_spinbox->setRange(-1000, 1000);
	z_spinbox->setSingleStep(0.1);
	nlayout->addWidget(z_spinbox);
	z_spinbox->setValue(cur.z);

	lay->addLayout(nlayout);
	update();
	nlayout->update();
	*/
}

MaterialEditorWidget* MaterialEditorWidget::mThis = nullptr;