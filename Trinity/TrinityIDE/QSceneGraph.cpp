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
	w_Scrollbar = new QScrollBar(this);
	

	
}

void QSceneGraph::paintEvent(QPaintEvent* event) {

	CDockWidget::paintEvent(event);


	//p.drawPath(path);
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

void QSceneGraph::resizeEvent(QResizeEvent* event)
{
	QSize size = event->size();
	int width = size.width();
	int height = size.height();

	w_SceneGraph->resize(width-15,height);
	w_Scrollbar->setGeometry(width - 15,0, 15, height);

	// Perform actions based on the new size of the widget
	// ...

	// Don't forget to call the base implementation
	QWidget::resizeEvent(event);
}

QSceneGraph::~QSceneGraph()
{}
