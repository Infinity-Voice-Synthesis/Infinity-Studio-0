#pragma once

#include <QObject>
#include <QList>
#include "LThread.h"
#include "Infinity_global.h"
#include "Infinity_Events.h"
#include <QMessageBox>
#include "ILLibs.h"

class ILVM : public QObject
{
	Q_OBJECT
	
	ILVM(QObject *parent);
	~ILVM();

	static ILVM vm;

	QList<LThread*> threads;
	QList<LThread*> threads_bin;
	LThread* mainThread = nullptr;

	const QString mainId = "_main";
	static quint64 t_count;

	static QString outStrTemp;

	bool isSafeMode = false;

	void VMPushOptionalFunctions(LThread* thread);
	void VMPushAllFunctions(LThread* thread);

public:
	static ILVM& getVM();

	static void lStdOut(const char* data, size_t size);
	static void lStdOutLine();
	static void lStdOutErr(const char* format, const char* data);

	void mainCritical();

	bool findThread(QString id);
	QStringList getThreadList();
	bool createThread(QString id);
	bool destoryThread(QString id);

	bool doStringOnThread(QString id, QString str);
	bool doFileOnThread(QString id, QString file);

	bool threadIsRunning(QString id);

public slots:
	void on_commandsIn(QString command);

private slots:
	void on_threadStart(QString id);
	void on_threadStop(QString id);

signals:
	void errorMessage(QString message);
	void normalMessage(QString message);
	void clearMessage();

	void mainStart();
	void mainStop();
};
