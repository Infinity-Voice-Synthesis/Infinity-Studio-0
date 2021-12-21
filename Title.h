#pragma once

#include <QWidget>
#include <QPainter>
#include "CloseButton.h"
#include "MaxiumButton.h"
#include "FloatButton.h"
#include "MiniumButton.h"
#include <QApplication>
#include <QScreen>
#include <QMouseEvent>
#include <QPoint>
#include <QMainWindow>
#include <QPixmap>
#include "Infinity_global.h"
#include <QMessageBox>
#include "MainMenuBar.h"
#include "StyleContainer.h"
#include "Infinity_Events.h"
#include "RefreshableWidget.h"

class Title : public RefreshableWidget
{
	Q_OBJECT

public:
	Title(QWidget* parent = Q_NULLPTR);
	~Title();

	void setWindowMaxium(bool windowMaxium);

private:
	CloseButton* closeB = nullptr;
	MaxiumButton* maxiumB = nullptr;
	FloatButton* floatB = nullptr;
	MiniumButton* miniumB = nullptr;
	MainMenuBar* menuBar = nullptr;

	bool mousePressed = false;
	QPoint mouseStartPoint;
	QPoint windowTopLeftPoint;

	void RAII_alloc();
	void RAII_free();

	QString titleHead = "Infinity Studio";

protected:
	void resizeAll()override;
	void paintEvent(QPaintEvent* event)override;
	void mousePressEvent(QMouseEvent* event)override;
	void mouseMoveEvent(QMouseEvent* event)override;
	void mouseReleaseEvent(QMouseEvent* event)override;
	void leaveEvent(QEvent* event)override;
	void mouseDoubleClickEvent(QMouseEvent* event)override;

private slots:
	void on_resourceRefresh();

signals:
	void closeB_clicked();
	void maxiumB_clicked();
	void floatB_clicked();
	void miniumB_clicked();

	void windowMove(QPoint pos);
};
