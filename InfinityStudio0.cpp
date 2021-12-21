#include "InfinityStudio0.h"

InfinityStudio0::InfinityStudio0(QWidget* parent)
	: QMainWindow(parent)
{
	this->RAII_alloc();
	if (!Infinity_global::getGlobal().get_RAII_memory_OK()) {
		return;
	}

	QSize screenSize = Infinity_global::getScreenSize();

	double win_width = 0.8, win_height = 0.8;
	StyleContainer::getContainer().getStyleObject().Get("window-width", win_width);
	StyleContainer::getContainer().getStyleObject().Get("window-height", win_height);

	double win_MWidth = 0.6, win_MHeight = 0.6;
	StyleContainer::getContainer().getStyleObject().Get("window-minimum-width", win_MWidth);
	StyleContainer::getContainer().getStyleObject().Get("window-minimum-height", win_MHeight);
	this->setMinimumWidth(screenSize.width() * win_MWidth);
	this->setMinimumHeight(screenSize.height() * win_MHeight);

	this->setWindowTitle("Infinity Studio 0");
	this->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	this->setMouseTracking(true);
	this->resize(screenSize.width() * win_width, screenSize.height() * win_height);
	this->showMaximized();

	connect(title, &Title::closeB_clicked, this, &InfinityStudio0::on_title_close);
	connect(title, &Title::maxiumB_clicked, this, &InfinityStudio0::on_title_maxium);
	connect(title, &Title::floatB_clicked, this, &InfinityStudio0::on_title_float);
	connect(title, &Title::miniumB_clicked, this, &InfinityStudio0::on_title_minium);

	connect(title, &Title::windowMove, this, &InfinityStudio0::on_windowMove);

	connect(&(Infinity_Events::getClass()), &Infinity_Events::view_show, central, &CentralWidget::on_viewShow);
	connect(&(Infinity_Events::getClass()), &Infinity_Events::resource_refresh, this, &InfinityStudio0::on_resourceRefresh);
	connect(&(Infinity_Events::getClass()), &Infinity_Events::console_click, this, &InfinityStudio0::on_consoleChanged);
	connect(&(Infinity_Events::getClass()), &Infinity_Events::background_fast, this, &InfinityStudio0::on_fastModeChanged);

	connect(this, &InfinityStudio0::consoleFastReady, &(Infinity_Events::getClass()), &Infinity_Events::on_console_ready);

	StyleContainer::getContainer().loadPix("pic-background-select", QString::fromStdString(StyleContainer::getContainer().getStyleObject()("pic-background-select")));
	StyleContainer::getContainer().loadPix("pic-background", QString::fromStdString(StyleContainer::getContainer().getStyleObject()("pic-background")));
	StyleContainer::getContainer().loadPix("main-icon", QString::fromStdString(StyleContainer::getContainer().getStyleObject()("main-icon")));

	title->show();
	tools->show();
	status->show();
	central->show();
	console->hide();
}

InfinityStudio0::~InfinityStudio0()
{
	this->RAII_free();
}

void InfinityStudio0::RAII_alloc()
{
	while (title == nullptr) {
		title = new Title(this);
		if (title == nullptr) {
			QMessageBox::Button result = QMessageBox::critical(this, "Infinity Studio 0", "Application can't alloc memory for object \"title\" on heap!\nPlease check your memory then retry or abort this application!", QMessageBox::Retry | QMessageBox::Button::Abort, QMessageBox::Abort);
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

	while (tools == nullptr) {
		tools = new ToolBar(this);
		if (tools == nullptr) {
			QMessageBox::Button result = QMessageBox::critical(this, "Infinity Studio 0", "Application can't alloc memory for object \"tools\" on heap!\nPlease check your memory then retry or abort this application!", QMessageBox::Retry | QMessageBox::Button::Abort, QMessageBox::Abort);
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

	while (status == nullptr) {
		status = new StatusBar(this);
		if (status == nullptr) {
			QMessageBox::Button result = QMessageBox::critical(this, "Infinity Studio 0", "Application can't alloc memory for object \"status\" on heap!\nPlease check your memory then retry or abort this application!", QMessageBox::Retry | QMessageBox::Button::Abort, QMessageBox::Abort);
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

	while (central == nullptr) {
		central = new CentralWidget(this);
		if (central == nullptr) {
			QMessageBox::Button result = QMessageBox::critical(this, "Infinity Studio 0", "Application can't alloc memory for object \"central\" on heap!\nPlease check your memory then retry or abort this application!", QMessageBox::Retry | QMessageBox::Button::Abort, QMessageBox::Abort);
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

	while (console == nullptr) {
		console = new ConsoleWidget(this);
		if (console == nullptr) {
			QMessageBox::Button result = QMessageBox::critical(this, "Infinity Studio 0", "Application can't alloc memory for object \"console\" on heap!\nPlease check your memory then retry or abort this application!", QMessageBox::Retry | QMessageBox::Button::Abort, QMessageBox::Abort);
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
}

void InfinityStudio0::RAII_free()
{
	console->deleteLater();
	console = nullptr;

	central->deleteLater();
	central = nullptr;

	status->deleteLater();
	status = nullptr;

	tools->deleteLater();
	tools = nullptr;

	title->deleteLater();
	title = nullptr;
}

void InfinityStudio0::on_resourceRefresh()
{
	StyleContainer::getContainer().loadPix("pic-background-select", QString::fromStdString(StyleContainer::getContainer().getStyleObject()("pic-background-select")));
	StyleContainer::getContainer().loadPix("pic-background", QString::fromStdString(StyleContainer::getContainer().getStyleObject()("pic-background")));
	StyleContainer::getContainer().loadPix("main-icon", QString::fromStdString(StyleContainer::getContainer().getStyleObject()("main-icon")));
	this->resizeAll();
	this->update();
}

void InfinityStudio0::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);

	QSize screenSize = Infinity_global::getScreenSize();

	QPainter painter(this);
	if (this->fastMode) {
		painter.setRenderHint(QPainter::RenderHint::SmoothPixmapTransform, false);
	}
	else {
		painter.setRenderHint(QPainter::RenderHint::SmoothPixmapTransform, true);
	}

	auto styleSrcFun = [&](QString key)->QString
	{
		return QString(
			QCoreApplication::applicationDirPath() +
			QString("/themes/") +
			Infinity_global::projectName + "/" +
			QString::fromStdString(StyleContainer::getContainer().getStyleObject()(key.toStdString()))
		);
	};

	QColor mainBackgroundColor = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()("color-background")));
	bool pic_background_diy = false;
	StyleContainer::getContainer().getStyleObject().Get("pic-background-diy", pic_background_diy);

	painter.fillRect(0, 0, this->width(), this->height(), mainBackgroundColor);

	if (pic_background_diy) {
		QPixmap& pic_background = StyleContainer::getContainer().getPix("pic-background-select");

		double pic_background_transparency = 1;
		StyleContainer::getContainer().getStyleObject().Get("pic-background-transparency", pic_background_transparency);

		double title_height = 0.04;
		StyleContainer::getContainer().getStyleObject()["title"].Get("height", title_height);
		double tools_width = 0.05;
		StyleContainer::getContainer().getStyleObject()["tools"].Get("width", tools_width);
		bool tools_left = true;
		StyleContainer::getContainer().getStyleObject()["tools"].Get("left", tools_left);
		double status_height = 0.03;
		StyleContainer::getContainer().getStyleObject()["status"].Get("height", status_height);

		int title_height_i = (double)(screenSize.height() * title_height);
		int tools_width_i = (double)(screenSize.width() * tools_width);
		int status_height_i = (double)(screenSize.height() * status_height);

		double pb_centx = (double)(this->width() - tools_width_i) * 0.5;
		double pb_centy = (double)(this->height() - title_height_i - status_height_i) * 0.5;

		if (tools_left) {
			pb_centx += tools_width_i;
		}
		pb_centy += title_height_i;

		int pb_wtrue = pic_background.width();
		int pb_htrue = pic_background.height();
		int pb_xpos = pb_centx - pb_wtrue / 2;
		int pb_ypos = pb_centy - pb_htrue / 2;

		painter.drawPixmap(pb_xpos, pb_ypos, pb_wtrue, pb_htrue, pic_background);

		QColor color_background_hover;
		if ((mainBackgroundColor.red() + mainBackgroundColor.green() + mainBackgroundColor.blue()) > 255 * 1.5) {
			color_background_hover.setRgb(255, 255, 255, 255 * (1 - pic_background_transparency));
		}
		else {
			color_background_hover.setRgb(0, 0, 0, 255 * (1 - pic_background_transparency));
		}

		painter.fillRect(pb_xpos, pb_ypos, pb_wtrue, pb_htrue, color_background_hover);
	}
	else {
		QPixmap& pic_background = StyleContainer::getContainer().getPix("pic-background");

		double pic_background_cx = 0.5, pic_background_cy = 0.5;
		StyleContainer::getContainer().getStyleObject().Get("pic-background-cx", pic_background_cx);
		StyleContainer::getContainer().getStyleObject().Get("pic-background-cy", pic_background_cy);

		double title_height = 0.04;
		StyleContainer::getContainer().getStyleObject()["title"].Get("height", title_height);
		double tools_width = 0.05;
		StyleContainer::getContainer().getStyleObject()["tools"].Get("width", tools_width);
		bool tools_left = true;
		StyleContainer::getContainer().getStyleObject()["tools"].Get("left", tools_left);
		double status_height = 0.03;
		StyleContainer::getContainer().getStyleObject()["status"].Get("height", status_height);

		int title_height_i = (double)(screenSize.height() * title_height);
		int tools_width_i = (double)(screenSize.width() * tools_width);
		int status_height_i = (double)(screenSize.height() * status_height);

		double pb_centx = (double)(this->width() - tools_width_i) * pic_background_cx;
		double pb_centy = (double)(this->height() - title_height_i - status_height_i) * pic_background_cy;

		if (tools_left) {
			pb_centx += tools_width_i;
		}
		pb_centy += title_height_i;

		int pb_wtrue = pic_background.width();
		int pb_htrue = pic_background.height();
		int pb_xpos = pb_centx - pb_wtrue / 2;
		int pb_ypos = pb_centy - pb_htrue / 2;

		painter.drawPixmap(pb_xpos, pb_ypos, pb_wtrue, pb_htrue, pic_background);
	}

	QIcon main_icon(StyleContainer::getContainer().getPix("main-icon"));
	this->setWindowIcon(main_icon);
}

void InfinityStudio0::resizeEvent(QResizeEvent* event)
{
	Q_UNUSED(event);

	this->resizeAll();
}

void InfinityStudio0::resizeAll()
{
	QSize screenSize = Infinity_global::getScreenSize();

	double title_height = 0.04;
	StyleContainer::getContainer().getStyleObject()["title"].Get("height", title_height);
	double tools_width = 0.05;
	StyleContainer::getContainer().getStyleObject()["tools"].Get("width", tools_width);
	bool tools_left = true;
	StyleContainer::getContainer().getStyleObject()["tools"].Get("left", tools_left);
	double status_height = 0.03;
	StyleContainer::getContainer().getStyleObject()["status"].Get("height", status_height);

	int title_height_i = (double)(screenSize.height() * title_height);
	int tools_width_i = (double)(screenSize.width() * tools_width);
	int status_height_i = (double)(screenSize.height() * status_height);

	{
		QSize pixSourceSize = StyleContainer::getContainer().getSourcePix("pic-background-select").size();

		double pb_scalex = (double)((double)(this->width() - tools_width_i) / (double)pixSourceSize.width());
		double pb_scaley = (double)((double)(this->height() - title_height_i - status_height_i) / (double)pixSourceSize.height());

		double pb_trueScale = qMax(pb_scalex, pb_scaley);
		StyleContainer::getContainer().scalePix("pic-background-select", pb_trueScale);
	}
	{
		double pic_background_px = 0.4, pic_background_py = 0.4;
		StyleContainer::getContainer().getStyleObject().Get("pic-background-px", pic_background_px);
		StyleContainer::getContainer().getStyleObject().Get("pic-background-py", pic_background_py);
		QSize pixSourceSize = StyleContainer::getContainer().getSourcePix("pic-background").size();

		double pb_scalex = (double)((double)((double)(this->width() - tools_width_i) * pic_background_px) / (double)pixSourceSize.width());
		double pb_scaley = (double)((double)((double)(this->height() - title_height_i - status_height_i) * pic_background_py) / (double)pixSourceSize.height());

		double pb_trueScale = qMin(pb_scalex, pb_scaley);
		StyleContainer::getContainer().scalePix("pic-background", pb_trueScale);
	}

	title->move(0, 0);
	title->resize(this->width(), (double)(screenSize.height() * title_height));
	title->raise();

	title->setWindowMaxium(this->isMaximized());

	if (tools_left) {
		tools->move(0, (double)(screenSize.height() * title_height));
	}
	else {
		tools->move(this->width() - (double)(screenSize.width() * tools_width), (double)(screenSize.height() * title_height));
	}
	tools->resize((double)(screenSize.width() * tools_width), this->height() - (double)(screenSize.height() * title_height) - (double)(screenSize.height() * status_height));
	tools->raise();

	tools->setLeft(tools_left);

	status->move(0, this->height() - (double)(screenSize.height() * status_height));
	status->resize(this->width(), (double)(screenSize.height() * status_height));
	status->raise();

	central->move((double)(screenSize.width() * tools_width), (double)(screenSize.height() * title_height));
	central->resize(this->width() - (double)(screenSize.width() * tools_width), this->height() - (double)(screenSize.height() * title_height) - (double)(screenSize.height() * status_height));
	central->raise();

	console->move((double)(screenSize.width() * tools_width), (double)(screenSize.height() * title_height));
	console->resize(this->width() - (double)(screenSize.width() * tools_width), this->height() - (double)(screenSize.height() * title_height) - (double)(screenSize.height() * status_height));
	console->raise();
}

void InfinityStudio0::on_title_close()
{
	this->close();
}

void InfinityStudio0::on_title_maxium()
{
	this->showMaximized();
}

void InfinityStudio0::on_title_float()
{
	this->showNormal();
}

void InfinityStudio0::on_title_minium()
{
	this->showMinimized();
}

void InfinityStudio0::on_windowMove(QPoint pos)
{
	this->move(pos);
}

void InfinityStudio0::on_consoleChanged()
{
	this->consoleOn = !this->consoleOn;
	if (this->consoleOn) {
		this->central->hide();
		this->console->show();
		this->console->setFocus();
	}
	else {
		this->console->hide();
		this->central->show();
	}
	emit this->consoleFastReady(this->consoleOn);
}

void InfinityStudio0::on_fastModeChanged(bool fast)
{
	this->fastMode = fast;
	this->update();
}