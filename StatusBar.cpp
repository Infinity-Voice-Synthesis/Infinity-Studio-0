#include "StatusBar.h"

StatusBar::StatusBar(QWidget *parent)
	: RefreshableWidget(parent)
{
	while (consoleb == nullptr) {
		consoleb = new ConsoleButton(this);
		if (consoleb == nullptr) {
			QMessageBox::Button result = QMessageBox::critical(this, "Infinity Studio 0", "Application can't alloc memory for object \"consoleb\" on heap!\nPlease check your memory then retry or abort this application!", QMessageBox::Retry | QMessageBox::Button::Abort, QMessageBox::Abort);
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

	connect(consoleb, &ConsoleButton::clicked, &(Infinity_Events::getClass()), &Infinity_Events::on_console_clicked);
}

StatusBar::~StatusBar()
{
	consoleb->deleteLater();
	consoleb = nullptr;
}

void StatusBar::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);
	QPainter painter(this);

	QColor color_background = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["status"]("color-background")));

	painter.fillRect(0, 0, this->width(), this->height(), color_background);
}

void StatusBar::resizeAll()
{
	QSize screenSize = Infinity_global::getScreenSize();

	double console_width = 0.08;
	StyleContainer::getContainer().getStyleObject()["status"]["console-button"].Get("width", console_width);

	int console_width_i = screenSize.width() * console_width;

	this->consoleb->resize(console_width_i, this->height());
	this->consoleb->move(0, 0);
	this->raise();
	this->show();
}
