#pragma once

#include <QWidget>
#include <QMouseEvent>
#include "ClickButton.h"

class TitleButton : public ClickButton
{
	Q_OBJECT

public:
	TitleButton(QWidget* parent = Q_NULLPTR);
	~TitleButton();
};
