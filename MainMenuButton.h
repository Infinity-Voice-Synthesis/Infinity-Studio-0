#pragma once

#include <QWidget>
#include <QString>
#include <QPainter>
#include "Infinity_global.h"
#include <QMouseEvent>
#include "StyleContainer.h"
#include "RefreshableWidget.h"

class MainMenuButton : public RefreshableWidget
{
	Q_OBJECT

public:
	MainMenuButton(QWidget* parent = Q_NULLPTR);
	~MainMenuButton();

	void setText(QString text);
	void setId(QString id);
	void setFontPixelSize(double size);

	QString getId() const;

	enum class MenuButtonState
	{
		Normal = 0,
		Hover = 1,
		Checked = 2,
		OtherChecked = 3
	};

	MenuButtonState getState() const;

private:

	QString text;
	QString id;
	double font_pixel_size = 0.009;

	MenuButtonState state = MenuButtonState::Normal;

	bool inWidget(QPoint pos);

	bool activeFlag = false;
protected:
	void paintEvent(QPaintEvent* event)override;

	void mousePressEvent(QMouseEvent* event)override;
	void mouseMoveEvent(QMouseEvent* event)override;
	void mouseReleaseEvent(QMouseEvent* event)override;
	void leaveEvent(QEvent* event)override;
public slots:
	void resetButton();
	void setButtonWait();
signals:
	void active(bool ok);
};
