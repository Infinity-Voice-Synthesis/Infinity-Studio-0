#include "VMStateButton.h"

VMStateButton::VMStateButton(QWidget *parent)
	: StatusButton(parent)
{
	this->str = "VMSB_Free";
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
	emit this->activeCritical();
}
