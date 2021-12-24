#pragma once

#include <QString>
#include <QStringList>
#include <QSet>
#include "Lua/lua.hpp"
#include <QCoreApplication>
#include <QMutex>

class ILLibs
{
	static QString destoryId;

	static std::function<void(QString&)> console_mesFunction;
	static std::function<void(QString&)> console_assFunction;
	static std::function<void()> console_clsFunction;

	static std::function<bool(QString&)> thread_finFunction;
	static std::function<QStringList()> thread_lstFunction;
	static std::function<bool(QString&)> thread_creFunction;
	static std::function<bool(QString&)> thread_rmvFunction;
	static std::function<bool(QString&)> thread_chkFunction;
	static std::function<bool(QString&)> thread_desFunction;
	static std::function<bool(QString&, QString&)> thread_runFunction;
	static std::function<bool(QString&, QString&)> thread_execFunction;
	static std::function<void()> thread_fluFunction;

public:
	static void set_destory(QString destoryId);
	static bool isDestoried(lua_State* state);

	static void reg_mesFunctions(
		std::function<void(QString&)> console_mesFunction,
		std::function<void(QString&)> console_assFunction,
		std::function<void()> cconsole_lsFunction
	);
	static void reg_thrFunctions(
		std::function<bool(QString&)> thread_finFunction,
		std::function<QStringList()> thread_lstFunction,
		std::function<bool(QString&)> thread_creFunction,
		std::function<bool(QString&)> thread_rmvFunction,
		std::function<bool(QString&)> thread_chkFunction,
		std::function<bool(QString&)> thread_desFunction,
		std::function<bool(QString&, QString&)> thread_runFunction,
		std::function<bool(QString&, QString&)> thread_execFunction,
		std::function<void()> thread_fluFunction
	);
	static int infinity_runtime_scriptPath(lua_State* state);

	static int infinity_console_println(lua_State* state);
	static int infinity_console_assert(lua_State* state);
	static int infinity_console_cls(lua_State* state);

	static int infinity_thread_current(lua_State* state);
	static int infinity_thread_find(lua_State* state);
	static int infinity_thread_list(lua_State* state);
	static int infinity_thread_create(lua_State* state);
	static int infinity_thread_remove(lua_State* state);
	static int infinity_thread_check(lua_State* state);
	static int infinity_thread_destory(lua_State* state);
	static int infinity_thread_run(lua_State* state);
	static int infinity_thread_exec(lua_State* state);
	static int infinity_thread_flush(lua_State* state);
};

