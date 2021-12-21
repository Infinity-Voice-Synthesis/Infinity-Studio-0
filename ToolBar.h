#pragma once

#include <QWidget>
#include <QPainter>
#include <QVector>
#include <QStringList>
#include "ToolButton.h"
#include "MultiToolButton.h"
#include "PermanentToolButton.h"
#include <QMessageBox>
#include "Infinity_global.h"
#include "StyleContainer.h"
#include <QSet>
#include "Infinity_Events.h"
#include "RefreshableWidget.h"

class ToolBar : public RefreshableWidget
{
	Q_OBJECT

public:
	ToolBar(QWidget* parent = Q_NULLPTR);
	~ToolBar();

	void setLeft(bool left);

private:
	bool left = true;

	QVector<QStringList> buttonList = {
		{
			"button-explore",
			"button-edit"
		},
		{
			"button-track_view",
			"button-note_view",
			"button-parameter_view"
		},
		{
			"button-note_edit",
			"button-phoneme_edit",
			"button-pitch_edit"
		}
	};
	QStringList buttonListPermanent = {
		"button-play_stop"
	};
	QStringList buttonListBottom = {
		"button-loop",
		"button-auto_follow"
	};

	QSet<QString> buttonInitList = {
		"button-explore",
		"button-track_view",
		"button-note_view",
		"button-note_edit"
	};
	QSet<QString> buttonMultiList = {
		"button-explore",
		"button-edit",
		"button-note_edit",
		"button-phoneme_edit",
		"button-pitch_edit"
	};

	QVector<ToolButton*> buttons;
	QVector<ToolButton*> bottomButtons;
	QVector<PermanentToolButton*> permanentButtons;
protected:
	void resizeAll()override;
	void paintEvent(QPaintEvent* event)override;
};
