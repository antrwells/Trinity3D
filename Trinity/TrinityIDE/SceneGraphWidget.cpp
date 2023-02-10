#include "SceneGraphWidget.h"
#include "qpainter.h"
#include "qpainterpath.h"
#include "TrinityGlobal.h"
#include <qevent.h>

SceneGraphWidget::SceneGraphWidget(QWidget* parent)
	: QWidget(parent)
{
	setMouseTracking(true);
	//ui.setupUi(this);
}



void SceneGraphWidget::DrawNode(Node3D* node, int& dx, int& dy, QPainter& p)
{

	auto name = node->GetName();

	bool open = node->mNodeOpen;






	QPainterPath path;

	if (mActiveNode == node) {
		path.addRect(QRectF(8, dy - 14, width() - (16), 25));


		p.setPen(QPen(QColor(255, 255, 255), 1));
		//p.setPen(pen);

		p.fillPath(path, QColor(120, 120, 120));
		p.drawPath(path);
	}

	if (mCurrentNode == node) {
		path.addRect(QRectF(8, dy - 14, width() - (16), 25));

		
		p.setPen(QPen(QColor(255, 255, 255), 1));
		//p.setPen(pen);

		p.fillPath(path, QColor(70, 70, 70));
		p.drawPath(path);
	}

	p.setPen(QPen(QColor(255, 255, 255), 2));
	p.drawRect(QRect(dx + 4, dy - 5, 8, 8));

	

	int a = 5;
	p.drawText(QPoint(dx + 20, dy + 3), name);
	if (open) {
		p.drawRect(QRect(dx + 6, dy - 3, 4, 4));
		auto cc = node->ChildrenCount();
		dx = dx + 15;
		dy = dy + 25;
		int ox = dx;
		for (int i = 0; i < cc; i++) {
		
			DrawNode(node->GetChild(i), dx, dy, p);
			dx = ox;
		}
	}
	else {
		dy = dy + 25;
	}

}

void SceneGraphWidget::paintEvent(QPaintEvent* event) {

	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing);
	QPainterPath path;
	path.addRect(QRectF(0, 0, width(), height()));
	p.setPen(QPen(QColor(255, 255, 255), 8));
	//p.setPen(pen);

	p.fillPath(path, QColor(30, 30, 30));
	p.drawPath(path);

	auto scene = TrinityGlobal::CurrentScene;
	//mCurrentNode = scene->GetRoot();
	int dx, dy;
	dx = 10;
	dy = 20;

	dy = dy - mScrollLink->value();
	DrawNode(scene->GetRoot(), dx, dy, p);

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

void SceneGraphWidget::CheckNode(Node3D* node, int& dx, int& dy, int mx, int my) {


	if (mx >= 2 && my >= (dy - 14) && mx < ((width() - 4)) && my <= ((dy - 14) + 25))
	{
		mCurrentNode = node;
	}

	if (node->mNodeOpen)
	{

		//		p.drawRect(QRect(dx + 6, dy - 3, 4, 4));
		auto cc = node->ChildrenCount();
		for (int i = 0; i < cc; i++) {
			dx = dx + 15;
			dy = dy + 25;
			CheckNode(node->GetChild(i), dx, dy,mx,my);
		}
	}
}

void SceneGraphWidget::mousePressEvent(QMouseEvent* event) {

	if (event->button() == Qt::LeftButton)
	{

		if (mCurrentNode != nullptr) {
			mActiveNode = mCurrentNode;
			//mActiveNode->mNodeOpen = mActiveNode ? false : true;
			if (mActiveNode->mNodeOpen)
			{
				mActiveNode->mNodeOpen = false;
			}
			else {
				mActiveNode->mNodeOpen = true;
			}
			update();
		}
		else {
			mActiveNode = nullptr;
			update();
		}

		update();
	}
	int max = 20;
	auto scene = TrinityGlobal::CurrentScene;
	GetMaxSize(scene->GetRoot(), max);
	int bb = 0;
	mScrollLink->setMaximum(max);
	mScrollLink->setPageStep(height());
}

void SceneGraphWidget::mouseMoveEvent(QMouseEvent* event)
{
	int x = event->x();
	int y = event->y();


	auto scene = TrinityGlobal::CurrentScene;
	//mCurrentNode = scene->GetRoot();

	mCurrentNode = nullptr;
	int dx, dy;
	dx = 10;
	dy = 20;
	dy = dy - mScrollLink->value();
	CheckNode(scene->GetRoot(), dx,dy, x, y);
	int max = 20;
	GetMaxSize(scene->GetRoot(), max);
	int bb = 0;
	mScrollLink->setMaximum(max);
	mScrollLink->setPageStep(height());
	


	// Perform actions based on the mouse position
	// ...

	// Don't forget to call the base implementation
	QWidget::mouseMoveEvent(event);

	update();

}

void SceneGraphWidget::GetMaxSize(Node3D* node, int& my)
{

	if (node->mNodeOpen)
	{

		//		p.drawRect(QRect(dx + 6, dy - 3, 4, 4));
		auto cc = node->ChildrenCount();
		for (int i = 0; i < cc; i++) {
			my = my + 25;
			GetMaxSize(node->GetChild(i), my);
		}
	}
	else {
		my = my + 25;
	}
}

SceneGraphWidget::~SceneGraphWidget()
{}
