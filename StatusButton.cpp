#include "StatusButton.h"

StatusButton::StatusButton(QWidget *parent)
	: ClickButton(parent)
{
}

StatusButton::~StatusButton()
{
}

void StatusButton::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);

	QColor col_background, col_main;

	switch (this->state)
	{
	case State::NormalState:
	{
		col_background = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["status"]["button"]("color-background-normal")));
		col_main = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["status"]["button"]("color-normal")));
		break;
	}
	case State::HoverState:
	{
		col_background = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["status"]["button"]("color-background-hover")));
		col_main = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["status"]["button"]("color-hover")));
		break;
	}
	case State::PressedState:
	{
		col_background = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["status"]["button"]("color-background-pressed")));
		col_main = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["status"]["button"]("color-pressed")));
		break;
	}
	}

	painter.fillRect(0, 0, this->width(), this->height(), col_background);
}
