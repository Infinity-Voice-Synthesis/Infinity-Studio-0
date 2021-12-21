#pragma once

#include "CJsonObject/CJsonObject.hpp"
#include <QFile>
#include <QCoreApplication>
#include "Infinity_global.h"

class GetTrans
{
public:
	GetTrans();
	~GetTrans();

	static QString getTransFilePath(QString trans);
	static QString getTransFileData(QString filename);
	static neb::CJsonObject parseJsonToObject(QString jsonData);
};
