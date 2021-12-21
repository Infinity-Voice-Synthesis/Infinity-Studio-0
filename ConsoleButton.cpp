#include "ConsoleButton.h"

ConsoleButton::ConsoleButton(QWidget *parent)
	: ClickButton(parent)
{
	this->setMouseTracking(true);
}

ConsoleButton::~ConsoleButton()
{
}

void ConsoleButton::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);
	QPainter painter(this);

	QColor col_background, col_main;

	switch (this->state)
	{
	case State::NormalState:
	{
		col_background = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["status"]["console-button"]("color-background-normal")));
		col_main = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["status"]["console-button"]("color-normal")));
		break;
	}
	case State::HoverState:
	{
		col_background = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["status"]["console-button"]("color-background-hover")));
		col_main = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["status"]["console-button"]("color-hover")));
		break;
	}
	case State::PressedState:
	{
		col_background = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["status"]["console-button"]("color-background-pressed")));
		col_main = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["status"]["console-button"]("color-pressed")));
		break;
	}
	}

	painter.fillRect(0, 0, this->width(), this->height(), col_background);

	QPen pen;
	pen.setWidth(1);
	pen.setColor(col_main);
	pen.setStyle(Qt::SolidLine);
	pen.setCapStyle(Qt::PenCapStyle::FlatCap);
	pen.setJoinStyle(Qt::PenJoinStyle::MiterJoin);
	painter.setPen(pen);

	QPolygon poly;
	poly.append(QPoint(0.25 * this->width(), 0.3 * this->height()));
	poly.append(QPoint(0.45 * this->width(), 0.45 * this->height()));
	poly.append(QPoint(0.25 * this->width(), 0.6 * this->height()));
	QLine line(0.5 * this->width(), 0.75 * this->height(), 0.75 * this->width(), 0.75 * this->height());

	painter.drawPolyline(poly);
	painter.drawLine(line);
}