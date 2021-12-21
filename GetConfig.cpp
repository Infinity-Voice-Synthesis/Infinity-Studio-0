#include "GetConfig.h"

GetConfig::GetConfig()
{
}

GetConfig::~GetConfig()
{
}

QString GetConfig::getConfigFilePath(QString group)
{
	return QString(QCoreApplication::applicationDirPath() + "/configs/" + Infinity_global::projectName + "/" + group + ".json");
}

QString GetConfig::getConfigFileData(QString filename)
{
	QFile file(filename);
	if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QString fileData = file.readAll();
		file.close();
		return fileData;
	}
	qDebug(QString("Can't open the config file:" + filename).toStdString().c_str());
	return QString();
}

QString GetConfig::getStyleName()
{
	QString data = getConfigFileData(getConfigFilePath("skin"));
	neb::CJsonObject jo;
	jo.Parse(data.toStdString());
	return QString::fromStdString(jo("style"));
}

QString GetConfig::getTransName()
{
	QString data = getConfigFileData(getConfigFilePath("skin"));
	neb::CJsonObject jo;
	jo.Parse(data.toStdString());
	return QString::fromStdString(jo("language"));
}

void GetConfig::refreshConfigs(neb::CJsonObject& object)
{
	QString styleName = GetConfig::getStyleName();

	QString styleData = GetStyle::getStyleFileData(GetStyle::getStyleFilePath(styleName));
	object = GetStyle::parseJsonToObject(styleData);
}

void GetConfig::refreshTranslates(neb::CJsonObject& object)
{
	QString transName = GetConfig::getTransName();

	QString transData = GetTrans::getTransFileData(GetTrans::getTransFilePath(transName));
	object = GetTrans::parseJsonToObject(transData);
}
