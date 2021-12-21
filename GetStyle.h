#pragma once

#include "CJsonObject/CJsonObject.hpp"
#include <QString>
#include <QColor>
#include <QFile>
#include <QCoreApplication>
#include "Infinity_global.h"

class GetStyle
{
public:
	GetStyle();
	~GetStyle();
	static QString getStyleFilePath(QString style);
	static QString getStyleFileData(QString filename);
	static neb::CJsonObject parseJsonToObject(QString jsonData);
	static QColor parseStringToColor(QString colorString);
private:

};
