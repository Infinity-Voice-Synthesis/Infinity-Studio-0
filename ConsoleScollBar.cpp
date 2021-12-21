#include "ConsoleScollBar.h"

ConsoleScollBar::ConsoleScollBar(QWidget *parent)
	: VScollBar(parent)
{
	this->scaleAble = false;
}

ConsoleScollBar::~ConsoleScollBar()
{
}

void ConsoleScollBar::setTips(QVector<double> tips)
{
	this->tips = tips;
	this->update();
}

void ConsoleScollBar::paintFlags()
{
	QPainter painter(this);
	
	QColor color_tip = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["console"]("scoll-tip-color")));

	double scoll_tip_width = 0.15;
	StyleContainer::getContainer().getStyleObject()["console"].Get("scoll-tip-width", scoll_tip_width);

	int scoll_tip_width_i = this->width() * scoll_tip_width;

	for (auto i : this->tips) {
		QRect rect((double)this->width() / (double)2 - (double)scoll_tip_width_i / (double)2, (double)this->height() * i - (double)scoll_tip_width_i / (double)2, scoll_tip_width_i, scoll_tip_width_i);
		painter.fillRect(rect, color_tip);
	}
}
