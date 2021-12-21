#pragma once

#include "TitleButton.h"
#include <QPainter>
#include "StyleContainer.h"

class MaxiumButton : public TitleButton
{
	Q_OBJECT

public:
	MaxiumButton(QWidget* parent = Q_NULLPTR);
	~MaxiumButton();

private:
protected:
	void paintEvent(QPaintEvent* event)override;
};
