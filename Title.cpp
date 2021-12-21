#include "Title.h"

Title::Title(QWidget* parent)
	: RefreshableWidget(parent)
{
	this->RAII_alloc();
	if (!Infinity_global::getGlobal().get_RAII_memory_OK()) {
		return;
	}

	closeB->show();
	maxiumB->hide();
	floatB->show();
	miniumB->show();
	menuBar->show();

	connect(closeB, &CloseButton::clicked, this, &Title::closeB_clicked);
	connect(maxiumB, &CloseButton::clicked, this, &Title::maxiumB_clicked);
	connect(floatB, &CloseButton::clicked, this, &Title::floatB_clicked);
	connect(miniumB, &CloseButton::clicked, this, &Title::miniumB_clicked);
	connect(&(Infinity_Events::getClass()), &Infinity_Events::resource_refresh, this, &Title::on_resourceRefresh);

	StyleContainer::getContainer().loadPix("title-icon", QString::fromStdString(StyleContainer::getContainer().getStyleObject()("main-icon")));

	this->setMouseTracking(true);
}

Title::~Title()
{
	this->RAII_free();
}

void Title::RAII_alloc()
{
	while (closeB == nullptr) {
		closeB = new CloseButton(this);
		if (closeB == nullptr) {
			QMessageBox::Button result = QMessageBox::critical(this, "Infinity Studio 0", "Application can't alloc memory for object \"closeB\" on heap!\nPlease check your memory then retry or abort this application!", QMessageBox::Retry | QMessageBox::Button::Abort, QMessageBox::Abort);
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
	while (maxiumB == nullptr) {
		maxiumB = new MaxiumButton(this);
		if (maxiumB == nullptr) {
			QMessageBox::Button result = QMessageBox::critical(this, "Infinity Studio 0", "Application can't alloc memory for object \"maxiumB\" on heap!\nPlease check your memory then retry or abort this application!", QMessageBox::Retry | QMessageBox::Button::Abort, QMessageBox::Abort);
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
	while (floatB == nullptr) {
		floatB = new FloatButton(this);
		if (floatB == nullptr) {
			QMessageBox::Button result = QMessageBox::critical(this, "Infinity Studio 0", "Application can't alloc memory for object \"floatB\" on heap!\nPlease check your memory then retry or abort this application!", QMessageBox::Retry | QMessageBox::Button::Abort, QMessageBox::Abort);
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
	while (miniumB == nullptr) {
		miniumB = new MiniumButton(this);
		if (miniumB == nullptr) {
			QMessageBox::Button result = QMessageBox::critical(this, "Infinity Studio 0", "Application can't alloc memory for object \"miniumB\" on heap!\nPlease check your memory then retry or abort this application!", QMessageBox::Retry | QMessageBox::Button::Abort, QMessageBox::Abort);
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
	while (menuBar == nullptr) {
		menuBar = new MainMenuBar(this);
		if (menuBar == nullptr) {
			QMessageBox::Button result = QMessageBox::critical(this, "Infinity Studio 0", "Application can't alloc memory for object \"menuBar\" on heap!\nPlease check your memory then retry or abort this application!", QMessageBox::Retry | QMessageBox::Button::Abort, QMessageBox::Abort);
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

void Title::RAII_free()
{
	menuBar->deleteLater();
	menuBar = nullptr;

	miniumB->deleteLater();
	miniumB = nullptr;

	floatB->deleteLater();
	floatB = nullptr;

	maxiumB->deleteLater();
	maxiumB = nullptr;

	closeB->deleteLater();
	closeB = nullptr;
}

void Title::on_resourceRefresh()
{
	StyleContainer::getContainer().loadPix("title-icon", QString::fromStdString(StyleContainer::getContainer().getStyleObject()("main-icon")));
	this->resizeAll();
	this->repaint();
}

void Title::resizeAll()
{
	QSize screenSize = Infinity_global::getScreenSize();

	double buttonw = 0.03;
	StyleContainer::getContainer().getStyleObject()["title"].Get("button-width", buttonw);
	int button_width = (double)((double)screenSize.width() * buttonw);

	closeB->move(this->width() - button_width, 0);
	closeB->resize(button_width, this->height());
	closeB->raise();

	maxiumB->move(this->width() - button_width * 2, 0);
	maxiumB->resize(button_width, this->height());
	maxiumB->raise();

	floatB->move(this->width() - button_width * 2, 0);
	floatB->resize(button_width, this->height());
	floatB->raise();

	miniumB->move(this->width() - button_width * 3, 0);
	miniumB->resize(button_width, this->height());
	miniumB->raise();

	//

	double icon_rWidth = 0;
	StyleContainer::getContainer().getStyleObject()["title"].Get("icon-rect-width", icon_rWidth);

	double font_pixel_size = 0, font_border_width = 0;
	StyleContainer::getContainer().getStyleObject()["title"].Get("font-pixel-size", font_pixel_size);
	StyleContainer::getContainer().getStyleObject()["title"].Get("font-border-width", font_border_width);
	int font_pixel_size_i = (double)(font_pixel_size * (double)screenSize.width());
	int font_border_width_i = (double)(font_border_width * (double)screenSize.width());

	double icon_px = 0, icon_py = 0;
	StyleContainer::getContainer().getStyleObject()["title"].Get("icon-px", icon_px);
	StyleContainer::getContainer().getStyleObject()["title"].Get("icon-py", icon_py);

	QPainter painter(this);
	QFont font;
	font.setPixelSize(font_pixel_size_i);
	painter.setFont(font);
	QPen pen;
	pen.setWidth(1);
	pen.setStyle(Qt::SolidLine);
	pen.setCapStyle(Qt::RoundCap);
	pen.setJoinStyle(Qt::RoundJoin);
	painter.setPen(pen);

	int head_div_width = painter.fontMetrics().horizontalAdvance(this->titleHead) + (font_border_width_i * 2);

	int button_area_width = button_width * 3;

	double main_menubar_mWidth = 0.475;
	StyleContainer::getContainer().getStyleObject()["main-menu-bar"].Get("width-maxmium", main_menubar_mWidth);
	int main_menubar_mWidth_i = (double)((double)this->width() * main_menubar_mWidth) - ((double)screenSize.width() * icon_rWidth);

	int title_empty_area = this->width() - button_area_width - main_menubar_mWidth_i - ((double)screenSize.width() * icon_rWidth);

	bool head_compact_mode = head_div_width > title_empty_area;//紧凑模式

	if (head_compact_mode) {
		this->menuBar->move((double)((double)screenSize.width() * icon_rWidth), 0);
		this->menuBar->resize(main_menubar_mWidth_i, this->height());
		this->menuBar->show();
		this->menuBar->raise();
	}
	else {
		int title_paint_width = painter.fontMetrics().horizontalAdvance(this->titleHead);
		this->menuBar->move((double)((double)screenSize.width() * icon_rWidth), 0);
		this->menuBar->resize((this->width() / 2) - (head_div_width / 2) - (double)((double)screenSize.width() * icon_rWidth), this->height());
		this->menuBar->show();
		this->menuBar->raise();
	}
	QSize iconSourceSize = StyleContainer::getContainer().getSourcePix("title-icon").size();
	int icon_cenx = (screenSize.width() * icon_rWidth) / 2, icon_ceny = this->height() / 2;
	double icon_scale = qMin((double)((double)((screenSize.width() * icon_rWidth) * icon_px) / (double)iconSourceSize.width()), (double)((double)(this->height() * icon_py) / (double)iconSourceSize.height()));
	StyleContainer::getContainer().scalePix("title-icon", icon_scale);
}

void Title::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);

	QSize screenSize = Infinity_global::getScreenSize();

	QPainter painter(this);
	painter.setRenderHints(QPainter::SmoothPixmapTransform);

	QColor titleBackgroundColor = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["title"]("color-background")));
	painter.fillRect(0, 0, this->width(), this->height(), titleBackgroundColor);

	double icon_rWidth = 0;
	StyleContainer::getContainer().getStyleObject()["title"].Get("icon-rect-width", icon_rWidth);

	double icon_px = 0, icon_py = 0;
	StyleContainer::getContainer().getStyleObject()["title"].Get("icon-px", icon_px);
	StyleContainer::getContainer().getStyleObject()["title"].Get("icon-py", icon_py);

	QPixmap& pix_icon = StyleContainer::getContainer().getPix("title-icon");

	int icon_cenx = (screenSize.width() * icon_rWidth) / 2, icon_ceny = this->height() / 2;

	painter.drawPixmap(icon_cenx - (double)((double)pix_icon.width() / (double)2), icon_ceny - (double)((double)pix_icon.height() / (double)2), pix_icon.width(), pix_icon.height(), pix_icon);

	//

	double font_pixel_size = 0, font_border_width = 0;
	StyleContainer::getContainer().getStyleObject()["title"].Get("font-pixel-size", font_pixel_size);
	StyleContainer::getContainer().getStyleObject()["title"].Get("font-border-width", font_border_width);

	QColor color = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["title"]("color")));

	int font_pixel_size_i = (double)(font_pixel_size * (double)screenSize.width());
	int font_border_width_i = (double)(font_border_width * (double)screenSize.width());

	//

	QFont font;
	font.setPixelSize(font_pixel_size_i);
	painter.setFont(font);
	QPen pen;
	pen.setWidth(1);
	pen.setColor(color);
	pen.setStyle(Qt::SolidLine);
	pen.setCapStyle(Qt::RoundCap);
	pen.setJoinStyle(Qt::RoundJoin);
	painter.setPen(pen);

	int head_div_width = painter.fontMetrics().horizontalAdvance(this->titleHead) + (font_border_width_i * 2);

	double buttonw = 0.03;
	StyleContainer::getContainer().getStyleObject()["title"].Get("button-width", buttonw);
	int button_width = (double)((double)screenSize.width() * buttonw);
	int button_area_width = button_width * 3;

	double main_menubar_mWidth = 0.475;
	StyleContainer::getContainer().getStyleObject()["main-menu-bar"].Get("width-maxmium", main_menubar_mWidth);
	int main_menubar_mWidth_i = (double)((double)this->width() * main_menubar_mWidth) - ((double)screenSize.width() * icon_rWidth);

	int title_empty_area = this->width() - button_area_width - main_menubar_mWidth_i - ((double)screenSize.width() * icon_rWidth);

	bool head_compact_mode = head_div_width > title_empty_area;//紧凑模式

	if (head_compact_mode) {
		QString trueText = this->titleHead;
		for (int i = 0; i < this->titleHead.length(); i++) {
			trueText = this->titleHead.left(this->titleHead.length() - i) + "...";
			head_div_width = painter.fontMetrics().horizontalAdvance(trueText) + (font_border_width_i * 2);
			if (head_div_width <= title_empty_area) {
				int title_paint_width = painter.fontMetrics().horizontalAdvance(trueText);
				QPoint head_point(main_menubar_mWidth_i + (double)((double)screenSize.width() * icon_rWidth) + font_border_width_i, (this->height() / 2) + (painter.fontMetrics().boundingRect('I').height() / 2));
				painter.drawText(head_point, trueText);
				break;
			}
		}
	}
	else {
		int title_paint_width = painter.fontMetrics().horizontalAdvance(this->titleHead);
		QPoint head_point((this->width() / 2) - (title_paint_width / 2), (this->height() / 2) + (painter.fontMetrics().boundingRect('I').height() / 2));
		painter.drawText(head_point, this->titleHead);
	}
}

void Title::setWindowMaxium(bool windowMaxium)
{
	if (windowMaxium) {
		floatB->show();
		maxiumB->hide();
	}
	else {
		maxiumB->show();
		floatB->hide();
	}
}

void Title::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton) {
		this->mousePressed = true;
		this->mouseStartPoint = event->globalPos();
		this->windowTopLeftPoint = reinterpret_cast<QWidget*>(parent())->frameGeometry().topLeft();
	}
}

void Title::mouseMoveEvent(QMouseEvent* event)
{
	Q_UNUSED(event);
	if (this->mousePressed) {
		QPoint distance = event->globalPos() - this->mouseStartPoint;

		if (event->globalPos().y() == 0) {
			emit maxiumB_clicked();
		}
		else {
			if (reinterpret_cast<QMainWindow*>(parent())->isMaximized()) {
				emit floatB_clicked();
			}
			emit windowMove(this->windowTopLeftPoint + distance);
		}
	}
}

void Title::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton) {
		this->mousePressed = false;
	}
}

void Title::leaveEvent(QEvent* event)
{
	Q_UNUSED(event);
	this->mousePressed = false;
}

void Title::mouseDoubleClickEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton) {
		this->mousePressed = false;
		if (reinterpret_cast<QMainWindow*>(parent())->isMaximized()) {
			emit floatB_clicked();
		}
		else {
			emit maxiumB_clicked();
		}
	}
}
