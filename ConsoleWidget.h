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
//#include "StringQueueThread.h"
#include <QMutex>
#include <QFontMetrics>
#include <QSet>

class ConsoleWidget : public RefreshableWidget
{
	Q_OBJECT

public:
	ConsoleWidget(QWidget *parent = Q_NULLPTR);
	~ConsoleWidget();

private:
	QString strInput;
	ConsoleScollBar* scoller = nullptr;
	//StringQueueThread* sThread = nullptr;

	enum class LineState {
		Input,
		Output,
		Error
	};

	QVector<QPair<QString, LineState>> lines;
	QVector<QPair<QString, LineState>> lineSplit;
	QMutex linesMutex;

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
	QTimer refreshTimer;

	const QString inputMask = ">> ";
	const QString outputMask = "<< ";

	bool haveChange = false;

	QSet<int> lineSet;

protected:
	void paintEvent(QPaintEvent* event)override;
	void keyPressEvent(QKeyEvent* event)override;
	void resizeAll()override;
	void wheelEvent(QWheelEvent* event)override;

	void showEvent(QShowEvent* event)override;
	void hideEvent(QHideEvent* event)override;
	void closeEvent(QCloseEvent* event)override;

public slots:
	void on_luaMessage(QString message);
	void on_luaError(QString message);
	void on_luaClear();

private slots:
	void on_ScollValueChanged(double sp, double ep);
	void on_timerTimeOut();
	void on_WheelChanged(int delta);
	void on_refreshTimeOut();

signals:
	void command(QString command);
};
