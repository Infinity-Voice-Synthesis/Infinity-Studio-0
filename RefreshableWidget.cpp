#include "RefreshableWidget.h"

RefreshableWidget::RefreshableWidget(QWidget *parent)
	: QWidget(parent)
{
	connect(&(Infinity_Events::getClass()), &Infinity_Events::resource_refresh, this, &RefreshableWidget::on_resourceRefresh);
}

RefreshableWidget::~RefreshableWidget()
{
}

void RefreshableWidget::on_resourceRefresh()
{
	this->resizeAll();
	this->update();
}

void RefreshableWidget::resizeAll()
{
}

void RefreshableWidget::resizeEvent(QResizeEvent* event)
{
	Q_UNUSED(event);
	this->resizeAll();
}