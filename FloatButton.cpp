#include "FloatButton.h"

FloatButton::FloatButton(QWidget* parent)
	: TitleButton(parent)
{
}

FloatButton::~FloatButton()
{
}

void FloatButton::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);

	QPainter painter(this);

	QColor col_background, col_main;

	switch (this->state)
	{
	case State::NormalState:
	{
		col_background = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["title"]["button-float"]("color-background-normal")));
		col_main = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["title"]["button-float"]("color-normal")));
		break;
	}
	case State::HoverState:
	{
		col_background = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["title"]["button-float"]("color-background-hover")));
		col_main = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["title"]["button-float"]("color-hover")));
		break;
	}
	case State::PressedState:
	{
		col_background = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["title"]["button-float"]("color-background-pressed")));
		col_main = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["title"]["button-float"]("color-pressed")));
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

	QBrush brush;
	brush.setColor(col_background);
	brush.setStyle(Qt::SolidPattern);
	painter.setBrush(brush);

	double button_delta = 0.25;
	StyleContainer::getContainer().getStyleObject()["title"].Get("button-delta", button_delta);

	double button_center = 0.5;
	StyleContainer::getContainer().getStyleObject()["title"].Get("button-center", button_center);

	int center_size = qMin((double)((double)this->width() * button_center), (double)((double)this->height() * button_center));

	QRect rect1(this->width() / 2 - center_size / 2 + center_size * button_delta, this->height() / 2 - center_size / 2, center_size - center_size * button_delta, center_size - center_size * button_delta);
	QRect rect2(this->width() / 2 - center_size / 2, this->height() / 2 - center_size / 2 + center_size * button_delta, center_size - center_size * button_delta, center_size - center_size * button_delta);

	painter.drawRect(rect1);
	painter.drawRect(rect2);
}
