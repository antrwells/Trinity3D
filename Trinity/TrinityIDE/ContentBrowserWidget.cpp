#include "ContentBrowserWidget.h"
#include "qpainter.h"
#include "qpainterpath.h"
#include <QFileDialog>
#include "qfileinfo.h"
#include "qdrag.h"
#include "qmimedata.h"
#include "Texture2D.h"
#include "Material.h"
#include "Mesh3D.h"

ContentBrowserWidget* ContentBrowserWidget::mThis = nullptr;

ContentBrowserWidget::ContentBrowserWidget(QWidget *parent)
	: ads::CDockWidget("Content Browser", parent)
{
//	ui.setupUi(this);
	folderIcon = QImage("t3d/folderIcon.png");
	fileIcon = QImage("t3d/fileIcon.png");
	file3DIcon = QImage("t3d/3dicon.png");
	fileScriptIcon = QImage("t3d/scripticon.png");
	w_Scrollbar = new QScrollBar(this);
	setMouseTracking(true);
	connect(w_Scrollbar, &QScrollBar::valueChanged, this, &ContentBrowserWidget::updateWidget);
	//installEventFilter(this);
	setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, &ContentBrowserWidget::customContextMenuRequested, this, &ContentBrowserWidget::showContextMenu);
//	setAcceptDrops(true);
	mThis = this;
}

ContentBrowserWidget::~ContentBrowserWidget()
{}

void ContentBrowserWidget::Reload() {

	Browse(mCurrentPath);
	update();
}

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

	for (int i = 0; i < mItems.size(); i++) {

		auto item = mItems[i];


		if (item->isFolder) {



			//if (but == mCurrentButton) {
				//p.fillRect(but->x + 4, 10 + 4, 54 - 8, height() - 28, QColor(80, 80, 80));
			//}
	//		else {
		//		p.fillRect(but->x + 4, 10 + 4, 54 - 8, height() - 28, QColor(40, 40, 40));
		//	}

			p.setOpacity(0.75);  // sets the opacity to 75%
			p.setCompositionMode(QPainter::CompositionMode_Screen);  // sets the composition mode to Screen

		

			p.drawImage(QRect(dx, dy, 64, 64), item->icon);
			if (item == mCurrentItem) {
				p.drawImage(QRect(dx, dy, 64, 64),item->icon);
				
				//p.fillRect(dx, dy, 64, 64, QColor(120, 120, 120));
			}
			else {
				//p.fillRect(dx, dy, 64, 64, QColor(40, 40, 40));
			}

			p.drawText(QPointF(dx + 5, dy + 74), item->name.c_str());



			dx = dx + 84;

			if (dx + 64 > width()) {
				dx = 20;
				dy = dy + 84;
			}

		}
	}

	for (int i = 0; i < mItems.size(); i++) {

		auto item = mItems[i];

		if (!item->isFolder) {

			p.setOpacity(0.75);  // sets the opacity to 75%
			p.setCompositionMode(QPainter::CompositionMode_Screen);  // sets the composition mode to Screen

			//if (but == mCurrentButton) {
				//p.fillRect(but->x + 4, 10 + 4, 54 - 8, height() - 28, QColor(80, 80, 80));
			//}
	//		else {
		//		p.fillRect(but->x + 4, 10 + 4, 54 - 8, height() - 28, QColor(40, 40, 40));
		//	}


			p.drawImage(QRect(dx, dy, 64, 64), item->icon);
			if (item == mCurrentItem) {
				p.drawImage(QRect(dx, dy, 64, 64), item->icon);
			}
			else {
				//p.fillRect(dx, dy, 64, 64, QColor(40, 40, 40));
			}


			p.drawText(QPointF(dx + 5, dy + 74), item->name.c_str());



			dx = dx + 84;

			if (dx + 64 > width()) {
				dx = 20;
				dy = dy + 84;
			}
		}
	}

	 dx = 20;
	 dy = 20;

	 for (int i = 0; i < mItems.size(); i++) {

		 auto item = mItems[i];

		if (item->isFolder) {

			



			dx = dx + 84;

			if (dx + 64 > width()) {
				dx = 20;
				dy = dy + 84;
			}
		}
	}


	 for (int i = 0; i < mItems.size(); i++) {

		 auto item = mItems[i];

		if (!item->isFolder) {

			



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

std::string getFileExtension(const std::string& filePath) {
	size_t dotPos = filePath.rfind('.');
	if (dotPos == std::string::npos) {
		return "";
	}
	return filePath.substr(dotPos + 1);
}

void ContentBrowserWidget::Back() {

	if (mPathStack.size() <= 1)
	{
		return;
	}

	mPathStack.pop();

	auto np = mPathStack.top();
	mPathStack.pop();
	Browse(np);


}

void ContentBrowserWidget::Browse(std::string path) {

	mCurrentPath = path;
	mPathStack.push(path);

	currentDir = DirCollection(path.c_str());
	mItems.resize(0);

	for (int i = 0; i < currentDir.enteries.size(); i++) {

		auto e = currentDir.enteries[i];

		ContentItem* item = new ContentItem;

		std::string ext = getFileExtension(e.name);

		if (e.folder || ext == "vmesh" || ext == "zs" || ext =="vgraph" || ext =="vmat" || ext =="png")
		{

			item->name = e.name;
			item->path = e.full;
			item->isFolder = e.folder;
			item->drawx = 0;
			item->drawy = 0;

			if (!e.folder) {
				QFileInfo fileInfo(QString(item->path.c_str()));
				QString fileExtension = fileInfo.suffix();

				auto ss = fileExtension.toStdString();
				item->type = ss;
			}
			if (ext == "vmesh" || ext == "vgraph" || ext=="vmat")
			{
				item->icon = file3DIcon;
			}
			else if (ext == "zs")
			{
				item->icon = fileScriptIcon;
			}
			else if (ext == "png")
			{
				item->icon = QImage(item->path.c_str());

			}
			else if (e.folder) {
				//	item->icon = fileIcon;
				item->icon = folderIcon;
			}



			mItems.push_back(item);
		}
	}

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



void ContentBrowserWidget::mouseMoveEvent(QMouseEvent* event)
{
	 mousePos = event->pos();


	if (isDrag) {
		
		if ((event->pos() - dragStartPos).manhattanLength() < QApplication::startDragDistance()) {
			//isDrag = false;
			return;
			//return;

		}
		//return;

		QDrag* drag = new QDrag(this);
		QMimeData* mimeData = new QMimeData;

		mimeData->setText(QString(mCurrentItem->path.c_str()));
		drag->setMimeData(mimeData);

		if (mCurrentItem->type == "vmesh")
		{
			mimeData->setProperty("type", "mesh");
		}
		else if (mCurrentItem->type == "vgraph")
		{
			mimeData->setProperty("type", "graph");
		}
		else if (mCurrentItem->type == "vmat")
		{
			mimeData->setProperty("type", "material");
		}
		else if (mCurrentItem->type == "png")
		{
			mimeData->setProperty("type", "texture");
		}else
		{
			mimeData->setProperty("type", "script");
		}
		
		Qt::DropAction act=  drag->exec();


		isDrag = false;
		return;
	}

	int x = event->x();
	int y = event->y();

	int dx = 20;
	int dy = 20 - w_Scrollbar->value();
	mCurrentEntry = nullptr;
	mCurrentName = "";
	mCurrentItem = nullptr;

	for (int i = 0; i < mItems.size(); i++) {

		auto item = mItems[i];

		if (item->isFolder) {

		

			//p.drawText(QPointF(dx + 5, dy + 74), entry.name.c_str());

			if (x >= (dx) && x <= (dx + 64) && y > dy && y < dy + 64)
			{
				mCurrentItem = item;
			}


			dx = dx + 84;

			if (dx + 64 > width()) {
				dx = 20;
				dy = dy + 84;
			}
		}
	}


	for (int i = 0; i < mItems.size(); i++) {

		auto item = mItems[i];

		if (!item->isFolder) {

		
			if (x >= (dx) && x <= (dx + 64) && y > dy && y < dy + 64)
			{

				//mCurrentName = std::string(entry.full);
				mCurrentItem = item;
			}


			dx = dx + 84;

			if (dx + 64 > width()) {
				dx = 20;
				dy = dy + 84;
			}
		}
	}
	update();

}

void ContentBrowserWidget::mousePressEvent(QMouseEvent* event) {

	if (event->button() == Qt::BackButton)
	{
		Back();
		update();
		QMouseEvent* event = new QMouseEvent(QEvent::MouseMove, mousePos, Qt::NoButton, Qt::NoButton, Qt::NoModifier);
		QCoreApplication::postEvent(this, event);
		return;
	}

	if (mCurrentItem != nullptr) {
		if (mCurrentItem->isFolder)
		{
			Browse(mCurrentItem->path);
			update();
			QMouseEvent* event = new QMouseEvent(QEvent::MouseMove, mousePos, Qt::NoButton, Qt::NoButton, Qt::NoModifier);
			QCoreApplication::postEvent(this, event);
			return;
		}
		if (event->button() == Qt::LeftButton) {
			dragStartPos = event->pos();
			isDrag = true;
		}
	}

}

void ContentBrowserWidget::Refreash() {



}

void ContentBrowserWidget::ImportFile() {

	QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "Media Files (*.fbx);;All Files (*)");
	if (!fileName.isEmpty()) {

		QFileInfo fileInfo(fileName);
		QString fileExtension = fileInfo.suffix();

		auto ss = fileExtension.toStdString();

		if (ss == std::string("fbx")) {

			Import3DForm* form = new Import3DForm;
			form->SetPath(fileInfo.filePath().toStdString());
			form->show();
		}
	}

}

void ContentBrowserWidget::CreateMaterial() {

	QString fileName = QFileDialog::getSaveFileName(this, "Create Material", mCurrentPath.c_str(), "Material (*.vmat);;All Files (*)");
	if (!fileName.isEmpty()) {

		Material *new_mat = new Material;
		new_mat->SaveMaterial(fileName.toStdString());
		Refreash();
	}

}



std::string ContentBrowserWidget::mCurrentPath = "";