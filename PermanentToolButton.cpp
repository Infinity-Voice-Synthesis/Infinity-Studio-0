#include "PermanentToolButton.h"

PermanentToolButton::PermanentToolButton(QWidget* parent)
	: RefreshableWidget(parent)
{
	connect(&(Infinity_Events::getClass()), &Infinity_Events::resource_refresh, this, &PermanentToolButton::on_resourceRefresh);
	this->setMouseTracking(true);
}

PermanentToolButton::~PermanentToolButton()
{
}

void PermanentToolButton::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);

	QPainter painter(this);
	painter.setRenderHints(QPainter::SmoothPixmapTransform);

	double bar_width = 0.05, icon_cx = 0.5, icon_cy = 0.5;
	StyleContainer::getContainer().getStyleObject()["tools"].Get("bar-width", bar_width);
	StyleContainer::getContainer().getStyleObject()["tools"].Get("icon-cx", icon_cx);
	StyleContainer::getContainer().getStyleObject()["tools"].Get("icon-cy", icon_cy);

	int bar_width_i = bar_width * this->width();

	QColor color_normal = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["tools"][this->id.toStdString()]("color-normal-1")));
	QColor color_hover = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["tools"][this->id.toStdString()]("color-hover-1")));
	QColor color_pressed = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["tools"][this->id.toStdString()]("color-pressed-1")));
	QColor color_checked = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["tools"][this->id.toStdString()]("color-normal-2")));
	QColor color_chover = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["tools"][this->id.toStdString()]("color-hover-2")));
	QColor color_cpressed = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["tools"][this->id.toStdString()]("color-pressed-2")));
	QColor color_background_normal = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["tools"][this->id.toStdString()]("color-background-normal-1")));
	QColor color_background_hover = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["tools"][this->id.toStdString()]("color-background-hover-1")));
	QColor color_background_pressed = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["tools"][this->id.toStdString()]("color-background-pressed-1")));
	QColor color_background_checked = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["tools"][this->id.toStdString()]("color-background-normal-2")));
	QColor color_background_chover = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["tools"][this->id.toStdString()]("color-background-hover-2")));
	QColor color_background_cpressed = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["tools"][this->id.toStdString()]("color-background-pressed-2")));

	QPixmap& icon_normal = StyleContainer::getContainer().getPix("button-" + this->id + "-icon-normal-1");
	QPixmap& icon_hover = StyleContainer::getContainer().getPix("button-" + this->id + "-icon-hover-1");
	QPixmap& icon_pressed = StyleContainer::getContainer().getPix("button-" + this->id + "-icon-pressed-1");
	QPixmap& icon_checked = StyleContainer::getContainer().getPix("button-" + this->id + "-icon-normal-2");
	QPixmap& icon_chover = StyleContainer::getContainer().getPix("button-" + this->id + "-icon-hover-2");
	QPixmap& icon_cpressed = StyleContainer::getContainer().getPix("button-" + this->id + "-icon-pressed-2");

	QPixmap* icon = nullptr;
	QColor color, color_background;

	switch (this->state)
	{
	case ButtonState::Normal:
	{
		icon = &icon_normal;
		color = color_normal;
		color_background = color_background_normal;
		break;
	}
	case ButtonState::Hover:
	{
		if (this->pressFlag) {
			icon = &icon_chover;
			color = color_chover;
			color_background = color_background_chover;
		}
		else {
			icon = &icon_hover;
			color = color_hover;
			color_background = color_background_hover;
		}
		break;
	}
	case ButtonState::Pressed:
	{
		if (this->pressFlag) {
			icon = &icon_cpressed;
			color = color_cpressed;
			color_background = color_background_cpressed;
		}
		else {
			icon = &icon_pressed;
			color = color_pressed;
			color_background = color_background_pressed;
		}
		break;
	}
	case ButtonState::Checked:
	{
		icon = &icon_checked;
		color = color_checked;
		color_background = color_background_checked;
		break;
	}
	}

	QRect barRect;
	int icon_centx = 0, icon_centy = 0;
	int icon_posx = 0, icon_posy = 0;

	if (this->left) {
		barRect = QRect(0, 0, bar_width_i, this->height());
		icon_centx = bar_width_i + (this->width() - bar_width_i) * icon_cx;
		icon_centy = this->height() * icon_cy;
	}
	else {
		barRect = QRect(this->width() - bar_width_i, 0, bar_width_i, this->height());
		icon_centx = (this->width() - bar_width_i) * icon_cx;
		icon_centy = this->height() * icon_cy;
	}

	icon_posx = icon_centx - icon->width() / 2;
	icon_posy = icon_centy - icon->height() / 2;

	painter.fillRect(0, 0, this->width(), this->height(), color_background);
	QRect icon_rect(icon_posx, icon_posy, icon->width(), icon->height());
	painter.drawPixmap(icon_rect, *icon);
	painter.fillRect(barRect, color);
}

void PermanentToolButton::on_resourceRefresh()
{
	StyleContainer::getContainer().loadPix("button-" + this->id + "-icon-normal-1", QString::fromStdString(StyleContainer::getContainer().getStyleObject()["tools"][this->id.toStdString()]("icon-normal-1")));
	StyleContainer::getContainer().loadPix("button-" + this->id + "-icon-hover-1", QString::fromStdString(StyleContainer::getContainer().getStyleObject()["tools"][this->id.toStdString()]("icon-hover-1")));
	StyleContainer::getContainer().loadPix("button-" + this->id + "-icon-pressed-1", QString::fromStdString(StyleContainer::getContainer().getStyleObject()["tools"][this->id.toStdString()]("icon-pressed-1")));
	StyleContainer::getContainer().loadPix("button-" + this->id + "-icon-normal-2", QString::fromStdString(StyleContainer::getContainer().getStyleObject()["tools"][this->id.toStdString()]("icon-normal-2")));
	StyleContainer::getContainer().loadPix("button-" + this->id + "-icon-hover-2", QString::fromStdString(StyleContainer::getContainer().getStyleObject()["tools"][this->id.toStdString()]("icon-hover-2")));
	StyleContainer::getContainer().loadPix("button-" + this->id + "-icon-pressed-2", QString::fromStdString(StyleContainer::getContainer().getStyleObject()["tools"][this->id.toStdString()]("icon-pressed-2")));
	this->resizeAll();
	this->update();
}

void PermanentToolButton::resizeAll()
{
	double bar_width = 0.05, icon_cx = 0.5, icon_cy = 0.5, icon_px = 0.8, icon_py = 0.8;
	StyleContainer::getContainer().getStyleObject()["tools"].Get("bar-width", bar_width);
	StyleContainer::getContainer().getStyleObject()["tools"].Get("icon-cx", icon_cx);
	StyleContainer::getContainer().getStyleObject()["tools"].Get("icon-cy", icon_cy);
	StyleContainer::getContainer().getStyleObject()["tools"].Get("icon-px", icon_px);
	StyleContainer::getContainer().getStyleObject()["tools"].Get("icon-py", icon_py);

	int bar_width_i = bar_width * this->width();

	QRect barRect;
	int icon_centx = 0, icon_centy = 0;
	int icon_posx = 0, icon_posy = 0;

	if (this->left) {
		icon_centx = bar_width_i + (this->width() - bar_width_i) * icon_cx;
		icon_centy = this->height() * icon_cy;
	}
	else {
		icon_centx = (this->width() - bar_width_i) * icon_cx;
		icon_centy = this->height() * icon_cy;
	}

	{
		QSize pixResourceSize = StyleContainer::getContainer().getSourcePix("button-" + this->id + "-icon-normal-1").size();
		double icon_scale = qMin((double)((this->width() - bar_width_i) * icon_px) / (double)pixResourceSize.width(), (double)(this->height() * icon_py) / (double)pixResourceSize.height());
		StyleContainer::getContainer().scalePix("button-" + this->id + "-icon-normal-1", icon_scale);
	}
	{
		QSize pixResourceSize = StyleContainer::getContainer().getSourcePix("button-" + this->id + "-icon-hover-1").size();
		double icon_scale = qMin((double)((this->width() - bar_width_i) * icon_px) / (double)pixResourceSize.width(), (double)(this->height() * icon_py) / (double)pixResourceSize.height());
		StyleContainer::getContainer().scalePix("button-" + this->id + "-icon-hover-1", icon_scale);
	}
	{
		QSize pixResourceSize = StyleContainer::getContainer().getSourcePix("button-" + this->id + "-icon-pressed-1").size();
		double icon_scale = qMin((double)((this->width() - bar_width_i) * icon_px) / (double)pixResourceSize.width(), (double)(this->height() * icon_py) / (double)pixResourceSize.height());
		StyleContainer::getContainer().scalePix("button-" + this->id + "-icon-pressed-1", icon_scale);
	}
	{
		QSize pixResourceSize = StyleContainer::getContainer().getSourcePix("button-" + this->id + "-icon-normal-2").size();
		double icon_scale = qMin((double)((this->width() - bar_width_i) * icon_px) / (double)pixResourceSize.width(), (double)(this->height() * icon_py) / (double)pixResourceSize.height());
		StyleContainer::getContainer().scalePix("button-" + this->id + "-icon-normal-2", icon_scale);
	}
	{
		QSize pixResourceSize = StyleContainer::getContainer().getSourcePix("button-" + this->id + "-icon-hover-2").size();
		double icon_scale = qMin((double)((this->width() - bar_width_i) * icon_px) / (double)pixResourceSize.width(), (double)(this->height() * icon_py) / (double)pixResourceSize.height());
		StyleContainer::getContainer().scalePix("button-" + this->id + "-icon-hover-2", icon_scale);
	}
	{
		QSize pixResourceSize = StyleContainer::getContainer().getSourcePix("button-" + this->id + "-icon-pressed-2").size();
		double icon_scale = qMin((double)((this->width() - bar_width_i) * icon_px) / (double)pixResourceSize.width(), (double)(this->height() * icon_py) / (double)pixResourceSize.height());
		StyleContainer::getContainer().scalePix("button-" + this->id + "-icon-pressed-2", icon_scale);
	}
}

void PermanentToolButton::setId(QString id)
{
	this->id = id;
	StyleContainer::getContainer().loadPix("button-" + id + "-icon-normal-1", QString::fromStdString(StyleContainer::getContainer().getStyleObject()["tools"][this->id.toStdString()]("icon-normal-1")));
	StyleContainer::getContainer().loadPix("button-" + id + "-icon-hover-1", QString::fromStdString(StyleContainer::getContainer().getStyleObject()["tools"][this->id.toStdString()]("icon-hover-1")));
	StyleContainer::getContainer().loadPix("button-" + id + "-icon-pressed-1", QString::fromStdString(StyleContainer::getContainer().getStyleObject()["tools"][this->id.toStdString()]("icon-pressed-1")));
	StyleContainer::getContainer().loadPix("button-" + id + "-icon-normal-2", QString::fromStdString(StyleContainer::getContainer().getStyleObject()["tools"][this->id.toStdString()]("icon-normal-2")));
	StyleContainer::getContainer().loadPix("button-" + id + "-icon-hover-2", QString::fromStdString(StyleContainer::getContainer().getStyleObject()["tools"][this->id.toStdString()]("icon-hover-2")));
	StyleContainer::getContainer().loadPix("button-" + id + "-icon-pressed-2", QString::fromStdString(StyleContainer::getContainer().getStyleObject()["tools"][this->id.toStdString()]("icon-pressed-2")));
}

const QString PermanentToolButton::getId()
{
	return this->id;
}

void PermanentToolButton::setLeft(bool left)
{
	this->left = left;
	this->update();
}

void PermanentToolButton::mousePressEvent(QMouseEvent* event)
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

void PermanentToolButton::mouseMoveEvent(QMouseEvent* event)
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

void PermanentToolButton::mouseReleaseEvent(QMouseEvent* event)
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
				this->pressFlag = !this->pressFlag;
				emit this->actived(this->id, this->pressFlag);
			}
			else {
				this->pressFlag = !this->pressFlag;
				if (this->pressFlag) {
					this->state = ButtonState::Checked;
				}
				else {
					this->state = ButtonState::Normal;
				}
				emit this->actived(this->id, this->pressFlag);
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

void PermanentToolButton::leaveEvent(QEvent* event)
{
	this->setCursor(Qt::ArrowCursor);
	if (this->pressFlag) {
		this->state = ButtonState::Checked;
	}
	else {
		this->state = ButtonState::Normal;
	}
	this->update();
}

bool PermanentToolButton::inWidget(QPoint pos)
{
	return
		pos.x() >= 0 &&
		pos.x() <= this->width() &&
		pos.y() >= 0 &&
		pos.y() <= this->height();
}

void PermanentToolButton::setChecked(bool checked)
{
	if (checked) {
		this->state = ButtonState::Checked;
	}
	else {
		this->state = ButtonState::Normal;
	}
	if (this->pressFlag != checked) {
		this->pressFlag = checked;
		this->update();
		emit this->actived(this->id, checked);
	}
	else {
		this->update();
	}
}

void PermanentToolButton::activeSlot(QString id, bool checked)
{
	if (this->id == id) {
		if (checked) {
			this->state = ButtonState::Checked;
		}
		else {
			this->state = ButtonState::Normal;
		}
		if (this->pressFlag != checked) {
			this->pressFlag = checked;
			this->update();
			emit this->actived(this->id, checked);
		}
		else {
			this->update();
		}
	}
}