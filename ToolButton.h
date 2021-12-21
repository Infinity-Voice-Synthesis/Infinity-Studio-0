#pragma once

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include "StyleContainer.h"
#include "Infinity_Events.h"
#include <QMouseEvent>
#include "RefreshableWidget.h"

class ToolButton : public RefreshableWidget
{
	Q_OBJECT

public:
	ToolButton(QWidget* parent = Q_NULLPTR);
	~ToolButton();

	const QString getId();

	enum class ButtonState {
		Normal = 0,
		Hover = 1,
		Pressed = 2,
		Checked = 3
	};

private:
	bool left = true;

protected:
	void paintEvent(QPaintEvent* event)override;
	void mousePressEvent(QMouseEvent* event)override;
	void mouseMoveEvent(QMouseEvent* event)override;
	void mouseReleaseEvent(QMouseEvent* event)override;
	void leaveEvent(QEvent* event)override;
	void resizeAll()override;

	QString id;
	ButtonState state = ButtonState::Normal;
	bool pressFlag = false;
	bool inWidget(QPoint pos);

signals:
	void actived(QString id, bool checked);

private slots:
	void on_resourceRefresh();

public slots:
	void setId(QString id);
	void setLeft(bool left);
	void setChecked(bool checked);
	void activeSlot(QString id, bool checked);
};
