#include "TrackWidget.h"

TrackWidget::TrackWidget(QWidget *parent)
	: RefreshableWidget(parent)
{
	this->setMouseTracking(true);
}

TrackWidget::~TrackWidget()
{
}

void TrackWidget::setStateTop(bool isTop)
{
	this->isTop = isTop;
	this->update();
}

void TrackWidget::setStateBottom(bool isBottom)
{
	this->isBottom = isBottom;
	this->update();
}

void TrackWidget::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);
	QPainter painter(this);
	QSize screenSize = Infinity_global::getScreenSize();

	QColor color_background = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["central"]("color-background")));

	double head_width = 0.15, scoll_width = 0.05, ruler_height = 0.05;
	StyleContainer::getContainer().getStyleObject()["central"].Get("head-width", head_width);
	StyleContainer::getContainer().getStyleObject()["central"].Get("scoll-width", scoll_width);
	StyleContainer::getContainer().getStyleObject()["central"].Get("ruler-height", ruler_height);

	int head_width_i = screenSize.width() * head_width;
	int scoll_width_i = screenSize.width() * scoll_width;
	int ruler_height_i = screenSize.width() * ruler_height;

	bool pic_background_diy = false;
	StyleContainer::getContainer().getStyleObject().Get("pic-background-diy", pic_background_diy);

	QPen pen;
	pen.setWidth(1);
	pen.setColor(Qt::darkGray);
	pen.setStyle(Qt::SolidLine);
	pen.setCapStyle(Qt::RoundCap);
	pen.setJoinStyle(Qt::RoundJoin);
	painter.setPen(pen);

	if (pic_background_diy) {
		double background_diy_transparency = 1;
		StyleContainer::getContainer().getStyleObject()["central"].Get("background-diy-transparency", background_diy_transparency);

		QColor color_background_hover;
		if ((color_background.red() + color_background.green() + color_background.blue()) > 255 * 1.5) {
			color_background_hover.setRgb(255, 255, 255, 255 * (1 - background_diy_transparency));
		}
		else {
			color_background_hover.setRgb(0, 0, 0, 255 * (1 - background_diy_transparency));
		}

		painter.fillRect(0, 0, this->width(), this->height(), color_background_hover);
	}
	else {
		painter.fillRect(0, 0, this->width(), this->height(), color_background);
	}

	QLine head_line(head_width_i, 0, head_width_i, this->height());
	QLine rscoll_line(this->width() - scoll_width_i, 0, this->width() - scoll_width_i, this->height());
	QLine bscoll_line(0, this->height() - scoll_width_i, this->width(), this->height() - scoll_width_i);
	QLine ruler_line(0, ruler_height_i, this->width(), ruler_height_i);

	painter.drawLine(head_line);
	painter.drawLine(rscoll_line);
	if (this->isTop) {
		painter.drawLine(ruler_line);
	}
	if (this->isBottom) {
		painter.drawLine(bscoll_line);
	}
}