#pragma once

#include <QThread>
#include <QCoreApplication>
#include <QQueue>
#include <QMutex>
#include "Infinity_global.h"

#include "Lua/lua.hpp"

#include "ILLibs.h"

class LThread : public QThread
{
	Q_OBJECT

public:
	LThread(QObject *parent);
	~LThread();

	bool doFile(QString name);
	bool doString(QString str);

	bool setId(QString id);
	QString getId();

	bool destoryId(QString id);

	void beginGlobalTable();
	void endGlobalTable(QString name);

	void beginTable(QString name);
	void endTable();

	void addFunction(QString name, lua_CFunction function);

private:
	lua_State* lstate = nullptr;

	QString lFileName;
	QString Id;
	QMutex idMutex;

	enum class LType {
		DoFile,
		DoString
	};

	LType tType = LType::DoFile;

	QQueue<QString> strList;

protected:
	void run()override;

signals:
	void errorMessage(QString message);
	void normalMessage(QString message);

	void tStarted(QString id);
	void tEnded(QString id);
};
