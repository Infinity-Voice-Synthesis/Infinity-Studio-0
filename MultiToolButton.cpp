#include "MultiToolButton.h"

MultiToolButton::MultiToolButton(QWidget *parent)
	: ToolButton(parent)
{
	this->setMouseTracking(true);
}

MultiToolButton::~MultiToolButton()
{
}

void MultiToolButton::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton) {
		switch (this->state)
		{
		case ButtonState::Normal:
		{
			this->state = ButtonState::Pressed;
			break;
		}
		case ButtonState::Hover:
		{
			this->state = ButtonState::Pressed;
			break;
		}
		case ButtonState::Pressed:
		{
			break;
		}
		case ButtonState::Checked:
		{
			this->state = ButtonState::Pressed;
			break;
		}
		}
		this->update();
	}
}

void MultiToolButton::mouseMoveEvent(QMouseEvent* event)
{
	if (this->inWidget(event->pos())) {
		this->setCursor(Qt::PointingHandCursor);
		switch (this->state)
		{
		case ButtonState::Normal:
		{
			this->state = ButtonState::Hover;
			break;
		}
		case ButtonState::Hover:
		{
			break;
		}
		case ButtonState::Pressed:
		{
			break;
		}
		case ButtonState::Checked:
		{
			this->state = ButtonState::Hover;
			break;
		}
		}
	}
	else {
		this->setCursor(Qt::ArrowCursor);
		switch (this->state)
		{
		case ButtonState::Normal:
		{
			break;
		}
		case ButtonState::Hover:
		{
			if (this->pressFlag) {
				this->state = ButtonState::Checked;
			}
			else {
				this->state = ButtonState::Normal;
			}
			break;
		}
		case ButtonState::Pressed:
		{
			break;
		}
		case ButtonState::Checked:
		{
			break;
		}
		}
	}
	this->update();
}

void MultiToolButton::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton) {
		switch (this->state)
		{
		case ButtonState::Normal:
		{
			break;
		}
		case ButtonState::Hover:
		{
			break;
		}
		case ButtonState::Pressed:
		{
			if (this->inWidget(event->pos())) {
				this->state = ButtonState::Hover;
				if (!this->pressFlag) {
					this->pressFlag = true;
					emit this->selected(this->id);
				}
			}
			else {
				if (!this->pressFlag) {
					this->pressFlag = true;
					this->state = ButtonState::Normal;
					emit this->selected(this->id);
				}
			}
			break;
		}
		case ButtonState::Checked:
		{
			break;
		}
		}
		this->update();
	}
}
