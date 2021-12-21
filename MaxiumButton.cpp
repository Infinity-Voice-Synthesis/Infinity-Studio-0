﻿#include "MaxiumButton.h"

MaxiumButton::MaxiumButton(QWidget* parent)
	: TitleButton(parent)
{
}

MaxiumButton::~MaxiumButton()
{
}

void MaxiumButton::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);

	QPainter painter(this);

	QColor col_background, col_main;

	switch (this->state)
	{
	case State::NormalState:
	{
		col_background = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["title"]["button-maximum"]("color-background-normal")));
		col_main = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["title"]["button-maximum"]("color-normal")));
		break;
	}
	case State::HoverState:
	{
		col_background = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["title"]["button-maximum"]("color-background-hover")));
		col_main = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["title"]["button-maximum"]("color-hover")));
		break;
	}
	case State::PressedState:
	{
		col_background = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["title"]["button-maximum"]("color-background-pressed")));
		col_main = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["title"]["button-maximum"]("color-pressed")));
		break;
	}
	}

	painter.fillRect(0, 0, this->width(), this->height(), col_background);

	QPen pen;
	pen.setWidth(2);
	pen.setColor(col_main);
	pen.setStyle(Qt::SolidLine);
	pen.setCapStyle(Qt::RoundCap);
	pen.setJoinStyle(Qt::RoundJoin);
	painter.setPen(pen);

	double button_center = 0.5;
	StyleContainer::getContainer().getStyleObject()["title"].Get("button-center", button_center);

	int center_size = qMin((double)((double)this->width() * button_center), (double)((double)this->height() * button_center));

	QRect rect(this->width() / 2 - center_size / 2, this->height() / 2 - center_size / 2, center_size, center_size);

	painter.drawRect(rect);
}
