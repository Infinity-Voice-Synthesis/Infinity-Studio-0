#include "StringQueueThread.h"

StringQueueThread::StringQueueThread(QObject *parent)
	: QThread(parent)
{
}

StringQueueThread::~StringQueueThread()
{
}

void StringQueueThread::strConnect(std::function<void(QStringList&)> func)
{
	this->queueMutex.lock();
	this->func = func;
	this->queueMutex.unlock();
}

void StringQueueThread::addMessage(QString message)
{
	this->queueMutex.lock();
	this->messageQueue.enqueue(message);
	this->queueMutex.unlock();
}

void StringQueueThread::run()
{
	while (true)
	{
		QApplication::processEvents();
		if (!this->messageQueue.isEmpty()) {
			this->queueMutex.lock();
			QString message = this->messageQueue.dequeue();
			this->queueMutex.unlock();
			QStringList messList = message.split('\n', Qt::KeepEmptyParts);
			this->func(messList);
		}
		if (this->isInterruptionRequested()) {
			break;
		}
	}
	this->quit();
}
