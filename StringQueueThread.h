#pragma once

#include <QThread>
#include <QMutex>
#include <QQueue>
#include <QApplication>

class StringQueueThread : public QThread
{
	Q_OBJECT

public:
	StringQueueThread(QObject *parent);
	~StringQueueThread();
	void strConnect(std::function<void(QStringList&)> func);
	void clear();

private:
	QMutex queueMutex;
	std::function<void(QStringList&)> func;
	QQueue<QString> messageQueue;

	QStringList strTemps;

protected:
	void run()override;

public slots:
	void addMessage(QString message);
};
