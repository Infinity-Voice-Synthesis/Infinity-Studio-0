#pragma once

#include <QObject>
#include <QList>
#include "LThread.h"
#include "Infinity_global.h"
#include "Infinity_Events.h"
#include <QMessageBox>

class ILVM : public QObject
{
	Q_OBJECT
	
	ILVM(QObject *parent);
	~ILVM();

	static ILVM vm;

	QList<LThread*> threads;
	LThread* mainThread = nullptr;

	const QString mainId = "_main";

	static QString outStrTemp;

public:
	static ILVM& getVM();

	static void lStdOut(const char* data, size_t size);
	static void lStdOutLine();
	static void lStdOutErr(const char* format, const char* data);

public slots:
	void on_commandsIn(QString command);

private slots:
	void on_threadStart(QString id);
	void on_threadStop(QString id);

signals:
	void errorMessage(QString message);
	void normalMessage(QString message);

	void mainStart();
	void mainStop();
};
