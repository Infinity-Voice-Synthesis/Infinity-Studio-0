#pragma once

#include "RefreshableWidget.h"
#include <QPainter>
#include "StyleContainer.h"
#include <QKeyEvent>
#include "ConsoleScollBar.h"
#include <QMessageBox>
#include <QVector>
#include <QTimer>
#include <QMouseEvent>
#include <QWheelEvent>

class ConsoleWidget : public RefreshableWidget
{
	Q_OBJECT

public:
	ConsoleWidget(QWidget *parent = Q_NULLPTR);
	~ConsoleWidget();

private:
	QString strInput;
	ConsoleScollBar* scoller = nullptr;

	enum class LineState {
		Input,
		Output,
		Error
	};

	QVector<QPair<QString, LineState>> lines;
	QVector<QPair<QString, LineState>> lineSplit;

	QStringList commandTemp;
	QString eLineTemp;
	int currentTemp = -1;

	void doString(QString command);

	void reSplit();
	void goDown();

	int currentTopLine = 0;

	int cursorPlace = 0;
	bool showCursor = true;

	QTimer curTimer;
	const int curWait = 600;

	const QString inputMask = ">> ";

protected:
	void paintEvent(QPaintEvent* event)override;
	void keyPressEvent(QKeyEvent* event)override;
	void resizeAll()override;
	void wheelEvent(QWheelEvent* event)override;

public slots:
	void on_luaMessage(QString message);
	void on_luaError(QString message);
	void on_luaClear();

private slots:
	void on_ScollValueChanged(double sp, double ep);
	void on_timerTimeOut();
	void on_WheelChanged(int delta);

signals:
	void command(QString command);
};
