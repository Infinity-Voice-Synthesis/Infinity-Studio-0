#pragma once

#include <QWidget>
#include <QMouseEvent>
#include "RefreshableWidget.h"

class ClickButton : public RefreshableWidget
{
	Q_OBJECT
public:
	ClickButton(QWidget* parent = Q_NULLPTR);
	~ClickButton();

private:
	bool buttonPressed = false;

	bool inWidget(QMouseEvent* event);

protected:
	void mousePressEvent(QMouseEvent* event)override;
	void mouseMoveEvent(QMouseEvent* event)override;
	void mouseReleaseEvent(QMouseEvent* event)override;
	void leaveEvent(QEvent* event)override;

	enum class State {
		NormalState,
		HoverState,
		PressedState
	};

	State state = State::NormalState;
signals:
	void clicked();
};
