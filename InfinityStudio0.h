#pragma once

#include <QtWidgets/QMainWindow>
#include <QPainter>
#include <QPixmap>
#include <QCoreApplication>
#include "Title.h"
#include <QApplication>
#include <QPoint>
#include <QIcon>
#include <QMessageBox>
#include "Infinity_global.h"
#include <QMouseEvent>
#include <QThread>
#include "ToolBar.h"
#include "StyleContainer.h"
#include "StatusBar.h"
#include "CentralWidget.h"
#include "ConsoleWidget.h"
#include "ILVM.h"

class InfinityStudio0 : public QMainWindow
{
	Q_OBJECT

public:
	InfinityStudio0(QWidget* parent = Q_NULLPTR);
	~InfinityStudio0();

private:
	Title* title = nullptr;
	ToolBar* tools = nullptr;
	StatusBar* status = nullptr;
	CentralWidget* central = nullptr;
	ConsoleWidget* console = nullptr;
	void RAII_alloc();
	void RAII_free();

	void resizeAll();

	bool consoleOn = false;

	bool fastMode = true;

protected:
	void paintEvent(QPaintEvent* event)override;
	void resizeEvent(QResizeEvent* event)override;

private slots:
	void on_titleClose();
	void on_titleMaximum();
	void on_titleFloat();
	void on_titleMinimum();

	void on_windowMove(QPoint pos);
	void on_resourceRefresh();
	void on_consoleChanged();

	void on_fastModeChanged(bool fast);

	void on_VMSBClicked();
	void on_VMSBActivedCritial();

signals:
	void consoleFastReady(bool fast);
};
