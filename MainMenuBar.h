#pragma once

#include <QWidget>
#include <QPainter>
#include <QStringList>
#include <QApplication>
#include <QScreen>
#include <QMainWindow>
#include "Infinity_global.h"
#include <QVector>
#include "MainMenuButton.h"
#include <QMessageBox>
#include "StyleContainer.h"
#include "RefreshableWidget.h"

class MainMenuBar : public RefreshableWidget
{
	Q_OBJECT

public:
	MainMenuBar(QWidget* parent);
	~MainMenuBar();

private:
	QStringList buttonList = {
		"MMB_File",
		"MMB_Edit",
		"MMB_View",
		"MMB_Modify",
		"MMB_Project",
		"MMB_Transport",
		"MMB_Automatic",
		"MMB_Config",
		"MMB_Misc"
	};
	QString strMore = ". . .";
	QVector<QRect> buttonRects;
	bool moreButtonOn = false;

	QVector<MainMenuButton*> buttons;

protected:
	void paintEvent(QPaintEvent* event)override;
	void resizeAll()override;

private slots:
	void on_active(bool ok);
};
