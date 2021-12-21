#pragma once

#include <QWidget>
#include "Infinity_global.h"
#include "Infinity_Events.h"
#include "StyleContainer.h"
#include <QPainter>
#include "RefreshableWidget.h"

class NoteWidget : public RefreshableWidget
{
	Q_OBJECT

public:
	NoteWidget(QWidget *parent = Q_NULLPTR);
	~NoteWidget();
	void setStateTop(bool isTop);
	void setStateBottom(bool isBottom);

private:
	bool isTop = false;
	bool isBottom = true;

protected:
	void paintEvent(QPaintEvent* event)override;
};
