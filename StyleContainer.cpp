#include "StyleContainer.h"

StyleContainer::StyleContainer(QObject* parent)
	:QObject(parent)
{
}


StyleContainer::~StyleContainer()
{

}

StyleContainer StyleContainer::styles(nullptr);

void StyleContainer::startListen()
{
	mutex.lock();
	watcher.addPath(GetConfig::getConfigFilePath("skin"));
	watcher.addPath(GetStyle::getStyleFilePath(GetConfig::getStyleName()));
	watcher.addPath(GetTrans::getTransFilePath(GetConfig::getTransName()));
	connect(&(this->watcher), &QFileSystemWatcher::fileChanged, this, &StyleContainer::on_config_changed);

	GetConfig::refreshConfigs(this->styleObject);
	GetConfig::refreshTranslates(this->translateObject);
	mutex.unlock();
}

StyleContainer& StyleContainer::getContainer()
{
	return StyleContainer::styles;
}

void StyleContainer::on_config_changed(const QString& path)
{
	Q_UNUSED(path);
	mutex.lock();
	watcher.removePaths(watcher.files());
	watcher.addPath(GetConfig::getConfigFilePath("skin"));
	watcher.addPath(GetStyle::getStyleFilePath(GetConfig::getStyleName()));
	watcher.addPath(GetTrans::getTransFilePath(GetConfig::getTransName()));

	GetConfig::refreshConfigs(this->styleObject);
	GetConfig::refreshTranslates(this->translateObject);
	mutex.unlock();
	this->refreshPix();
	emit this->resource_refresh();
}

neb::CJsonObject& StyleContainer::getStyleObject()
{
	mutex.lock();
	mutex.unlock();
	return this->styleObject;
}

neb::CJsonObject& StyleContainer::getTransObject()
{
	mutex.lock();
	mutex.unlock();
	return this->translateObject;
}

void StyleContainer::refreshPix()
{
	auto styleSrcFun = [&](QString path)->QString
	{
		return QString(
			QCoreApplication::applicationDirPath() +
			QString("/themes/") +
			path
		);
	};

	for (int i = 0; i < this->sourceMap.size(); i++) {
		mutex.lock();
		this->sourceMap[this->sourceMap.keys().at(i)].load(this->paths.value(this->sourceMap.keys().at(i)));
		mutex.unlock();
	}

	for (int i = 0; i < this->sourceMap.size(); i++) {
		this->scalePix(this->sourceMap.keys().at(i), this->scales.value(this->sourceMap.keys().at(i)));
	}
}

void StyleContainer::loadPix(QString name, QString path)
{
	auto styleSrcFun = [&](QString path)->QString
	{
		return QString(
			QCoreApplication::applicationDirPath() +
			QString("/themes/") +
			path
		);
	};

	QPixmap pixtemp;

	mutex.lock();
	pixtemp.load(styleSrcFun(path));
	mutex.unlock();

	this->sourceMap.insert(name, pixtemp);
	if (!this->scales.contains(name)) {
		this->scales.insert(name, 1);
	}
	this->paths.insert(name, path);

	this->scalePix(name, this->scales.value(name));
}

void StyleContainer::scalePix(QString name, double s)
{
	if (s != this->scales.value(name) || !this->scaleMap.contains(name)) {
		QPixmap tempMap = this->sourceMap.value(name);
		this->scaleMap.insert(name, tempMap.scaled(tempMap.width() * s, tempMap.height() * s, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation));
	}
}

QPixmap& StyleContainer::getPix(QString name)
{
	return this->scaleMap[name];
}

QPixmap& StyleContainer::getSourcePix(QString name)
{
	return this->sourceMap[name];
}