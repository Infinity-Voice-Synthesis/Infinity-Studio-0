#pragma once

#include "TitleButton.h"
#include <QPainter>
#include "StyleContainer.h"

class MiniumButton : public TitleButton
{
	Q_OBJECT

public:
	MiniumButton(QWidget* parent = Q_NULLPTR);
	~MiniumButton();

private:
protected:
	void paintEvent(QPaintEvent* event)override;
};
