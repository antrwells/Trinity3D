#include "ContentBrowserWidget.h"
#include "qpainter.h"
#include "qpainterpath.h"

ContentBrowserWidget::ContentBrowserWidget(QWidget *parent)
	: ads::CDockWidget("Content Browser", parent)
{
//	ui.setupUi(this);
	folderIcon = QImage("t3d/folderIcon.png");
	fileIcon = QImage("t3d/fileIcon.png");
	w_Scrollbar = new QScrollBar(this);
	connect(w_Scrollbar, &QScrollBar::valueChanged, this, &ContentBrowserWidget::updateWidget);
}

ContentBrowserWidget::~ContentBrowserWidget()
{}



void ContentBrowserWidget::paintEvent(QPaintEvent* event) {

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


	int dx = 20;
	int dy = 20 - w_Scrollbar->value();

	for (int i = 0; i < currentDir.enteries.size(); i++) {

		auto entry = currentDir.enteries[i];

		if (entry.folder) {

			p.setOpacity(0.75);  // sets the opacity to 75%
			p.setCompositionMode(QPainter::CompositionMode_Screen);  // sets the composition mode to Screen

			//if (but == mCurrentButton) {
				//p.fillRect(but->x + 4, 10 + 4, 54 - 8, height() - 28, QColor(80, 80, 80));
			//}
	//		else {
		//		p.fillRect(but->x + 4, 10 + 4, 54 - 8, height() - 28, QColor(40, 40, 40));
		//	}
			p.drawImage(QRect(dx, dy, 64, 64), folderIcon);

			p.drawText(QPointF(dx + 5, dy + 74), entry.name.c_str());



			dx = dx + 84;

			if (dx + 64 > width()) {
				dx = 20;
				dy = dy + 84;
			}
		}
	}


	for (int i = 0; i < currentDir.enteries.size(); i++) {

		auto entry = currentDir.enteries[i];

		if (!entry.folder) {

			p.setOpacity(0.75);  // sets the opacity to 75%
			p.setCompositionMode(QPainter::CompositionMode_Screen);  // sets the composition mode to Screen

			//if (but == mCurrentButton) {
				//p.fillRect(but->x + 4, 10 + 4, 54 - 8, height() - 28, QColor(80, 80, 80));
			//}
	//		else {
		//		p.fillRect(but->x + 4, 10 + 4, 54 - 8, height() - 28, QColor(40, 40, 40));
		//	}
			p.drawImage(QRect(dx, dy, 64, 64), fileIcon);

			p.drawText(QPointF(dx + 5, dy + 74), entry.name.c_str());



			dx = dx + 84;

			if (dx + 64 > width()) {
				dx = 20;
				dy = dy + 84;
			}
		}
	}

	 dx = 20;
	 dy = 20;

	for (int i = 0; i < currentDir.enteries.size(); i++) {

		auto entry = currentDir.enteries[i];

		if (entry.folder) {

			



			dx = dx + 84;

			if (dx + 64 > width()) {
				dx = 20;
				dy = dy + 84;
			}
		}
	}


	for (int i = 0; i < currentDir.enteries.size(); i++) {

		auto entry = currentDir.enteries[i];

		if (!entry.folder) {

			



			dx = dx + 84;

			if (dx + 64 > width()) {
				dx = 20;
				dy = dy + 84;
			}
		}
	}

	int max = dy - (height() - 20);

	if (max < 20) max = 20;
	w_Scrollbar->setMaximum(max);
	w_Scrollbar->setPageStep(height());


}

void ContentBrowserWidget::Browse(std::string path) {

	currentDir = DirCollection(path.c_str());

}


void ContentBrowserWidget::resizeEvent(QResizeEvent* event)
{
	QSize size = event->size();
	int width = size.width();
	int height = size.height();

	//w_SceneGraph->resize(width - 15, height);
	w_Scrollbar->setGeometry(width - 15, 0, 15, height);

	// Perform actions based on the new size of the widget
	// ...

	// Don't forget to call the base implementation
	QWidget::resizeEvent(event);
}