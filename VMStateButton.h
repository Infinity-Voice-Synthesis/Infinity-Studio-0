#pragma once

#include "StatusButton.h"

class VMStateButton : public StatusButton
{
	Q_OBJECT

public:
	VMStateButton(QWidget *parent = Q_NULLPTR);
	~VMStateButton();

	void setVMRunning(bool running);

protected:
	void mouseDoubleClickEvent(QMouseEvent* event)override;

signals:
	void activeCritical();
};
