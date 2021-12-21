#include "InfinityStudio0.h"
#include <QtWidgets/QApplication>
#include "GetConfig.h"
#include "CJsonObject/CJsonObject.hpp"
#include <QFontDatabase>
#include "Infinity_global.h"
#include "StyleContainer.h"
#include "ILVM.h"

void app_init()
{
	StyleContainer::getContainer().startListen();

	QString fontFile = QString::fromStdString(StyleContainer::getContainer().getStyleObject()("font"));
	int fontClass = 0;
	StyleContainer::getContainer().getStyleObject().Get("font-class", fontClass);

	int fontId = QFontDatabase::addApplicationFont(QCoreApplication::applicationDirPath() + QString("/themes/") + Infinity_global::projectName + "/" + fontFile);
	QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(fontClass);
	QFont font(fontName);
	QApplication::setFont(font);
}

int main(int argc, char* argv[])
{
	QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);
	QApplication a(argc, argv);

	::app_init();

	InfinityStudio0 w;

	Infinity_global::getGlobal().set_App_init_OK(true);

	if (Infinity_global::getGlobal().get_RAII_memory_OK()) {
		QObject::connect(&(StyleContainer::getContainer()), &StyleContainer::resource_refresh, &(Infinity_Events::getClass()), &Infinity_Events::on_resource_refresh);

		QObject::connect(&(Infinity_Events::getClass()), &Infinity_Events::lua_command, &(ILVM::getVM()), &ILVM::on_commandsIn, Qt::ConnectionType::QueuedConnection);
		QObject::connect(&(ILVM::getVM()), &ILVM::errorMessage, &(Infinity_Events::getClass()), &Infinity_Events::on_luaErrorMessage, Qt::ConnectionType::QueuedConnection);
		QObject::connect(&(ILVM::getVM()), &ILVM::normalMessage, &(Infinity_Events::getClass()), &Infinity_Events::on_luaNormalMessage, Qt::ConnectionType::QueuedConnection);
		QObject::connect(&(ILVM::getVM()), &ILVM::mainStart, &(Infinity_Events::getClass()), &Infinity_Events::on_luaMainStarted, Qt::ConnectionType::QueuedConnection);
		QObject::connect(&(ILVM::getVM()), &ILVM::mainStop, &(Infinity_Events::getClass()), &Infinity_Events::on_luaMainEnded, Qt::ConnectionType::QueuedConnection);

		w.show();
		return a.exec();
	}
	else {
		return -1;
	}
}
