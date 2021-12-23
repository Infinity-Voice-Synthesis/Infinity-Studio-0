#pragma once

#include <QWidget>
#include <QPainter>
#include "Infinity_global.h"
#include "Infinity_Events.h"
#include "StyleContainer.h"
#include "ConsoleButton.h"
#include <QMessageBox>
#include "RefreshableWidget.h"
#include "VMStateButton.h"

class StatusBar : public RefreshableWidget
{
	Q_OBJECT

public:
	StatusBar(QWidget *parent = Q_NULLPTR);
	~StatusBar();

	bool VMIsFree();

private:
	ConsoleButton* consoleb = nullptr;
	VMStateButton* vmb = nullptr;

	bool vmFree = true;

protected:
	void paintEvent(QPaintEvent* event)override;
	void resizeAll()override;

private slots:
	void on_VMMTStart();
	void on_VMMTEnd();

signals:
	void VMBClicked();
	void VMBActiveCritical();

};
