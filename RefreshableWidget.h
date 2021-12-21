#pragma once

#include <QWidget>
#include "Infinity_Events.h"

class RefreshableWidget : public QWidget
{
	Q_OBJECT

public:
	RefreshableWidget(QWidget *parent = Q_NULLPTR);
	~RefreshableWidget();

private:
protected:
	virtual void resizeAll();
	void resizeEvent(QResizeEvent* event)override;

private slots:
	virtual void on_resourceRefresh();
};
