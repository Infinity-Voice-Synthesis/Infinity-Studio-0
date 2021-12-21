#include "MainMenuButton.h"

MainMenuButton::MainMenuButton(QWidget* parent)
	: RefreshableWidget(parent)
{
	this->setMouseTracking(true);
}

MainMenuButton::~MainMenuButton()
{
}

void MainMenuButton::setText(QString text)
{
	this->text = text;
	this->update();
}

void MainMenuButton::setId(QString id)
{
	this->id = id;
}

void MainMenuButton::setFontPixelSize(double size)
{
	this->font_pixel_size = size;
	this->update();
}

QString MainMenuButton::getId() const
{
	return this->id;
}

MainMenuButton::MenuButtonState MainMenuButton::getState() const
{
	return this->state;
}

void MainMenuButton::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);

	QColor color_normal = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["main-menu-bar"]("color-normal")));
	QColor color_hover = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["main-menu-bar"]("color-hover")));
	QColor color_checked = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["main-menu-bar"]("color-checked")));
	QColor color_background_normal = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["main-menu-bar"]("color-background-normal")));
	QColor color_background_hover = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["main-menu-bar"]("color-background-hover")));
	QColor color_background_checked = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["main-menu-bar"]("color-background-checked")));

	QPainter painter(this);

	QPen pen;
	pen.setWidth(1);
	pen.setStyle(Qt::SolidLine);
	pen.setJoinStyle(Qt::RoundJoin);
	pen.setCapStyle(Qt::RoundCap);

	QBrush brush;
	brush.setStyle(Qt::SolidPattern);

	switch (this->state)
	{
	case MenuButtonState::Normal:
		pen.setColor(color_normal);
		brush.setColor(color_background_normal);
		painter.fillRect(0, 0, this->width(), this->height(), color_background_normal);
		break;
	case MenuButtonState::Hover:
		pen.setColor(color_hover);
		brush.setColor(color_background_hover);
		painter.fillRect(0, 0, this->width(), this->height(), color_background_hover);
		break;
	case MenuButtonState::Checked:
		pen.setColor(color_checked);
		brush.setColor(color_background_checked);
		painter.fillRect(0, 0, this->width(), this->height(), color_background_checked);
		break;
	case MenuButtonState::OtherChecked:
		pen.setColor(color_normal);
		brush.setColor(color_background_normal);
		painter.fillRect(0, 0, this->width(), this->height(), color_background_normal);
		break;
	default:
		pen.setColor(Qt::white);
		brush.setColor(Qt::black);
		painter.fillRect(0, 0, this->width(), this->height(), Qt::black);
		break;
	}

	painter.setPen(pen);
	painter.setBrush(brush);

	int font_pixel_size_i = this->font_pixel_size * Infinity_global::getScreenSize().width();

	QFont font;
	font.setPixelSize(font_pixel_size_i);
	painter.setFont(font);

	int font_width = painter.fontMetrics().horizontalAdvance(this->text);
	QPoint textPoint((this->width() / 2) - (font_width / 2), (this->height() / 2) + (painter.fontMetrics().boundingRect('I').height() / 2));
	painter.drawText(textPoint, this->text);
}

void MainMenuButton::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton) {
		switch (this->state)
		{
		case MenuButtonState::Normal:
		{
			if (this->inWidget(event->pos())) {
				this->state = MenuButtonState::Checked;
				this->update();
				this->activeFlag = true;
				emit this->active(true);
			}
			break;
		}
		case MenuButtonState::Hover:
		{
			if (this->inWidget(event->pos())) {
				this->state = MenuButtonState::Checked;
				this->update();
				this->activeFlag = true;
				emit this->active(true);
			}
			break;
		}
		case MenuButtonState::Checked:
		{
			if (this->inWidget(event->pos())) {
				this->activeFlag = false;
			}
			break;
		}
		default:
		{
			break;
		}
		}
	}
}

void MainMenuButton::mouseMoveEvent(QMouseEvent* event)
{
	switch (this->state)
	{
	case MenuButtonState::OtherChecked:
	{
		if (this->inWidget(event->pos())) {
			this->state = MenuButtonState::Checked;
			this->update();
			emit this->active(true);
		}
		break;
	}
	case MenuButtonState::Checked:
	{
		break;
	}
	default:
	{
		if (this->inWidget(event->pos())) {
			this->state = MenuButtonState::Hover;
			this->update();
		}
		else {
			this->state = MenuButtonState::Normal;
			this->update();
		}
		break;
	}
	}
}

void MainMenuButton::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton) {
		switch (this->state)
		{
		case MenuButtonState::Checked:
		{
			if (!this->activeFlag) {
				this->state = MenuButtonState::Hover;
				this->update();
				emit this->active(false);
			}
			break;
		}
		default:
		{
			break;
		}
		}
	}
}

void MainMenuButton::leaveEvent(QEvent* event)
{
	Q_UNUSED(event);
	switch (this->state)
	{
	case MenuButtonState::Hover:
	{
		this->state = MenuButtonState::Normal;
		this->update();
	}
	default:
		break;
	}
}

bool MainMenuButton::inWidget(QPoint pos)
{
	return pos.x() >= 0 &&
		pos.x() <= this->width() &&
		pos.y() >= 0 &&
		pos.y() <= this->height();
}

void MainMenuButton::resetButton()
{
	if (this->state == MenuButtonState::Checked) {
		this->state = MenuButtonState::Normal;
		this->update();
		this->activeFlag = false;
		emit this->active(false);
	}
	else if (this->state == MenuButtonState::OtherChecked)
	{
		this->state = MenuButtonState::Normal;
		this->update();
	}
}

void MainMenuButton::setButtonWait()
{
	this->state = MenuButtonState::OtherChecked;
	this->update();
	this->activeFlag = false;
}
