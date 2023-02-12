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
			event->acceptProposedAction();
		}
	}

	void dragMoveEvent(QDragMoveEvent* event)
	{
		if (event->mimeData()->hasText()) {
			event->acceptProposedAction();
		}
	}

	void dropEvent(QDropEvent* event)
	{
		if (event->mimeData()->hasText()) {
			//setText(event->mimeData()->text());
			event->acceptProposedAction();

			auto scene = TrinityGlobal::CurrentScene;

			auto node = scene->ReadNodeFromFile(std::string(event->mimeData()->text().toStdString()));

			if (mActiveNode != nullptr) {
				mActiveNode->AddNode(node);
			}
			else {
				scene->AddNode(node);
			}
			//scene->AddNode(node);




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
	Node3D* mActiveNode = nullptr;
	int max_y = 0;
	QScrollBar* mScrollLink;
};
