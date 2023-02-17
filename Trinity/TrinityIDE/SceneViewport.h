#pragma once

#include <QWidget>
#include "ui_SceneViewport.h"
#include "QDirect3D12Widget.h"
#include "Texture2D.h"
#include "SmartDraw.h"
#include "qdrag.h"
#include <QDrag>
#include "qmimedata.h"
#include "TrinityGlobal.h"
#include "SceneGraph.h"


class NodeCamera;
class NodeEntity;
class MeshLines;

enum GizmoMode {

	Translate,Rotate,Scale

};

enum GizmoSpace {

	Global,Local

};

class SceneViewport : public QDirect3D12Widget
{
	Q_OBJECT

signals:

	void ViewportReady();

public:
	SceneViewport(QWidget *parent = nullptr);
	~SceneViewport();

	static void BeginPlay() {

		mThis->Play();

	}

	static void Pause() {

	}

	static void Stop()
	{
		mThis->StopPlay();
	}

	static SceneViewport* mThis;

	void Play();
	void StopPlay();

	void SetMode(int mode)
	{
		mGizMode = (GizmoMode)mode;
		if (mode == 0) {
			mCurrentGizmo = mTranslateGizmo;
		}
		else if (mode == 1)
		{
			mCurrentGizmo = mRotateGizmo;
		}
		else if (mode == 2) {
			mCurrentGizmo = mScaleGizmo;
		}
	}
	void SetSpace(int mode) {

		if (mode == 0) {

			mGizmoSpace = GizmoSpace::Local;

		}
		if (mode == 1)
		{

			mGizmoSpace = GizmoSpace::Global;
		}

	}

protected:
	void dragEnterEvent(QDragEnterEvent* event)
	{
		if (event->mimeData()->hasText()) {
			if (event->mimeData()->property("type").toString() == QString("mesh"))
			{
				event->acceptProposedAction();
			}
		}
	}

	void dragMoveEvent(QDragMoveEvent* event)
	{
		if (event->mimeData()->hasText()) {
			if (event->mimeData()->property("type").toString() == QString("mesh"))
			{
				event->acceptProposedAction();
			}
		}
	}

	void dropEvent(QDropEvent* event)
	{
		if (event->mimeData()->hasText()) {

			if (event->mimeData()->property("type").toString() == QString("mesh"))
			{
				//	event->acceptProposedAction();

				//setText(event->mimeData()->text());
				event->acceptProposedAction();

				auto scene = TrinityGlobal::CurrentScene;

				auto node = scene->ReadNodeFromFile(std::string(event->mimeData()->text().toStdString()));

				scene->AddNode(node);

			}

		}
	}

	void createGrid();
	void resizeEvent(QResizeEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	bool eventFilter(QObject* obj, QEvent* event) override;
protected:
	void keyPressEvent(QKeyEvent* event) override
	{
		//qDebug() << "Key pressed: " << event->key();
		int key = event->key();

		float moveSpeed = 0.1f;

		if (event->modifiers() == Qt::ShiftModifier)
		{
			moveSpeed = 0.3f;
		}

		switch (key) {
		case Qt::Key::Key_Alt:
			mSpeedMod = 0.4f;
			break;
		case Qt::Key::Key_Shift:
			mSpeedMod = 2.0f;
			break;
		case Qt::Key::Key_W:
			mCamMoveY = moveSpeed;
			break;
		case Qt::Key::Key_A:
			mCamMoveX = -moveSpeed;
			break;
		case Qt::Key::Key_S :
			mCamMoveY = -moveSpeed;
			break;
		case Qt::Key::Key_D:
			mCamMoveX = moveSpeed;
			break;

		}

	}

	void keyReleaseEvent(QKeyEvent* event) override
	{
		qDebug() << "Key released: " << event->key();

		int key = event->key();

		switch (key) {
		case Qt::Key::Key_Alt:
			mSpeedMod = 1.0f;
			break;
		case Qt::Key::Key_Shift:
			mSpeedMod = 1.0f;
			break;
		case Qt::Key::Key_W:
			mCamMoveY = 0;
			break;
		case Qt::Key::Key_A:
			mCamMoveX = 0;
			break;
		case Qt::Key::Key_S:
			mCamMoveY = 0;
			break;
		case Qt::Key::Key_D:
			mCamMoveX = 0;
			break;

		}
	}

private slots:
	void LoadResources();
	void RenderScene();


private:
	Ui::SceneViewportClass ui;
	Texture2D* mTex1;
	Texture2D* iconLight, * iconCam, * iconEmpty;
	SmartDraw* mDraw;
	NodeCamera* mEditCam;
	float mMoveX, mMoveY, mMoveZ;
	bool first_Move = true;
	float mLastX, mLastY;
	float mCamPitch = 0;
	float mCamYaw = 0;
	bool mRotateLock = false;
	float mCamMoveX = 0;
	float mCamMoveY = 0;
	float mSpeedMod = 1.0f;
	NodeEntity* mTranslateGizmo;
	NodeEntity* mRotateGizmo;
	NodeEntity* mScaleGizmo;
	NodeEntity* mCurrentGizmo;
	GizmoMode mGizMode = GizmoMode::Translate;
	GizmoSpace mGizmoSpace = GizmoSpace::Global;
	//
	bool gLock_x, gLock_y, gLock_z;
	bool gLock = false;
	bool mLeftDown = false;
	float mTranslateRatio = 0.02f;
	float mRotateRatio = 0.22f;
	float mScaleRatio = 0.07f;
	MeshLines* mEditGrid = nullptr;
	bool mPlaying = false;

};

