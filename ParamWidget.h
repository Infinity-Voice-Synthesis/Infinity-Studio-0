#pragma once

#include <QWidget>
#include "Infinity_global.h"
#include "Infinity_Events.h"
#include "StyleContainer.h"
#include <QPainter>
#include "RefreshableWidget.h"

class ParamWidget : public RefreshableWidget
{
	Q_OBJECT

public:
	ParamWidget(QWidget *parent = Q_NULLPTR);
	~ParamWidget();
	void setStateTop(bool isTop);
	void setStateBottom(bool isBottom);

private:
	bool isTop = false;
	bool isBottom = false;

protected:
	void paintEvent(QPaintEvent* event)override;
};
