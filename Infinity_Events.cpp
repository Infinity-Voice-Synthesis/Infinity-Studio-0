#include "Infinity_Events.h"

Infinity_Events::Infinity_Events(QObject* parent)
	: QObject(parent)
{
}

Infinity_Events::~Infinity_Events()
{
}

Infinity_Events Infinity_Events::IE_Class(nullptr);

Infinity_Events& Infinity_Events::getClass()
{
	return IE_Class;
}

void Infinity_Events::on_button_actived(QString id, bool checked)
{
	if (id == "button-track_view") {
		emit this->view_show(id, checked);
	}
	else if (id == "button-note_view") {
		emit this->view_show(id, checked);
	}
	else if (id == "button-parameter_view") {
		emit this->view_show(id, checked);
	}
	else {

	}
}

void Infinity_Events::on_button_selected(QString id)
{
	if (id == "button-explore") {
		emit this->button_active("button-edit", false);
	}
	else if (id == "button-edit") {
		emit this->button_active("button-explore", false);
	}
	else if (id == "button-note_edit") {
		emit this->button_active("button-phoneme_edit", false);
		emit this->button_active("button-pitch_edit", false);
	}
	else if (id == "button-phoneme_edit") {
		emit this->button_active("button-note_edit", false);
		emit this->button_active("button-pitch_edit", false);
	}
	else if (id == "button-pitch_edit") {
		emit this->button_active("button-note_edit", false);
		emit this->button_active("button-phoneme_edit", false);
	}
	else {

	}
}

void Infinity_Events::on_resource_refresh()
{
	emit this->resource_refresh();
}

void Infinity_Events::on_console_clicked()
{
	emit this->console_click();
}

void Infinity_Events::on_console_ready(bool fast)
{
	this->ConsoleFastReady = fast;
	emit this->background_fast(this->ConsoleFastReady || this->CentralFastReady);
}

void Infinity_Events::on_central_ready(bool fast)
{
	this->CentralFastReady = fast;
	emit this->background_fast(this->ConsoleFastReady || this->CentralFastReady);
}

void Infinity_Events::on_luaErrorMessage(QString message)
{
	emit this->console_error(message);
}

void Infinity_Events::on_luaNormalMessage(QString message)
{
	emit this->console_normal(message);
}

void Infinity_Events::on_luaMainStarted()
{
	emit this->console_mainStart();
}

void Infinity_Events::on_luaMainEnded()
{
	emit this->console_mainEnd();
}

void Infinity_Events::on_console_command(QString command)
{
	emit this->lua_command(command);
}