#include "GetStyle.h"

GetStyle::GetStyle()
{
}

GetStyle::~GetStyle()
{
}

QString GetStyle::getStyleFilePath(QString style)
{
	return QString(QCoreApplication::applicationDirPath() + "/themes/" + Infinity_global::projectName + "/" + style + ".json");
}

QString GetStyle::getStyleFileData(QString filename)
{
	QFile file(filename);
	if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QString fileData = file.readAll();
		file.close();
		return fileData;
	}
	qDebug(QString("Can't open the style file:" + filename).toStdString().c_str());
	return QString();
}

neb::CJsonObject GetStyle::parseJsonToObject(QString jsonData)
{
	neb::CJsonObject jo;
	jo.Parse(jsonData.toStdString());
	return jo;
}

QColor GetStyle::parseStringToColor(QString colorString)
{
	QColor color;
	color.setRgb(colorString.toUInt(nullptr, 16));
	return color;
}
