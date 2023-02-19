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
