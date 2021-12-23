#pragma once

#include "ClickButton.h"
#include <QPainter>
#include "StyleContainer.h"

class StatusButton : public ClickButton
{
	Q_OBJECT

public:
	StatusButton(QWidget *parent = Q_NULLPTR);
	~StatusButton();

protected:
	void paintEvent(QPaintEvent* event)override;
	QString str;

};
