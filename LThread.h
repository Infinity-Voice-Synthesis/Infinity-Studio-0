#pragma once

#include <QThread>
#include <QCoreApplication>
#include <QQueue>
#include "Infinity_global.h"

#include "Lua/lua.hpp"

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

private:
	lua_State* lstate = nullptr;

	QString lFileName;
	QString Id;

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
