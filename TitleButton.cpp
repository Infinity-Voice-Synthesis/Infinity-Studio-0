#include "TitleButton.h"

TitleButton::TitleButton(QWidget* parent)
	: ClickButton(parent)
{
	this->setMouseTracking(true);
}

TitleButton::~TitleButton()
{
}
