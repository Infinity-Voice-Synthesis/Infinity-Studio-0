#pragma once

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include "StyleContainer.h"
#include <QMouseEvent>
#include "Infinity_Events.h"
#include "RefreshableWidget.h"

class PermanentToolButton : public RefreshableWidget
{
	Q_OBJECT

public:
	PermanentToolButton(QWidget* parent = Q_NULLPTR);
	~PermanentToolButton();
	
	const QString getId();

	enum class ButtonState {
		Normal = 0,
		Hover = 1,
		Pressed = 2,
		Checked = 3
	};

private:

	QString id;
	ButtonState state = ButtonState::Normal;
	bool left = true;
	bool pressFlag = false;

	bool inWidget(QPoint pos);

protected:
	void paintEvent(QPaintEvent* event)override;
	void mousePressEvent(QMouseEvent* event)override;
	void mouseMoveEvent(QMouseEvent* event)override;
	void mouseReleaseEvent(QMouseEvent* event)override;
	void leaveEvent(QEvent* event)override;
	void resizeAll()override;

signals:
	void actived(QString id, bool checked);

public slots:
	void setId(QString id);
	void setLeft(bool left);
	void setChecked(bool checked);
	void activeSlot(QString id, bool checked);

private slots:
	void on_resourceRefresh();
};
