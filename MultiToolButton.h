#pragma once

#include "ToolButton.h"

class MultiToolButton : public ToolButton
{
	Q_OBJECT

public:
	MultiToolButton(QWidget *parent = Q_NULLPTR);
	~MultiToolButton();

protected:
	void mousePressEvent(QMouseEvent* event)override;
	void mouseMoveEvent(QMouseEvent* event)override;
	void mouseReleaseEvent(QMouseEvent* event)override;

signals:
	void selected(QString id);
};
