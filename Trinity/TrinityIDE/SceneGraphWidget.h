#pragma once

#include <QMainWindow>
#include "ui_SceneGraphWidget.h"
#include "Node3D.h"
#include <QMouseEvent>
#include "qscrollbar.h"
#include "qdrag.h"
#include "qmimedata.h"
#include "TrinityGlobal.h"
class SceneGraphWidget : public QWidget
{
	Q_OBJECT

public:
	SceneGraphWidget(QWidget *parent = nullptr);
	~SceneGraphWidget();
	void SetScroller(QScrollBar* scroll) {
		mScrollLink = scroll;
		connect(scroll, &QScrollBar::valueChanged, this, &SceneGraphWidget::updateWidget);
	}

public slots:
	void updateWidget(int newValue)
	{
		update();
	}
private slots:
	void showContextMenu(const QPoint& pos)
	{
		QMenu contextMenu(tr("Context menu"), this);

		QAction action1("Create", this);
		connect(&action1, &QAction::triggered, [=] { });
		contextMenu.addAction(&action1);


		QAction action2("Delete", this);
		connect(&action2, &QAction::triggered, [=] { DeleteCurrent(); });
		contextMenu.addAction(&action2);



		contextMenu.exec(mapToGlobal(pos));
	}

protected:
	void DeleteCurrent();
	void dragEnterEvent(QDragEnterEvent* event)
	{
		if (event->mimeData()->hasText()) {
			if (event->mimeData()->property("type").toString() == QString("mesh") || event->mimeData()->property("type").toString() == QString("node"))
			{
				event->acceptProposedAction();
			}
		}
	}

	void dragMoveEvent(QDragMoveEvent* event)
	{
		if (event->mimeData()->hasText()) {
			if (event->mimeData()->property("type").toString() == QString("mesh") || event->mimeData()->property("type").toString() == QString("node"))
			{
				event->acceptProposedAction();
			}
		}
	}

	void dropEvent(QDropEvent* event)
	{
		if (event->mimeData()->hasText()) {
			//setText(event->mimeData()->text());
			if (event->mimeData()->property("type").toString() == QString("mesh") || event->mimeData()->property("type").toString() == QString("node"))
			{
				event->acceptProposedAction();

				if (event->mimeData()->property("type").toString() == QString("node")) {


					QPoint globalMousePos = QCursor::pos();

					// Map the mouse position to local coordinates of the widget
					QPoint localMousePos = this->mapFromGlobal(globalMousePos);
					mox = localMousePos.x();
					moy = localMousePos.y();
					int dx, dy;
					dx = 10;
					dy = 20;
					dy = dy - mScrollLink->value();
					mCurrentNode = nullptr;
					CheckNode(TrinityGlobal::CurrentScene->GetRoot(), dx, dy, mox, moy);
					int max = 20;
					if (mCurrentNode == nullptr) {
						mCurrentNode = TrinityGlobal::CurrentScene->GetRoot();
						mCurrentNode->AddNode(mActiveNode);
						return;
					}
					if (mActiveNode->IsChildOf(mCurrentNode) == false) {
						if (mCurrentNode != TrinityGlobal::CurrentScene->GetRoot()) {
							if (mCurrentNode != mActiveNode) {

								if (mCurrentNode != nullptr && mActiveNode != nullptr) {

									mCurrentNode->AddNode(mActiveNode);

								}

							}
						}
					}

					int a = 5;
					
					update();

				}
				else {


					auto scene = TrinityGlobal::CurrentScene;

					auto node = scene->ReadNodeFromFile(std::string(event->mimeData()->text().toStdString()));

					if (mActiveNode != nullptr) {
						mActiveNode->AddNode(node);
					}
					else {
						scene->AddNode(node);
					}
				}
				//scene->AddNode(node);

			}


		}
	}
	void CheckNode(Node3D* node, int& dx, int& dy,int mx,int my);
	void DrawNode(Node3D* node, int& dx, int& dy,QPainter& p);
	void GetMaxSize(Node3D* node, int& sy);

	virtual void paintEvent(QPaintEvent* event);
	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;

private:
	Ui::SceneGraphWidgetClass ui;
	Node3D* mCurrentNode = nullptr;
	Node3D* mDragNode = nullptr;
	Node3D* mActiveNode = nullptr;
	int max_y = 0;
	QScrollBar* mScrollLink;
	QPoint dragStartPos;
	bool isDrag = false;
	int mox, moy;
	bool openClose = false;
};
