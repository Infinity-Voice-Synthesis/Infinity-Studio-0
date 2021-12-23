#include "VScollBar.h"

VScollBar::VScollBar(QWidget *parent)
	: RefreshableWidget(parent)
{
	this->setMouseTracking(true);
}

VScollBar::~VScollBar()
{
}

void VScollBar::paintFlags()
{
	
}

void VScollBar::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);
	QColor color_background = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["scoller"]("color-background")));
	QColor color_normal = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["scoller"]("color-normal")));
	QColor color_hover = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["scoller"]("color-hover")));
	QColor color_pressed = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["scoller"]("color-pressed")));
	QColor color_border = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["scoller"]("color-border")));

	QPainter painter(this);

	painter.fillRect(0, 0, this->width(), this->height(), color_background);
	
	QColor color;
	switch (this->state)
	{
	case State::Normal:
		color = color_normal;
		break;
	case State::Hover:
		color = color_hover;
		break;
	default:
		color = color_pressed;
		break;
	}

	QRect blockRect(0, this->height() * this->sp, this->width(), this->height() * (this->ep - this->sp));
	painter.fillRect(blockRect, color);

	QPen pen;
	pen.setWidth(1);
	pen.setStyle(Qt::SolidLine);
	pen.setCapStyle(Qt::RoundCap);
	pen.setJoinStyle(Qt::RoundJoin);
	pen.setColor(color_border);
	painter.setPen(pen);

	painter.drawRect(0, 0, this->width(), this->height());

	painter.end();
	this->paintFlags();
}

void VScollBar::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton) {
		double resize_distance = 0.02;
		StyleContainer::getContainer().getStyleObject()["scoller"].Get("resize-distance", resize_distance);
		if (this->state == State::Normal || this->state == State::Hover) {
			if (this->scaleAble) {
				if (
					event->pos().x() >= 0 && event->pos().x() <= this->width() &&
					event->pos().y() >= (this->sp - resize_distance) * this->height() && event->pos().y() <= (this->sp + resize_distance) * this->height()
					) {
					this->setCursor(Qt::CursorShape::SplitVCursor);
					this->state = State::TPressed;
					this->spt = this->sp;
					this->pressY = event->pos().y();
				}
				else if (
					event->pos().x() >= 0 && event->pos().x() <= this->width() &&
					event->pos().y() >= (this->ep - resize_distance) * this->height() && event->pos().y() <= (this->ep + resize_distance) * this->height()
					) {
					this->setCursor(Qt::CursorShape::SplitVCursor);
					this->state = State::BPressed;
					this->ept = this->ep;
					this->pressY = event->pos().y();
				}
				else if (
					event->pos().x() >= 0 && event->pos().x() <= this->width() &&
					event->pos().y() >= this->sp * this->height() && event->pos().y() <= this->ep * this->height()
					) {
					this->setCursor(Qt::CursorShape::ClosedHandCursor);
					this->state = State::CPressed;
					this->spt = this->sp;
					this->ept = this->ep;
					this->pressY = event->pos().y();
				}
				else {
					int spi = event->pos().y() - ((this->ep - this->sp) / 2) * this->height();
					if (spi < 0) {
						spi = 0;
					}
					if (spi + (this->ep - this->sp) * this->height() > this->height()) {
						spi = this->height() - (this->ep - this->sp) * this->height();
					}
					double spn = (double)spi / (double)this->height();
					double epn = spn + (this->ep - this->sp);
					this->sp = spn;
					this->ep = epn;
					emit this->valueChanged(this->sp, this->ep);

					this->setCursor(Qt::CursorShape::ClosedHandCursor);
					this->state = State::CPressed;
					this->spt = this->sp;
					this->ept = this->ep;
					this->pressY = event->pos().y();
				}
			}
			else {
				if (
					event->pos().x() >= 0 && event->pos().x() <= this->width() &&
					event->pos().y() >= this->sp * this->height() && event->pos().y() <= this->ep * this->height()
					) {
					this->setCursor(Qt::CursorShape::ClosedHandCursor);
					this->state = State::CPressed;
					this->spt = this->sp;
					this->ept = this->ep;
					this->pressY = event->pos().y();
				}
				else {
					int spi = event->pos().y() - ((this->ep - this->sp) / 2) * this->height();
					if (spi < 0) {
						spi = 0;
					}
					if (spi + (this->ep - this->sp) * this->height() > this->height()) {
						spi = this->height() - (this->ep - this->sp) * this->height();
					}
					double spn = (double)spi / (double)this->height();
					double epn = spn + (this->ep - this->sp);
					this->sp = spn;
					this->ep = epn;
					emit this->valueChanged(this->sp, this->ep);

					this->setCursor(Qt::CursorShape::ClosedHandCursor);
					this->state = State::CPressed;
					this->spt = this->sp;
					this->ept = this->ep;
					this->pressY = event->pos().y();
				}
			}

			this->update();
		}
	}

}

void VScollBar::mouseMoveEvent(QMouseEvent* event)
{
	double resize_distance = 0.02;
	StyleContainer::getContainer().getStyleObject()["scoller"].Get("resize-distance", resize_distance);

	this->mousePos = event->pos();

	if (this->state == State::Normal || this->state == State::Hover) {
		if (this->scaleAble) {
			if (
				event->pos().x() >= 0 && event->pos().x() <= this->width() &&
				event->pos().y() >= (this->sp - resize_distance) * this->height() && event->pos().y() <= (this->sp + resize_distance) * this->height()
				) {
				this->setCursor(Qt::CursorShape::SplitVCursor);
				this->state = State::Hover;
			}
			else if (
				event->pos().x() >= 0 && event->pos().x() <= this->width() &&
				event->pos().y() >= (this->ep - resize_distance) * this->height() && event->pos().y() <= (this->ep + resize_distance) * this->height()
				) {
				this->setCursor(Qt::CursorShape::SplitVCursor);
				this->state = State::Hover;
			}
			else if (
				event->pos().x() >= 0 && event->pos().x() <= this->width() &&
				event->pos().y() >= this->sp * this->height() && event->pos().y() <= this->ep * this->height()
				) {
				this->setCursor(Qt::CursorShape::OpenHandCursor);
				this->state = State::Hover;
			}
			else {
				this->setCursor(Qt::CursorShape::ArrowCursor);
				this->state = State::Normal;
			}
		}
		else {
			if (
				event->pos().x() >= 0 && event->pos().x() <= this->width() &&
				event->pos().y() >= this->sp * this->height() && event->pos().y() <= this->ep * this->height()
				) {
				this->setCursor(Qt::CursorShape::OpenHandCursor);
				this->state = State::Hover;
			}
			else {
				this->setCursor(Qt::CursorShape::ArrowCursor);
				this->state = State::Normal;
			}
		}
		
		this->update();
	}
	else {
		switch (this->state)
		{
		case State::TPressed:
		{
			double spn = this->spt + ((double)(event->pos().y() - this->pressY) / (double)this->height());
			if (spn < 0) {
				spn = 0;
			}
			if (spn > this->ep) {
				spn = this->ep;
			}
			if (this->ep - spn > this->maxPer) {
				spn = this->ep - this->maxPer;
			}
			if (this->ep - spn < this->minPer) {
				spn = this->ep - this->minPer;
			}
			this->sp = spn;
			break;
		}
		case State::BPressed:
		{
			double epn = this->ept + ((double)(event->pos().y() - this->pressY) / (double)this->height());
			if (epn > 1) {
				epn = 1;
			}
			if (epn < this->sp) {
				epn = this->sp;
			}
			if (epn - this->sp > this->maxPer) {
				epn = this->sp + this->maxPer;
			}
			if (epn - this->sp < this->minPer) {
				epn = this->sp + this->minPer;
			}
			this->ep = epn;
			break;
		}
		case State::CPressed:
		{
			double spn = this->spt + ((double)(event->pos().y() - this->pressY) / (double)this->height());
			double epn = this->ept + ((double)(event->pos().y() - this->pressY) / (double)this->height());
			if (spn < 0) {
				spn = 0;
				epn = spn + (this->ept - this->spt);
			}
			if (epn > 1) {
				epn = 1;
				spn = epn - (this->ept - this->spt);
			}
			this->sp = spn;
			this->ep = epn;
			break;
		}
		}

		this->update();
		emit this->valueChanged(this->sp, this->ep);
	}
}

void VScollBar::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton) {
		if (this->state == State::BPressed || this->state == State::CPressed || this->state == State::TPressed) {
			double resize_distance = 0.02;
			StyleContainer::getContainer().getStyleObject()["scoller"].Get("resize-distance", resize_distance);

			if (this->scaleAble) {
				if (
					event->pos().x() >= 0 && event->pos().x() <= this->width() &&
					event->pos().y() >= (this->sp - resize_distance) * this->height() && event->pos().y() <= (this->sp + resize_distance) * this->height()
					) {
					this->setCursor(Qt::CursorShape::SplitVCursor);
					this->state = State::Hover;
				}
				else if (
					event->pos().x() >= 0 && event->pos().x() <= this->width() &&
					event->pos().y() >= (this->ep - resize_distance) * this->height() && event->pos().y() <= (this->ep + resize_distance) * this->height()
					) {
					this->setCursor(Qt::CursorShape::SplitVCursor);
					this->state = State::Hover;
				}
				else if (
					event->pos().x() >= 0 && event->pos().x() <= this->width() &&
					event->pos().y() >= this->sp * this->height() && event->pos().y() <= this->ep * this->height()
					) {
					this->setCursor(Qt::CursorShape::OpenHandCursor);
					this->state = State::Hover;
				}
				else {
					this->setCursor(Qt::CursorShape::ArrowCursor);
					this->state = State::Normal;
				}
			}
			else {
				if (
					event->pos().x() >= 0 && event->pos().x() <= this->width() &&
					event->pos().y() >= this->sp * this->height() && event->pos().y() <= this->ep * this->height()
					) {
					this->setCursor(Qt::CursorShape::OpenHandCursor);
					this->state = State::Hover;
				}
				else {
					this->setCursor(Qt::CursorShape::ArrowCursor);
					this->state = State::Normal;
				}
			}

			this->spt = 0;
			this->ept = 1;
			this->pressY = 0;

			this->update();
			emit this->valueChanged(this->sp, this->ep);
		}
	}
}

void VScollBar::leaveEvent(QEvent* event)
{
	this->setCursor(Qt::CursorShape::ArrowCursor);
	this->state = State::Normal;
	this->spt = 0;
	this->ept = 1;
	this->pressY = 0;
	this->update();
}

QPair<double,double> VScollBar::setValue(double sp, double ep)
{
	double resize_distance = 0.02;
	StyleContainer::getContainer().getStyleObject()["scoller"].Get("resize-distance", resize_distance);

	if (ep - sp < this->minPer) {
		double cent = (sp + ep) / 2;
		sp = cent - (this->minPer / 2);
		ep = cent + (this->minPer / 2);
	}
	if (ep - sp > this->maxPer) {
		double cent = (sp + ep) / 2;
		sp = cent - (this->maxPer / 2);
		ep = cent + (this->maxPer / 2);
	}
	if (sp < 0) {
		double delta = ep - sp;
		sp = 0;
		ep = sp + delta;
	}
	if (ep > 1) {
		double delta = ep - sp;
		ep = 1;
		sp = ep - delta;
	}

	if (this->scaleAble) {
		if (
			this->mousePos.x() >= 0 && this->mousePos.x() <= this->width() &&
			this->mousePos.y() >= (this->sp - resize_distance) * this->height() && this->mousePos.y() <= (this->sp + resize_distance) * this->height()
			) {
			this->setCursor(Qt::CursorShape::SplitVCursor);
			this->state = State::Hover;
		}
		else if (
			this->mousePos.x() >= 0 && this->mousePos.x() <= this->width() &&
			this->mousePos.y() >= (this->ep - resize_distance) * this->height() && this->mousePos.y() <= (this->ep + resize_distance) * this->height()
			) {
			this->setCursor(Qt::CursorShape::SplitVCursor);
			this->state = State::Hover;
		}
		else if (
			this->mousePos.x() >= 0 && this->mousePos.x() <= this->width() &&
			this->mousePos.y() >= this->sp * this->height() && this->mousePos.y() <= this->ep * this->height()
			) {
			this->setCursor(Qt::CursorShape::OpenHandCursor);
			this->state = State::Hover;
		}
		else {
			this->setCursor(Qt::CursorShape::ArrowCursor);
			this->state = State::Normal;
		}
	}
	else {
		if (
			this->mousePos.x() >= 0 && this->mousePos.x() <= this->width() &&
			this->mousePos.y() >= this->sp * this->height() && this->mousePos.y() <= this->ep * this->height()
			) {
			this->setCursor(Qt::CursorShape::OpenHandCursor);
			this->state = State::Hover;
		}
		else {
			this->setCursor(Qt::CursorShape::ArrowCursor);
			this->state = State::Normal;
		}
	}
	
	this->spt = 0;
	this->ept = 1;
	this->pressY = 0;
	this->sp = sp;
	this->ep = ep;
	this->update();
	return qMakePair(sp, ep);
}

void VScollBar::wheelEvent(QWheelEvent* event)
{
	emit this->wheelChanged(event->angleDelta().y());
}

QPair<double, double> VScollBar::getValue()
{
	return qMakePair(this->sp, this->ep);
}