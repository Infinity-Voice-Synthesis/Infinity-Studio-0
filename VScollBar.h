#pragma once

#include "RefreshableWidget.h"
#include <QPainter>
#include <QMouseEvent>
#include "StyleContainer.h"
#include <QWheelEvent>

class VScollBar : public RefreshableWidget
{
	Q_OBJECT

public:
	VScollBar(QWidget *parent = Q_NULLPTR);
	~VScollBar();

	QPair<double, double> setValue(double sp, double ep);
	QPair<double, double> getValue();

protected:
	double sp = 0, ep = 1;
	double minPer = 0, maxPer = 1;
	bool scaleAble = true;

	double spt = 0, ept = 1;
	int pressY = 0;

	QPoint mousePos;

	virtual void paintFlags();
	void paintEvent(QPaintEvent* event)override;
	void mousePressEvent(QMouseEvent* event)override;
	void mouseMoveEvent(QMouseEvent* event)override;
	void mouseReleaseEvent(QMouseEvent* event)override;
	void leaveEvent(QEvent* event)override;
	void wheelEvent(QWheelEvent* event)override;

	enum class State {
		Normal,
		Hover,
		TPressed,
		CPressed,
		BPressed
	};

	State state = State::Normal;

signals:
	void valueChanged(double sp, double ep);
	void wheelChanged(int delta);
};
