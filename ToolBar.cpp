#include "ToolBar.h"

ToolBar::ToolBar(QWidget* parent)
	: RefreshableWidget(parent)
{
	for (auto sl : this->buttonList) {
		for (auto s : sl) {
			ToolButton* button = nullptr;
			while (button == nullptr) {
				if (this->buttonMultiList.contains(s)) {
					button = reinterpret_cast<ToolButton*>(new(std::nothrow) MultiToolButton(this));
				}
				else {
					button = new ToolButton(this);
				}
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
			button->setId(s);
			if (this->buttonInitList.contains(s)) {
				button->setChecked(true);
			}
			button->hide();
			if (this->buttonMultiList.contains(s)) {
				connect(reinterpret_cast<MultiToolButton*>(button), &MultiToolButton::selected, &(Infinity_Events::getClass()), &Infinity_Events::on_button_selected);
				connect(&(Infinity_Events::getClass()), &Infinity_Events::button_active, button, &MultiToolButton::activeSlot);
			}
			else {
				connect(button, &ToolButton::actived, &(Infinity_Events::getClass()), &Infinity_Events::on_button_actived);
			}
			this->buttons.append(button);
		}
	}

	for (auto s : this->buttonListBottom) {
		ToolButton* button = nullptr;
		while (button == nullptr) {
			button = new(std::nothrow) ToolButton(this);
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
		button->setId(s);
		if (this->buttonInitList.contains(s)) {
			button->setChecked(true);
		}
		button->hide();
		connect(button, &ToolButton::actived, &(Infinity_Events::getClass()), &Infinity_Events::on_button_actived);
		this->bottomButtons.append(button);
	}

	for (auto s : this->buttonListPermanent) {
		PermanentToolButton* button = nullptr;
		while (button == nullptr) {
			button = new(std::nothrow) PermanentToolButton(this);
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
		button->setId(s);
		if (this->buttonInitList.contains(s)) {
			button->setChecked(true);
		}
		button->hide();
		connect(button, &PermanentToolButton::actived, &(Infinity_Events::getClass()), &Infinity_Events::on_button_actived);
		this->permanentButtons.append(button);
	}
}

ToolBar::~ToolBar()
{
	for (auto bt : this->permanentButtons) {
		bt->deleteLater();
	}
	this->permanentButtons.clear();

	for (auto bt : this->bottomButtons) {
		bt->deleteLater();
	}
	this->bottomButtons.clear();

	for (auto bt : this->buttons) {
		bt->deleteLater();
	}
	this->buttons.clear();
}

void ToolBar::resizeAll()
{
	QSize screenSize = Infinity_global::getScreenSize();

	double button_height = 0.08, button_split = 0.02, button_group_split = 0.05;
	StyleContainer::getContainer().getStyleObject()["tools"].Get("button-height", button_height);
	StyleContainer::getContainer().getStyleObject()["tools"].Get("button-split", button_split);
	StyleContainer::getContainer().getStyleObject()["tools"].Get("button-group-split", button_group_split);

	int button_height_i = button_height * screenSize.height();
	int button_split_i = button_split * screenSize.height();
	int button_group_split_i = button_group_split * screenSize.height();

	for (int i = 0, count = 0; i < this->buttonList.size(); i++) {
		QStringList list = this->buttonList.at(i);
		for (int j = 0; j < list.size(); j++, count++) {
			int posy = (i + 1) * button_group_split_i + ((count + 1) - (i + 1)) * button_split_i + count * button_height_i;
			ToolButton* bt = this->buttons.at(count);
			bt->move(0, posy);
			bt->resize(this->width(), button_height_i);
			bt->raise();
			bt->show();
		}
	}
	for (int i = 0; i < this->buttonListPermanent.size(); i++) {
		int posy = this->height() - button_group_split_i - i * button_split_i - (i + 1) * button_height_i;
		PermanentToolButton* bt = this->permanentButtons.at(i);
		bt->move(0, posy);
		bt->resize(this->width(), button_height_i);
		bt->raise();
		bt->show();
	}
	for (int i = 0; i < this->buttonListBottom.size(); i++) {
		int posy = this->height() - button_group_split_i - (i + this->permanentButtons.size()) * button_split_i - (i + this->permanentButtons.size() + 1) * button_height_i;
		ToolButton* bt = this->bottomButtons.at(i);
		bt->move(0, posy);
		bt->resize(this->width(), button_height_i);
		bt->raise();
		bt->show();
	}
}

void ToolBar::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);

	QPainter painter(this);

	QColor color_background = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["tools"]("color-background")));
	painter.fillRect(0, 0, this->width(), this->height(), color_background);
}

void ToolBar::setLeft(bool left)
{
	this->left = left;
	for (auto bt : this->buttons) {
		bt->setLeft(left);
	}
	for (auto bt : this->bottomButtons) {
		bt->setLeft(left);
	}
	for (auto bt : this->permanentButtons) {
		bt->setLeft(left);
	}
	this->update();
}
