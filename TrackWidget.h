#pragma once

#include <QWidget>
#include "Infinity_global.h"
#include "Infinity_Events.h"
#include "StyleContainer.h"
#include <QPainter>
#include "RefreshableWidget.h"

class TrackWidget : public RefreshableWidget
{
	Q_OBJECT

public:
	TrackWidget(QWidget *parent = Q_NULLPTR);
	~TrackWidget();
	void setStateTop(bool isTop);
	void setStateBottom(bool isBottom);

private:
	bool isTop = true;
	bool isBottom = false;

protected:
	void paintEvent(QPaintEvent* event)override;
};
