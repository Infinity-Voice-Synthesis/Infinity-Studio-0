#include "VMStateButton.h"

VMStateButton::VMStateButton(QWidget *parent)
	: StatusButton(parent)
{
	this->str = "VMSB_Free";
	this->clickTimer.setSingleShot(true);
	connect(&(this->clickTimer), &QTimer::timeout, this, &VMStateButton::clicked);
}

VMStateButton::~VMStateButton()
{
}

void VMStateButton::setVMRunning(bool running)
{
	if (running) {
		this->str = "VMSB_Busy";
	}
	else {
		this->str = "VMSB_Free";
	}
	this->update();
}

void VMStateButton::mouseDoubleClickEvent(QMouseEvent* event)
{
	Q_UNUSED(event);
	this->clickTimer.stop();
	emit this->activeCritical();
}

void VMStateButton::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton && this->buttonPressed) {
		if (this->inWidget(event)) {
			if (this->state == State::PressedState) {
				this->state = State::NormalState;
				this->buttonPressed = false;
				this->update();
				this->clickTimer.start(200);
				return;
			}
			this->state = State::HoverState;
		}
		else {
			this->state = State::NormalState;
		}
		this->buttonPressed = false;
		this->update();
	}
}