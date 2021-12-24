#include "ILLibs.h"

QSet<QString> ILLibs::threadDestoried;

std::function<void(QString&)> ILLibs::console_mesFunction;
std::function<void(QString&)> ILLibs::console_assFunction;
std::function<void()> ILLibs::console_clsFunction;

std::function<bool(QString&)> ILLibs::thread_finFunction;
std::function<QStringList()> ILLibs::thread_lstFunction;
std::function<bool(QString&)> ILLibs::thread_creFunction;
std::function<bool(QString&)> ILLibs::thread_desFunction;
std::function<bool(QString&)> ILLibs::thread_chkFunction;
std::function<bool(QString&, QString&)> ILLibs::thread_runFunction;
std::function<bool(QString&, QString&)> ILLibs::thread_execFunction;

bool ILLibs::isDestoried(lua_State* state)
{
	lua_getfield(state, LUA_REGISTRYINDEX, "_ITHREADID");
	QString tName = QString::fromStdString(luaL_checkstring(state, -1));
	return ILLibs::threadDestoried.contains(tName);
}

void ILLibs::add_destory(QString threadId)
{
	if (!ILLibs::threadDestoried.contains(threadId)) {
		ILLibs::threadDestoried.insert(threadId);
	}
}

void ILLibs::reg_mesFunctions(
	std::function<void(QString&)> console_mesFunction,
	std::function<void(QString&)> console_assFunction,
	std::function<void()> console_clsFunction
)
{
	ILLibs::console_mesFunction = console_mesFunction;
	ILLibs::console_assFunction = console_assFunction;
	ILLibs::console_clsFunction = console_clsFunction;
}

void ILLibs::reg_thrFunctions(
	std::function<bool(QString&)> thread_finFunction,
	std::function<QStringList()> thread_lstFunction,
	std::function<bool(QString&)> thread_creFunction,
	std::function<bool(QString&)> thread_desFunction,
	std::function<bool(QString&)> thread_chkFunction,
	std::function<bool(QString&, QString&)> thread_doFunction,
	std::function<bool(QString&, QString&)> thread_execFunction
)
{
	ILLibs::thread_finFunction = thread_finFunction;
	ILLibs::thread_lstFunction = thread_lstFunction;
	ILLibs::thread_creFunction = thread_creFunction;
	ILLibs::thread_desFunction = thread_desFunction;
	ILLibs::thread_chkFunction = thread_chkFunction;
	ILLibs::thread_runFunction = thread_doFunction;
	ILLibs::thread_execFunction = thread_execFunction;
}

int ILLibs::infinity_runtime_scriptPath(lua_State* state)
{
	if (ILLibs::isDestoried(state)) {
		return 0;
	}
	QString name = QString::fromStdString(luaL_checkstring(state, 1));
	lua_pushstring(state, QString(QCoreApplication::applicationDirPath() + "/scripts/" + name + ".lua").toStdString().c_str());
	return 1;
}

int ILLibs::infinity_console_println(lua_State* state)
{
	if (ILLibs::isDestoried(state)) {
		return 0;
	}
	QString message = QString::fromStdString(luaL_checkstring(state, 1));
	if (!message.isEmpty()) {
		ILLibs::console_mesFunction(message);
	}
	return 0;
}

int ILLibs::infinity_console_assert(lua_State* state)
{
	if (ILLibs::isDestoried(state)) {
		return 0;
	}
	QString message = QString::fromStdString(luaL_checkstring(state, 1));
	if (!message.isEmpty()) {
		ILLibs::console_assFunction(message);
	}
	return 0;
}

int ILLibs::infinity_console_cls(lua_State* state)
{
	if (ILLibs::isDestoried(state)) {
		return 0;
	}
	ILLibs::console_clsFunction();
	return 0;
}

int ILLibs::infinity_thread_current(lua_State* state)
{
	if (ILLibs::isDestoried(state)) {
		return 0;
	}
	lua_getfield(state, LUA_REGISTRYINDEX, "_ITHREADID");
	return 1;
}

int ILLibs::infinity_thread_find(lua_State* state)
{
	if (ILLibs::isDestoried(state)) {
		return 0;
	}
	QString id = QString::fromStdString(luaL_checkstring(state, 1));
	lua_pushboolean(state, ILLibs::thread_finFunction(id));
	return 1;
}

int ILLibs::infinity_thread_list(lua_State* state)
{
	if (ILLibs::isDestoried(state)) {
		return 0;
	}
	QStringList tList = ILLibs::thread_lstFunction();
	lua_newtable(state);
	int count = 0;
	for (auto& s : tList) {
		lua_pushnumber(state, ++count);
		lua_pushstring(state, s.toStdString().c_str());
		lua_settable(state, -3);
	}
	return 1;
}

int ILLibs::infinity_thread_create(lua_State* state)
{
	if (ILLibs::isDestoried(state)) {
		return 0;
	}
	QString id = QString::fromStdString(luaL_checkstring(state, 1));
	bool ok = ILLibs::thread_creFunction(id);
	if (!ok) {
		QString error = QString::asprintf("Can't create thread:%s", qPrintable(id));
		ILLibs::console_assFunction(error);
	}
	lua_pushboolean(state, ok);
	return 1;
}

int ILLibs::infinity_thread_destory(lua_State* state)
{
	if (ILLibs::isDestoried(state)) {
		return 0;
	}
	QString id = QString::fromStdString(luaL_checkstring(state, 1));
	bool ok = ILLibs::thread_desFunction(id);
	if (!ok) {
		QString error = QString::asprintf("Can't destory thread:%s", qPrintable(id));
		ILLibs::console_assFunction(error);
	}
	lua_pushboolean(state, ok);
	return 1;
}

int ILLibs::infinity_thread_check(lua_State* state)
{
	if (ILLibs::isDestoried(state)) {
		return 0;
	}
	QString id = QString::fromStdString(luaL_checkstring(state, 1));
	lua_pushboolean(state, ILLibs::thread_chkFunction(id));
	return 1;
}

int ILLibs::infinity_thread_run(lua_State* state)
{
	if (ILLibs::isDestoried(state)) {
		return 0;
	}
	QString id = QString::fromStdString(luaL_checkstring(state, 1));
	QString str = QString::fromStdString(luaL_checkstring(state, 2));
	bool ok = ILLibs::thread_runFunction(id, str);
	if (!ok) {
		QString error = QString::asprintf("Can't run \"%s\" on thread:%s", qPrintable(str), qPrintable(id));
		ILLibs::console_assFunction(error);
	}
	lua_pushboolean(state, ok);
	return 1;
}

int ILLibs::infinity_thread_exec(lua_State* state)
{
	if (ILLibs::isDestoried(state)) {
		return 0;
	}
	QString id = QString::fromStdString(luaL_checkstring(state, 1));
	QString str = QString::fromStdString(luaL_checkstring(state, 2));
	bool ok = ILLibs::thread_execFunction(id, str);
	if (!ok) {
		QString error = QString::asprintf("Can't execute \"%s\" on thread:%s", qPrintable(str), qPrintable(id));
		ILLibs::console_assFunction(error);
	}
	lua_pushboolean(state, ok);
	return 1;
}
