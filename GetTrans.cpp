#include "GetTrans.h"

GetTrans::GetTrans()
{

}

GetTrans::~GetTrans()
{

}

QString GetTrans::getTransFilePath(QString trans)
{
	return QString(QCoreApplication::applicationDirPath() + "/translates/" + Infinity_global::projectName + "/" + trans + ".json");
}

QString GetTrans::getTransFileData(QString filename)
{
	QFile file(filename);
	if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QString fileData = file.readAll();
		file.close();
		return fileData;
	}
	qDebug(QString("Can't open the translate file:" + filename).toStdString().c_str());
	return QString();
}

neb::CJsonObject GetTrans::parseJsonToObject(QString jsonData)
{
	neb::CJsonObject jo;
	jo.Parse(jsonData.toStdString());
	return jo;
}
