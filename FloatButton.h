#pragma once

#include "TitleButton.h"
#include <QPainter>
#include "StyleContainer.h"

class FloatButton : public TitleButton
{
	Q_OBJECT

public:
	FloatButton(QWidget* parent = Q_NULLPTR);
	~FloatButton();

private:
protected:
	void paintEvent(QPaintEvent* event)override;
};
