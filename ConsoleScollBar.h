#pragma once

#include "VScollBar.h"
#include <QVector>
#include <QPainter>

class ConsoleScollBar : public VScollBar
{
	Q_OBJECT

public:
	ConsoleScollBar(QWidget *parent = Q_NULLPTR);
	~ConsoleScollBar();

	void setTips(QVector<double> tips);

private:
	QVector<double> tips;

protected:
	void paintFlags()override;

};
