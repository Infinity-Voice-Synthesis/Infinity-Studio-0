#include "LThread.h"

extern "C" {
#include "Lua/lstate.h"
}

LThread::LThread(QObject *parent)
	: QThread(parent)
{
	this->lstate = luaL_newstate();
	this->lstate->thread_id = (void*)(&(this->Id));
	this->lstate->thread_mutex = (void*)(&(this->idMutex));
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
		bool error = luaL_dofile(this->lstate, this->lFileName.toStdString().c_str());
		if (error) {
			emit this->errorMessage(QString::fromStdString(lua_tostring(this->lstate, -1)));
			lua_pop(this->lstate, 1);
			emit this->tEnded(this->Id);
			return;
		}
	}
	while (this->strList.size() > 0) {
		bool error = luaL_dostring(this->lstate, this->strList.dequeue().toStdString().c_str());
		if (error) {
			emit this->errorMessage(QString::fromStdString(lua_tostring(this->lstate, -1)));
			lua_pop(this->lstate, 1);
		}
	}
	emit this->tEnded(this->Id);
	quit();
}

bool LThread::doFile(QString name)
{
	if (!this->Id.isEmpty()) {
		if (!this->isRunning()) {
			this->tType = LType::DoFile;
			this->lFileName = name;
			this->start();
			return true;
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
		else {
			emit this->normalMessage("The VM is running.Command will wait in queue.");
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

bool LThread::destoryId(QString id)
{
	if (this->isRunning()) {
		this->idMutex.lock();
		this->Id = id;
		this->idMutex.unlock();
		return true;
	}
	return false;
}