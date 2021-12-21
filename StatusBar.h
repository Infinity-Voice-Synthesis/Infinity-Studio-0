#pragma once

#include <QWidget>
#include <QPainter>
#include "Infinity_global.h"
#include "Infinity_Events.h"
#include "StyleContainer.h"
#include "ConsoleButton.h"
#include <QMessageBox>
#include "RefreshableWidget.h"

class StatusBar : public RefreshableWidget
{
	Q_OBJECT

public:
	StatusBar(QWidget *parent = Q_NULLPTR);
	~StatusBar();

private:
	ConsoleButton* consoleb = nullptr;

protected:
	void paintEvent(QPaintEvent* event)override;
	void resizeAll()override;
};
