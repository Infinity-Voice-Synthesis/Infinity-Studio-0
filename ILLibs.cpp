#include "ILLibs.h"

QSet<QString> ILLibs::threadDestoried;

std::function<void(QString&)> ILLibs::mesFunction;
std::function<void(QString&)> ILLibs::assFunction;
std::function<void()> ILLibs::clsFunction;

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

void ILLibs::reg_mesFunctions(std::function<void(QString&)> mesFunction, std::function<void(QString&)> assFunction, std::function<void()> clsFunction)
{
	ILLibs::mesFunction = mesFunction;
	ILLibs::assFunction = assFunction;
	ILLibs::clsFunction = clsFunction;
}

int ILLibs::infinity_console_println(lua_State* state)
{
	if (ILLibs::isDestoried(state)) {
		return 0;
	}
	QString message = QString::fromStdString(luaL_checkstring(state, 1));
	if (!message.isEmpty()) {
		ILLibs::mesFunction(message);
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
		ILLibs::assFunction(message);
	}
	return 0;
}

int ILLibs::infinity_console_cls(lua_State* state)
{
	if (ILLibs::isDestoried(state)) {
		return 0;
	}
	ILLibs::clsFunction();
	return 0;
}
