#pragma once

#include <QString>
#include <QSet>
#include "Lua/lua.hpp"

class ILLibs
{
	static QSet<QString> threadDestoried;
	static std::function<void(QString&)> mesFunction;
	static std::function<void(QString&)> assFunction;
	static std::function<void()> clsFunction;

	static bool isDestoried(lua_State* state);

public:
	static void add_destory(QString threadId);
	static void reg_mesFunctions(std::function<void(QString&)> mesFunction, std::function<void(QString&)> assFunction, std::function<void()> clsFunction);

	static int infinity_console_println(lua_State* state);
	static int infinity_console_assert(lua_State* state);
	static int infinity_console_cls(lua_State* state);
};

