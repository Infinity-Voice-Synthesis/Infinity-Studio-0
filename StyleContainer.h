#pragma once

#include <QObject>
#include <QFile>
#include <QFileSystemWatcher>
#include "CJsonObject/CJsonObject.hpp"
#include "GetStyle.h"
#include "GetConfig.h"
#include <QCoreApplication>
#include <QApplication>
#include <QMutex>
#include <QMap>
#include <QPixmap>

class StyleContainer:public QObject
{
	Q_OBJECT
private:
	StyleContainer(QObject* parent = nullptr);
	~StyleContainer();

	static StyleContainer styles;
	neb::CJsonObject styleObject;
	neb::CJsonObject translateObject;

	QFileSystemWatcher watcher;
	QMutex mutex;

	QMap<QString, QPixmap> sourceMap;
	QMap<QString, QPixmap> scaleMap;
	QMap<QString, double> scales;
	QMap<QString, QString> paths;

public:
	static StyleContainer& getContainer();
	neb::CJsonObject& getStyleObject();
	neb::CJsonObject& getTransObject();
	void startListen();

	void refreshPix();
	void loadPix(QString name, QString path);
	void scalePix(QString name, double s);
	QPixmap& getPix(QString name);
	QPixmap& getSourcePix(QString name);

private slots:
	void on_config_changed(const QString& path);

signals:
	void resource_refresh();
};

