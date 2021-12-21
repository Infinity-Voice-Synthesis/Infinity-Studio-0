#pragma once

#include <QWidget>
#include "Infinity_global.h"
#include "Infinity_Events.h"
#include "StyleContainer.h"
#include <QPainter>
#include <QVector>
#include "TrackWidget.h"
#include "NoteWidget.h"
#include "ParamWidget.h"
#include <QMessageBox>
#include <QMouseEvent>
#include "RefreshableWidget.h"

#pragma warning(disable:26812)//I don't wanna use enum class for CentralWidget::CentralState

class CentralWidget : public RefreshableWidget
{
	Q_OBJECT

public:
	CentralWidget(QWidget *parent = Q_NULLPTR);
	~CentralWidget();

private:
	enum CentralState {
		OffState = 0,			//0000
		TrackViewState = 1,		//0001
		NoteViewState = 2,		//0010
		ParamViewState = 4,		//0100
		TrackAndNoteState = 3,	//0011
		TrackAndParamState = 5,	//0101
		NoteAndParamState = 6,	//0110
		AllState = 7			//0111
	};
	enum class SplitState {
		Normal = 0,
		Split0 = 1,
		Split1 = 2
	};

	QVector<double> splitLine = { 0.5,0 };

	CentralState state = CentralState::TrackAndNoteState;
	SplitState splitState = SplitState::Normal;

	double splitTemp = 0;
	int pressedY = 0;

	TrackWidget* trackw = nullptr;
	NoteWidget* notew = nullptr;
	ParamWidget* paramw = nullptr;

protected:
	void resizeAll()override;
	void paintEvent(QPaintEvent* event)override;

	void mousePressEvent(QMouseEvent* event)override;
	void mouseReleaseEvent(QMouseEvent* event)override;
	void mouseMoveEvent(QMouseEvent* event)override;
	void leaveEvent(QEvent* event)override;

public slots:
	void on_viewShow(QString id, bool checked);

signals:
	void centralFastReady(bool fast);
};
