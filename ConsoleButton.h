#pragma once

#include "ClickButton.h"
#include <QPainter>
#include "StyleContainer.h"

class ConsoleButton : public ClickButton
{
	Q_OBJECT

public:
	ConsoleButton(QWidget *parent = Q_NULLPTR);
	~ConsoleButton();

protected:
	void paintEvent(QPaintEvent* event)override;

private:
};
