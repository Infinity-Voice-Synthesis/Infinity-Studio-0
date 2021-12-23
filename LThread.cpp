#include "LThread.h"

LThread::LThread(QObject *parent)
	: QThread(parent)
{
	this->lstate = luaL_newstate();
	luaL_openlibs(this->lstate);

	bool error1 = luaL_dostring(this->lstate, QString("package.path = '" + QCoreApplication::applicationDirPath() + "/scripts/?.lua;'").toStdString().c_str());
	if (error1) {
		qDebug("Lua Error:%s", qPrintable(lua_tostring(this->lstate, -1)));
		lua_pop(this->lstate, 1);
	}
	bool error2 = luaL_dostring(this->lstate, QString("package.cpath = '" + QCoreApplication::applicationDirPath() + "/scripts/libs/?.dll;'").toStdString().c_str());
	if (error2) {
		qDebug("Lua Error:%s", qPrintable(lua_tostring(this->lstate, -1)));
		lua_pop(this->lstate, 1);
	}
}

LThread::~LThread()
{
	lua_close(this->lstate);
}

void LThread::run()
{
	emit this->tStarted(this->Id);
	if (this->tType == LType::DoFile) {
		bool error = luaL_dofile(this->lstate, QString(QCoreApplication::applicationDirPath() + "/scripts/" + this->lFileName + ".lua").toStdString().c_str());
		if (error) {
			emit this->errorMessage(QString::fromStdString(lua_tostring(this->lstate, -1)));
			lua_pop(this->lstate, 1);
		}
	}
	else if (this->tType == LType::DoString) {
		while (this->strList.size() > 0) {
			bool error = luaL_dostring(this->lstate, this->strList.dequeue().toStdString().c_str());
			if (error) {
				emit this->errorMessage(QString::fromStdString(lua_tostring(this->lstate, -1)));
				lua_pop(this->lstate, 1);
			}
		}
	}
	emit this->tEnded(this->Id);
	quit();
}

bool LThread::doFile(QString name)
{
	if (!this->Id.isEmpty()) {
		if (this->tType != LType::DoString) {
			if (!this->isRunning()) {
				this->tType = LType::DoFile;
				this->lFileName = name;
				this->start();
				return true;
			}
		}
	}
	return false;
}

bool LThread::doString(QString str)
{
	if (!this->Id.isEmpty()) {
		this->tType = LType::DoString;
		this->strList.enqueue(str);
		if (!this->isRunning()) {
			this->start();
		}
		return true;
	}
	return false;
}

bool LThread::setId(QString id)
{
	if (!id.isEmpty()) {
		if (this->Id.isEmpty()) {
			this->Id = id;
			lua_pushstring(this->lstate, "_ITHREADID");
			lua_pushstring(this->lstate, id.toStdString().c_str());
			lua_settable(this->lstate, LUA_REGISTRYINDEX);
			return true;
		}
	}
	return false;
}

QString LThread::getId()
{
	return this->Id;
}

void LThread::beginGlobalTable()
{
	lua_newtable(this->lstate);
}

void LThread::endGlobalTable(QString name)
{
	lua_setglobal(this->lstate, name.toStdString().c_str());
}

void LThread::beginTable(QString name)
{
	lua_pushstring(this->lstate, name.toStdString().c_str());
	lua_newtable(this->lstate);
}

void LThread::endTable()
{
	lua_settable(this->lstate, -3);
}

void LThread::addFunction(QString name, lua_CFunction function)
{
	lua_pushstring(this->lstate, name.toStdString().c_str());
	lua_pushcfunction(this->lstate, function);
	lua_settable(this->lstate, -3);
}
