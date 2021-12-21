#pragma once

#include "CJsonObject/CJsonObject.hpp"
#include <QString>
#include <QFile>
#include <QCoreApplication>
#include "GetStyle.h"
#include "GetTrans.h"
#include "Infinity_global.h"

class GetConfig
{
public:
	GetConfig();
	~GetConfig();
	static QString getStyleName();
	static QString getTransName();
	static void refreshConfigs(neb::CJsonObject& object);
	static void refreshTranslates(neb::CJsonObject& object);
	static QString getConfigFilePath(QString group);
	static QString getConfigFileData(QString filename);
private:
};
