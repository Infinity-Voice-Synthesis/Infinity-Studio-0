#pragma once

#include <QMainWindow>
#include <QApplication>
#include <QScreen>

class Infinity_global
{
public:
	bool get_RAII_memory_OK();
	void set_RAII_memory_OK(bool RAII_memory_OK);

	bool get_App_init_OK();
	void set_App_init_OK(bool App_init_OK);

	static QMainWindow* getMainWindow();
	static QSize getScreenSize();

	static Infinity_global& getGlobal();

	static QString projectName;

private:
	Infinity_global();

	bool RAII_memory_OK = true;
	bool App_init_OK = false;

	static Infinity_global i_global;
};
