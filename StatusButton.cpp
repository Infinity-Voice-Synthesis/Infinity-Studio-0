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

	double font_height = 0.6;
	StyleContainer::getContainer().getStyleObject()["status"]["button"].Get("font-height", font_height);

	int font_pixel_size_i = font_height * this->height();

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

	QPen pen;
	pen.setWidth(1);
	pen.setColor(col_main);
	pen.setStyle(Qt::SolidLine);
	pen.setJoinStyle(Qt::RoundJoin);
	pen.setCapStyle(Qt::RoundCap);
	painter.setPen(pen);

	QFont font;
	font.setPixelSize(font_pixel_size_i);
	painter.setFont(font);

	QString strTrans = QString::fromStdString(StyleContainer::getContainer().getTransObject()(this->str.toStdString()));

	int font_width = painter.fontMetrics().horizontalAdvance(strTrans);
	QPoint textPoint((this->width() / 2) - (font_width / 2), (this->height() / 2) + (painter.fontMetrics().boundingRect('I').height() / 2));
	painter.drawText(textPoint, strTrans);
}
