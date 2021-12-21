#pragma once

#include <QObject>
#include <QString>

class Infinity_Events : public QObject
{
	Q_OBJECT
	Infinity_Events(QObject* parent);
	~Infinity_Events();
	static Infinity_Events IE_Class;

	bool ConsoleFastReady = false;
	bool CentralFastReady = true;

public:
	static Infinity_Events& getClass();

public slots:
	void on_button_actived(QString id, bool checked);
	void on_button_selected(QString id);
	void on_resource_refresh();
	void on_console_clicked();

	void on_console_ready(bool fast);
	void on_central_ready(bool fast);

	void on_console_command(QString command);

	void on_luaErrorMessage(QString message);
	void on_luaNormalMessage(QString message);
	void on_luaMainStarted();
	void on_luaMainEnded();

signals:
	void button_active(QString id, bool checked);
	void view_show(QString id, bool checked);
	void resource_refresh();
	void console_click();

	void background_fast(bool fast);

	void lua_command(QString command);

	void console_error(QString message);
	void console_normal(QString message);
	void console_mainStart();
	void console_mainEnd();
};
