#include "QSceneGraph.h"
#include "qpainter.h"
#include "qpainterpath.h"


QSceneGraph::QSceneGraph(QWidget *parent)
	: CDockWidget("Scene Graph",parent)
{
	ui.setupUi(this);

	QPalette myPal;

	myPal.setColor(QPalette::Button, Qt::black);

	setAutoFillBackground(true);
	setPalette(myPal);

	w_SceneGraph = new SceneGraphWidget(this);
	w_SceneGraph->setGeometry(this->geometry());

	
}

void QSceneGraph::paintEvent(QPaintEvent* event) {

	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing);
	QPainterPath path;
	path.addRect(QRectF(0, 0, width(), height()));
	p.setPen(QPen(QColor(30, 30, 30), 4));
	//p.setPen(pen);

	p.fillPath(path,QColor(30,30,30));
	p.drawPath(path);
	/*
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setPen(QPen(QColor(30,30,30),4));
	const int distance = 2;

	
	painter.drawRect(QRect(0, 0, width(), height()));
	painter.drawf
//	painter.drawRoundedRect(QRect(distance, distance,
	//	width() - 2 * distance, height() - 2 * distance),
	//	10, 10);
	*/
}


QSceneGraph::~QSceneGraph()
{}
