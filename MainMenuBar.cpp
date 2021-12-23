#include "MainMenuBar.h"

MainMenuBar::MainMenuBar(QWidget* parent)
	: RefreshableWidget(parent)
{
	for (int i = 0; i < this->buttonList.size(); i++) {
		MainMenuButton* button = nullptr;
		while (button == nullptr) {
			button = new(std::nothrow) MainMenuButton(this);
			if (button == nullptr) {
				QMessageBox::Button result = QMessageBox::critical(this, "Infinity Studio 0", "Application can't alloc memory for object \"button\" on heap!\nPlease check your memory then retry or abort this application!", QMessageBox::Retry | QMessageBox::Button::Abort, QMessageBox::Abort);
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
		button->setText(this->buttonList.at(i));
		button->setId(this->buttonList.at(i));
		button->hide();
		connect(button, &MainMenuButton::active, this, &MainMenuBar::on_active);
		this->buttons.append(button);
	}
	MainMenuButton* moreButton = nullptr;
	while (moreButton == nullptr) {
		moreButton = new(std::nothrow) MainMenuButton(this);
		if (moreButton == nullptr) {
			QMessageBox::Button result = QMessageBox::critical(this, "Infinity Studio 0", "Application can't alloc memory for object \"moreButton\" on heap!\nPlease check your memory then retry or abort this application!", QMessageBox::Retry | QMessageBox::Button::Abort, QMessageBox::Abort);
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
	moreButton->setText(this->strMore);
	moreButton->setId("MMB_More");
	moreButton->hide();
	connect(moreButton, &MainMenuButton::active, this, &MainMenuBar::on_active);
	this->buttons.append(moreButton);

	this->setMouseTracking(true);
}

MainMenuBar::~MainMenuBar()
{
	for (auto bt : this->buttons) {
		bt->deleteLater();
	}
	this->buttons.clear();
}

void MainMenuBar::resizeAll()
{
	QSize screenSize = Infinity_global::getScreenSize();

	double font_pixel_size = 0, font_border_width = 0;
	StyleContainer::getContainer().getStyleObject()["main-menu-bar"].Get("font-pixel-size", font_pixel_size);
	StyleContainer::getContainer().getStyleObject()["main-menu-bar"].Get("font-border-width", font_border_width);
	int font_pixel_size_i = font_pixel_size * screenSize.width();
	int font_border_width_i = font_border_width * screenSize.width();

	QFont font;
	font.setPixelSize(font_pixel_size_i);
	QFontMetrics fontM(font);

	int button_xpos_temp = 0;
	this->moreButtonOn = false;

	for (int i = 0; i < this->buttons.size(); i++) {
		MainMenuButton* buttonHideTemp = this->buttons.at(i);
		buttonHideTemp->hide();
	}
	for (int i = 0; i < this->buttonList.size(); i++) {
		QString strSource = this->buttonList.at(i);
		QString strTrans = QString::fromStdString(StyleContainer::getContainer().getTransObject()(strSource.toStdString()));
		if (strTrans.isEmpty()) {
			strTrans = strSource;
		}
		int more_font_width = fontM.horizontalAdvance(this->strMore);
		int font_width = fontM.horizontalAdvance(strTrans);
		if ((font_width + more_font_width + font_border_width_i * 4) > (this->width() - button_xpos_temp)) {
			MainMenuButton* buttonTemp = this->buttons.at(this->buttonList.size());
			buttonTemp->move(button_xpos_temp, 0);
			buttonTemp->resize(more_font_width + font_border_width_i * 2, this->height());
			buttonTemp->setText(this->strMore);
			buttonTemp->setFontPixelSize(font_pixel_size);
			buttonTemp->show();
			buttonTemp->repaint();
			buttonTemp->raise();
			this->moreButtonOn = true;
			break;
		}
		MainMenuButton* buttonTemp = this->buttons.at(i);
		buttonTemp->move(button_xpos_temp, 0);
		buttonTemp->resize(font_width + font_border_width_i * 2, this->height());
		buttonTemp->setText(strTrans);
		buttonTemp->setFontPixelSize(font_pixel_size);
		buttonTemp->show();
		buttonTemp->repaint();
		buttonTemp->raise();
		button_xpos_temp += (font_width + font_border_width_i * 2);
	}
}

void MainMenuBar::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);
}

void MainMenuBar::on_active(bool ok)
{
	MainMenuButton* button = reinterpret_cast<MainMenuButton*>(sender());
	if (ok) {
		for (auto bt : this->buttons) {
			if (bt != button) {
				bt->setButtonWait();
			}
		}
	}
	else {
		for (auto bt : this->buttons) {
			if (bt != button) {
				bt->resetButton();
			}
		}
	}
}
