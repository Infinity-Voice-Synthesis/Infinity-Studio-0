#pragma once

#include "TitleButton.h"
#include <QPainter>
#include "StyleContainer.h"

class CloseButton : public TitleButton
{
	Q_OBJECT

public:
	CloseButton(QWidget* parent = Q_NULLPTR);
	~CloseButton();

private:
protected:
	void paintEvent(QPaintEvent* event)override;
};
