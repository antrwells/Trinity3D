#pragma once

#include <QWidget>
#include "ui_SceneViewport.h"
#include "QDirect3D12Widget.h"
#include "Texture2D.h"
#include "SmartDraw.h"

class NodeCamera;

class SceneViewport : public QDirect3D12Widget
{
	Q_OBJECT

signals:

	void ViewportReady();

public:
	SceneViewport(QWidget *parent = nullptr);
	~SceneViewport();

protected:

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
	
};

