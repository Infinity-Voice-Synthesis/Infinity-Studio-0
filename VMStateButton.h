#pragma once

#include "StatusButton.h"
#include <QTimer>

class VMStateButton : public StatusButton
{
	Q_OBJECT

public:
	VMStateButton(QWidget *parent = Q_NULLPTR);
	~VMStateButton();

	void setVMRunning(bool running);

protected:
	void mouseDoubleClickEvent(QMouseEvent* event)override;
	void mouseReleaseEvent(QMouseEvent* event)override;

private:
	QTimer clickTimer;

signals:
	void activeCritical();
};
