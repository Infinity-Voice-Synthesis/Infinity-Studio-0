#include "Infinity_global.h"

Infinity_global::Infinity_global()
{

}

Infinity_global Infinity_global::i_global;
QString Infinity_global::projectName = "org.infinity.infinitystudio";

Infinity_global& Infinity_global::getGlobal()
{
	return Infinity_global::i_global;
}

bool Infinity_global::get_RAII_memory_OK()
{
	return this->RAII_memory_OK;
}

void Infinity_global::set_RAII_memory_OK(bool RAII_memory_OK)
{
	this->RAII_memory_OK = RAII_memory_OK;
}

bool Infinity_global::get_App_init_OK()
{
	return this->App_init_OK;
}

void Infinity_global::set_App_init_OK(bool App_init_OK)
{
	this->App_init_OK = App_init_OK;
}

QMainWindow* Infinity_global::getMainWindow()
{
	foreach(QWidget * w, qApp->topLevelWidgets())
	{
		if (QMainWindow* mainWin = qobject_cast<QMainWindow*>(w))
			return mainWin;
	}
	return nullptr;
}

QSize Infinity_global::getScreenSize()
{
	if (Infinity_global::getMainWindow() == nullptr) {
		return QApplication::screens().at(0)->availableSize();
	}
	if (QApplication::screenAt((Infinity_global::getMainWindow()->frameGeometry().topLeft() + Infinity_global::getMainWindow()->frameGeometry().topRight()) / 2) == nullptr) {
		return QApplication::screens().at(0)->availableSize();
	}
	return QApplication::screenAt((Infinity_global::getMainWindow()->frameGeometry().topLeft() + Infinity_global::getMainWindow()->frameGeometry().bottomRight()) / 2)->availableSize();
}
