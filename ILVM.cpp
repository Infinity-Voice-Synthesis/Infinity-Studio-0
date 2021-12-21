#include "ILVM.h"

ILVM ILVM::vm = ILVM(nullptr);
QString ILVM::outStrTemp;

void ILVM::lStdOut(const char* data, size_t size)
{
	for (int i = 0; i < size; i++) {
		ILVM::outStrTemp.append(data[i]);
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
}

ILVM::~ILVM()
{
	if (this->mainThread != nullptr) {
		if (this->mainThread->isRunning()) {
			this->mainThread->terminate();
			this->mainThread->wait();
		}
		this->mainThread->deleteLater();
		this->mainThread = nullptr;
	}
	for (auto thread : this->threads) {
		if (thread->isRunning()) {
			thread->terminate();
			thread->wait();
		}
		thread->deleteLater();
	}
	this->threads.clear();
}

ILVM& ILVM::getVM()
{
	return ILVM::vm;
}

void ILVM::on_commandsIn(QString command)
{
	if (this->mainThread == nullptr) {
		while (this->mainThread == nullptr) {
			this->mainThread = new LThread(this);
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
		connect(this->mainThread, &LThread::errorMessage, this, &ILVM::errorMessage, Qt::ConnectionType::QueuedConnection);
		connect(this->mainThread, &LThread::normalMessage, this, &ILVM::normalMessage, Qt::ConnectionType::QueuedConnection);
		connect(this->mainThread, &LThread::tStarted, this, &ILVM::on_threadStart, Qt::ConnectionType::QueuedConnection);
		connect(this->mainThread, &LThread::tEnded, this, &ILVM::on_threadStop, Qt::ConnectionType::QueuedConnection);

		this->mainThread->setId(this->mainId);

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
