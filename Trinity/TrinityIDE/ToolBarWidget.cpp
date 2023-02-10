#include "ToolBarWidget.h"
#include "qpainter.h"
#include "qpainterpath.h"

ToolBarWidget::ToolBarWidget(QWidget *parent)
	: QWidget(parent)
{
	//ui.setupUi(this);
	buttonImg = QImage("t3d/toolbar_Button.png");
	setMouseTracking(true);
}

ToolBarWidget::~ToolBarWidget()
{}


void ToolBarWidget::paintEvent(QPaintEvent* event) {


	QPainter p(this);
	QPainterPath path;
	
	path.addRect(QRectF(-1, 0, width()+1, height()));
	p.setPen(QPen(QColor(255, 255, 255), 1));
	//p.setPen(pen);

	p.fillPath(path, QColor(30, 30, 30));
	//p.drawPath(path);

	QRect rect(-1, 0, width() + 1, height());


	QLinearGradient gradient( rect.topLeft(), rect.bottomLeft());
	gradient.setColorAt(0, QColor(20, 20, 20));
	gradient.setColorAt(1, QColor(35, 35, 35));
	p.fillRect(rect, gradient);

	for (int i = 0; i < mButtons.size(); i++) {

		auto but = mButtons[i];

		p.setOpacity(0.75);  // sets the opacity to 75%
		p.setCompositionMode(QPainter::CompositionMode_Screen);  // sets the composition mode to Screen
		
		if (but == mCurrentButton) {
			p.fillRect(but->x+4,10+4,54-8,height()-28, QColor(80,80,80));
		}
		else {
			p.fillRect(but->x + 4, 10 + 4, 54 - 8, height() - 28, QColor(40, 40, 40));
		}
		p.drawImage(QRect(but->x, 10, 54, height() - 20), buttonImg);
		if (but->type == 1) {
			p.drawImage(QRect(but->x + 8, 10 + 8, 54 - 16, height() - 36), but->image);
		}
	}
	
	//p.setPen(QPen::)


	//p.drawRect(0, 0, width(), height());

	//QWidget::paintEvent(event);
}

void ToolBarWidget::mouseMoveEvent(QMouseEvent* event)
{
	int x = event->x();
	int y = event->y();
	mCurrentButton = nullptr;
	for (int i = 0; i < mButtons.size(); i++) {

		auto but = mButtons[i];

		if (x > but->x && x < but->x + 54 && y>10 && y < 10+(height() - 20))
		{
			mCurrentButton = but;
			break;
		}

		//p.drawImage(QRect(but->x, 10, 54, height() - 20), buttonImg);
		if (but->type == 1) {
		//	p.drawImage(QRect(but->x + 4, 10 + 4, 54 - 8, height() - 28), but->image);
		}
	}
	update();
}

void ToolBarWidget::mousePressEvent(QMouseEvent* event) {

	if (event->button() == Qt::LeftButton)
	{

		if (mCurrentButton != nullptr) {
			mCurrentButton->act();
		}

	}
}