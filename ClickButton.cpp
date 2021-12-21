#include "ClickButton.h"

ClickButton::ClickButton(QWidget* parent)
	: RefreshableWidget(parent)
{
	this->setMouseTracking(true);
}

ClickButton::~ClickButton()
{
}

void ClickButton::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton) {
		if (this->inWidget(event)) {
			this->state = State::PressedState;
			this->buttonPressed = true;
		}
		this->update();
	}
}

void ClickButton::mouseMoveEvent(QMouseEvent* event)
{
	if (this->inWidget(event)) {
		if (this->buttonPressed) {
			this->state = State::PressedState;
		}
		else {
			this->state = State::HoverState;
		}
	}
	else {
		if (this->buttonPressed) {
			this->state = State::HoverState;
		}
		else {
			this->state = State::NormalState;
		}
	}
	this->update();
}

void ClickButton::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton && this->buttonPressed) {
		if (this->inWidget(event)) {
			if (this->state == State::PressedState) {
				this->state = State::NormalState;
				this->buttonPressed = false;
				this->update();
				emit clicked();
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

void ClickButton::leaveEvent(QEvent* event)
{
	Q_UNUSED(event);
	this->state = State::NormalState;
	this->buttonPressed = false;
	this->update();
}

bool ClickButton::inWidget(QMouseEvent* event)
{
	return
		event->pos().x() >= 0 &&
		event->pos().x() <= this->width() &&
		event->pos().y() >= 0 &&
		event->pos().y() <= this->height();
}
