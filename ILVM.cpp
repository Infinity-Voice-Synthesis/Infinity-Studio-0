#include "ILVM.h"

ILVM ILVM::vm = ILVM(nullptr);
QString ILVM::outStrTemp;
quint64 ILVM::t_count = 0;

void ILVM::lStdOut(const char* data, size_t size)
{
	for (int i = 0; i < size; i++) {
		ILVM::outStrTemp.append(data[i]);
		QApplication::processEvents();
	}
}

void ILVM::lStdOutLine()
{
	emit ILVM::getVM().normalMessage(ILVM::outStrTemp);
	ILVM::outStrTemp.clear();
}

void ILVM::lStdOutErr(const char* format, const char* data)
{
	emit ILVM::getVM().errorMessage(QString::asprintf(format, data));
}

ILVM::ILVM(QObject *parent)
	: QObject(parent)
{
	set_LUA_InfOChar(ILVM::lStdOut);
	set_LUA_InfOLine(ILVM::lStdOutLine);
	set_LUA_InfOError(ILVM::lStdOutErr);

	ILLibs::reg_mesFunctions(
		[this](QString message) {emit this->normalMessage(message); },
		[this](QString message) {emit this->errorMessage(message); },
		[this] {emit this->clearMessage(); }
	);
}

ILVM::~ILVM()
{
	this->mainThread = nullptr;

	for (auto thread : this->threads) {
		if (thread->isRunning()) {
			thread->terminate();
			thread->wait();
		}
		thread->deleteLater();
	}
	this->threads.clear();

	for (auto thread : this->threads_bin) {
		if (thread->isRunning()) {
			thread->terminate();
			thread->wait();
		}
		thread->deleteLater();
	}
	this->threads_bin.clear();
}

ILVM& ILVM::getVM()
{
	return ILVM::vm;
}

void ILVM::on_commandsIn(QString command)
{
	if (this->mainThread == nullptr) {
		while (this->mainThread == nullptr) {
			this->mainThread = new(std::nothrow) LThread(this);
			if (this->mainThread == nullptr) {
				QMessageBox::Button result = QMessageBox::critical(nullptr, "Infinity Studio 0", "Application can't alloc memory for object \"mainThread\" on heap!\nPlease check your memory then retry or abort this application!", QMessageBox::Retry | QMessageBox::Button::Abort, QMessageBox::Abort);
				if (result != QMessageBox::Retry) {
					if (Infinity_global::getGlobal().get_App_init_OK()) {
						Infinity_global::getGlobal().set_RAII_memory_OK(false);
						QApplication::exit(-1);
					}
					Infinity_global::getGlobal().set_RAII_memory_OK(false);
					return;
				}
			}
		}
		this->threads.append(this->mainThread);

		if (this->isSafeMode) {
			this->VMPushOptionalFunctions(this->mainThread);
		}
		else {
			this->VMPushAllFunctions(this->mainThread);
		}

		connect(this->mainThread, &LThread::errorMessage, this, &ILVM::errorMessage, Qt::ConnectionType::QueuedConnection);
		connect(this->mainThread, &LThread::normalMessage, this, &ILVM::normalMessage, Qt::ConnectionType::QueuedConnection);
		connect(this->mainThread, &LThread::tStarted, this, &ILVM::on_threadStart, Qt::ConnectionType::QueuedConnection);
		connect(this->mainThread, &LThread::tEnded, this, &ILVM::on_threadStop, Qt::ConnectionType::QueuedConnection);

		this->mainThread->setId(this->mainId + "_" + QString::number(ILVM::t_count));
		ILVM::t_count++;

		emit this->normalMessage(QString("VM initialized: "  LUA_VERSION));
	}
	if (this->mainThread->isRunning()) {
		emit this->normalMessage("The VM is running.Command will wait in queue.");
	}
	if (!this->mainThread->doString(command)) {
		emit this->errorMessage("Can't execute the command!");
	}
}

void ILVM::on_threadStart(QString id)
{
	if (id == this->mainId) {
		emit this->mainStart();
	}
}

void ILVM::on_threadStop(QString id)
{
	if (id == this->mainId) {
		emit this->mainStop();
	}
}

void ILVM::mainCritical()
{
	for (int i = 0; i < this->threads.size(); i++) {
		LThread* thread = this->threads.at(i);
		if (thread->getId() == this->mainId) {
			if (thread->isRunning()) {
				this->mainThread = nullptr;

				disconnect(thread, &LThread::errorMessage, this, &ILVM::errorMessage);
				disconnect(thread, &LThread::normalMessage, this, &ILVM::normalMessage);
				disconnect(thread, &LThread::tStarted, this, &ILVM::on_threadStart);
				disconnect(thread, &LThread::tEnded, this, &ILVM::on_threadStop);

				this->threads.removeAt(i);
				this->threads_bin.append(thread);

				thread->quit();

				ILLibs::add_destory(thread->getId());

				this->isSafeMode = true;

				emit this->mainStop();
				emit this->clearMessage();
				emit this->errorMessage("Warning!!!!! The blocked Lua thread has been put into the background. Please save the data immediately and restart the editor!");
			}
			break;
		}
	}
}

void ILVM::VMPushOptionalFunctions(LThread* thread)
{

}

void ILVM::VMPushAllFunctions(LThread* thread)
{
	thread->beginGlobalTable();

	thread->beginTable("Console");
	thread->addFunction("println", ILLibs::infinity_console_println);
	thread->addFunction("assert", ILLibs::infinity_console_assert);
	thread->addFunction("cls", ILLibs::infinity_console_cls);
	thread->endTable();//Console

	thread->beginTable("Thread");

	thread->endTable();//Thread

	thread->beginTable("Synth");

	thread->endTable();//Synth

	thread->endGlobalTable("Infinity");
}
