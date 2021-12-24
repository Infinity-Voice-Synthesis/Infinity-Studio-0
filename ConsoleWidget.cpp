#include "ConsoleWidget.h"

ConsoleWidget::ConsoleWidget(QWidget *parent)
	: RefreshableWidget(parent)
{
	while (scoller == nullptr) {
		scoller = new(std::nothrow) ConsoleScollBar(this);
		if (scoller == nullptr) {
			QMessageBox::Button result = QMessageBox::critical(this, "Infinity Studio 0", "Application can't alloc memory for object \"scoller\" on heap!\nPlease check your memory then retry or abort this application!", QMessageBox::Retry | QMessageBox::Button::Abort, QMessageBox::Abort);
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

	while (sThread == nullptr) {
		sThread = new(std::nothrow) StringQueueThread(this);
		if (sThread == nullptr) {
			QMessageBox::Button result = QMessageBox::critical(this, "Infinity Studio 0", "Application can't alloc memory for object \"sThread\" on heap!\nPlease check your memory then retry or abort this application!", QMessageBox::Retry | QMessageBox::Button::Abort, QMessageBox::Abort);
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

	sThread->strConnect([this](QStringList& lines)->void {
		for (auto& s : lines) {
			this->linesMutex.lock();
			this->lines.append(qMakePair(s, LineState::Output));
			this->linesMutex.unlock();
			this->haveChange = true;
		}
		});
	
	connect(this, &ConsoleWidget::command, &(Infinity_Events::getClass()), &Infinity_Events::on_console_command);
	connect(&(Infinity_Events::getClass()), &Infinity_Events::console_normal, sThread, &StringQueueThread::addMessage);
	//connect(&(Infinity_Events::getClass()), &Infinity_Events::console_normal, this, &ConsoleWidget::on_luaMessage);
	connect(&(Infinity_Events::getClass()), &Infinity_Events::console_error, this, &ConsoleWidget::on_luaError);
	connect(&(Infinity_Events::getClass()), &Infinity_Events::console_clear, this, &ConsoleWidget::on_luaClear);

	connect(scoller, &ConsoleScollBar::valueChanged, this, &ConsoleWidget::on_ScollValueChanged);
	connect(scoller, &ConsoleScollBar::wheelChanged, this, &ConsoleWidget::on_WheelChanged);

	sThread->start();

	scoller->show();
	this->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
	this->setCursor(Qt::CursorShape::BitmapCursor);
	this->setMouseTracking(true);

	connect(&curTimer, &QTimer::timeout, this, &ConsoleWidget::on_timerTimeOut);
	connect(&refreshTimer, &QTimer::timeout, this, &ConsoleWidget::on_refreshTimeOut);
}

ConsoleWidget::~ConsoleWidget()
{
	if (sThread->isRunning()) {
		sThread->requestInterruption();
		sThread->wait();
	}
	sThread->deleteLater();
	sThread = nullptr;

	scoller->deleteLater();
	scoller = nullptr;
}

void ConsoleWidget::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);
	QPainter painter(this);
	QSize screenSize = Infinity_global::getScreenSize();

	QColor color_background = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["console"]("color-background")));
	QColor color_normal = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["console"]("color-normal")));
	QColor color_message = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["console"]("color-message")));
	QColor color_error = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["console"]("color-error")));
	QColor color_cursor = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["console"]("color-cursor")));

	bool pic_background_diy = false;
	StyleContainer::getContainer().getStyleObject().Get("pic-background-diy", pic_background_diy);
	int line_size = 25;
	StyleContainer::getContainer().getStyleObject()["console"].Get("line-size", line_size);
	double scoll_width = 0.02;
	StyleContainer::getContainer().getStyleObject()["console"].Get("scoll-width", scoll_width);
	double font_height = 0.6;
	StyleContainer::getContainer().getStyleObject()["console"].Get("font-height", font_height);
	double margin = 0.02;
	StyleContainer::getContainer().getStyleObject()["console"].Get("margin", margin);
	double cursor_height = 0.8;
	StyleContainer::getContainer().getStyleObject()["console"].Get("cursor-height", cursor_height);

	int scoll_width_i = screenSize.width() * scoll_width;

	int windWidth = this->width() - scoll_width_i;

	int paintableWidth = windWidth * (1 - margin * 2);
	int paintMarginLeft = windWidth * margin;

	int lineHeight = this->height() / line_size;
	int fontPixelSize = lineHeight * font_height;

	QPen pen;
	pen.setWidth(1);
	pen.setColor(Qt::white);
	pen.setStyle(Qt::SolidLine);
	pen.setCapStyle(Qt::RoundCap);
	pen.setJoinStyle(Qt::RoundJoin);
	painter.setPen(pen);

	if (pic_background_diy) {
		double background_diy_transparency = 1;
		StyleContainer::getContainer().getStyleObject()["console"].Get("background-diy-transparency", background_diy_transparency);

		QColor color_background_hover;
		if ((color_background.red() + color_background.green() + color_background.blue()) > 255 * 1.5) {
			color_background_hover.setRgb(255, 255, 255, 255 * (1 - background_diy_transparency));
		}
		else {
			color_background_hover.setRgb(0, 0, 0, 255 * (1 - background_diy_transparency));
		}

		painter.fillRect(0, 0, this->width(), this->height(), color_background_hover);
	}
	else {
		painter.fillRect(0, 0, this->width(), this->height(), color_background);
	}

	QFont font;
	font.setPixelSize(fontPixelSize);
	painter.setFont(font);

	int fontTrueHeight = painter.fontMetrics().boundingRect('I').height();

	int lTop = this->currentTopLine;
	lTop = qMax(lTop, 0);
	int lBottom = lTop + line_size;

	for (int i = lTop; i < this->lineSplit.size() && i < lBottom; i++) {
		auto& p = this->lineSplit.at(i);

		QRect lineRect(paintMarginLeft, (i * lineHeight) - (lTop * lineHeight), paintableWidth, lineHeight);
		QPoint paintPoint(lineRect.left(), (double)(lineRect.top() + lineRect.bottom()) / (double)2 + (double)fontTrueHeight / (double)2);

		switch (p.second)
		{
		case LineState::Input:
			pen.setColor(color_normal);
			break;
		case LineState::Output:
			pen.setColor(color_message);
			break;
		case LineState::Error:
			pen.setColor(color_error);
			break;
		}

		painter.setPen(pen);

		painter.drawText(paintPoint, p.first);
	}

	QString strnow = this->strInput;
	strnow.prepend(this->inputMask);

	QStringList strNS;
	QString strtemp;
	while (strnow.length() > 0) {
		if (painter.fontMetrics().horizontalAdvance(strtemp + strnow.at(0)) > paintableWidth) {
			strNS.append(strtemp);
			strtemp.clear();
		}
		strtemp.append(strnow.at(0));
		strnow.remove(0, 1);
	}
	if (!strtemp.isEmpty()) {
		strNS.append(strtemp);
	}

	for (int i = 0; i < strNS.size(); i++) {
		QRect lineRect(paintMarginLeft, ((this->lineSplit.size() + i) * lineHeight) - (lTop * lineHeight), paintableWidth, lineHeight);
		QPoint paintPoint(lineRect.left(), (double)(lineRect.top() + lineRect.bottom()) / (double)2 + (double)fontTrueHeight / (double)2);

		pen.setColor(color_normal);
		painter.setPen(pen);

		painter.drawText(paintPoint, strNS.at(i));
	}

	if (this->showCursor) {
		int curCountTemp = this->cursorPlace + this->inputMask.size();
		int lineNum = 0;
		for (int i = 0; i < strNS.size(); i++) {
			if (curCountTemp <= strNS.at(i).length()) {
				break;
			}
			curCountTemp -= strNS.at(i).length();
			lineNum++;
		}

		pen.setColor(color_cursor);
		painter.setPen(pen);

		int curLinex = paintMarginLeft + painter.fontMetrics().horizontalAdvance(strNS.at(lineNum).left(curCountTemp));
		int curLineHC = ((this->lineSplit.size() + lineNum) * lineHeight) - (static_cast<long long>(lTop) * lineHeight) + lineHeight / 2;
		QLine curLine(curLinex, curLineHC - (lineHeight * cursor_height) / 2, curLinex, curLineHC + (lineHeight * cursor_height) / 2);
		painter.drawLine(curLine);
	}

	QPixmap curPix(2, 2);
	curPix.fill(color_cursor);
	QCursor curs(curPix);
	this->setCursor(curs);
}

void ConsoleWidget::keyPressEvent(QKeyEvent* event)
{
	if (this->isHidden()) {
		return;
	}

	double cursor_speed = 2;
	StyleContainer::getContainer().getStyleObject()["console"].Get("cursor-speed", cursor_speed);

	if (event->modifiers() == Qt::KeyboardModifier::NoModifier) {
		Qt::Key key = static_cast<Qt::Key>(event->key());
		if (key >= Qt::Key::Key_A && key <= Qt::Key::Key_Z) {
			this->strInput.insert(this->cursorPlace, QChar('a' + key - Qt::Key::Key_A));
			this->cursorPlace++;
			this->currentTemp = -1;
		}
		else if (key >= Qt::Key::Key_0 && key <= Qt::Key::Key_9) {
			this->strInput.insert(this->cursorPlace, QChar('0' + key - Qt::Key::Key_0));
			this->cursorPlace++;
			this->currentTemp = -1;
		}
		else {
			switch (key)
			{
			case Qt::Key_Up:
				if (this->currentTemp == -1) {
					if (this->commandTemp.size() > 0) {
						this->currentTemp = this->commandTemp.size() - 1;
						this->eLineTemp = this->strInput;
						this->strInput = this->commandTemp.at(this->currentTemp);
						this->cursorPlace = this->strInput.size();
					}
				}
				else {
					if (this->currentTemp > 0) {
						this->currentTemp--;
						this->strInput = this->commandTemp.at(this->currentTemp);
						this->cursorPlace = this->strInput.size();
					}
				}
				break;
			case Qt::Key_Down:
				if (this->currentTemp != -1) {
					if (this->currentTemp < this->commandTemp.size() - 1) {
						this->currentTemp++;
						this->strInput = this->commandTemp.at(this->currentTemp);
						this->cursorPlace = this->strInput.size();
					}
					else {
						this->currentTemp = -1;
						this->strInput = this->eLineTemp;
						this->cursorPlace = this->strInput.size();
					}
				}
				break;
			case Qt::Key_Left:
				if (this->cursorPlace > 0) {
					this->cursorPlace--;
				}
				break;
			case Qt::Key_Right:
				if (this->cursorPlace < this->strInput.size()) {
					this->cursorPlace++;
				}
				break;
			case Qt::Key_Space:
				this->strInput.insert(this->cursorPlace, QChar(' '));
				this->cursorPlace++;
				this->currentTemp = -1;
				break;
			case Qt::Key_Tab:
				this->strInput.insert(this->cursorPlace, QChar('\t'));
				this->cursorPlace++;
				this->currentTemp = -1;
				break;
			case Qt::Key_Backspace:
				if (!this->strInput.isEmpty() && this->cursorPlace > 0) {
					if (this->strInput.size() > this->cursorPlace) {
						if (this->strInput.at(static_cast<qsizetype>(this->cursorPlace) - 1) == '(' && this->strInput.at(this->cursorPlace) == ')') {
							this->strInput.remove(static_cast<qsizetype>(this->cursorPlace) - 1, 2);
						}
						else if (this->strInput.at(static_cast<qsizetype>(this->cursorPlace) - 1) == '[' && this->strInput.at(this->cursorPlace) == ']') {
							this->strInput.remove(static_cast<qsizetype>(this->cursorPlace) - 1, 2);
						}
						else if (this->strInput.at(static_cast<qsizetype>(this->cursorPlace) - 1) == '{' && this->strInput.at(this->cursorPlace) == '}') {
							this->strInput.remove(static_cast<qsizetype>(this->cursorPlace) - 1, 2);
						}
						else if (this->strInput.at(static_cast<qsizetype>(this->cursorPlace) - 1) == '\"' && this->strInput.at(this->cursorPlace) == '\"') {
							this->strInput.remove(static_cast<qsizetype>(this->cursorPlace) - 1, 2);
						}
						else if (this->strInput.at(static_cast<qsizetype>(this->cursorPlace) - 1) == '\'' && this->strInput.at(this->cursorPlace) == '\'') {
							this->strInput.remove(static_cast<qsizetype>(this->cursorPlace) - 1, 2);
						}
						else {
							this->strInput.remove(static_cast<qsizetype>(this->cursorPlace) - 1, 1);
						}
					}
					else {
						this->strInput.remove(static_cast<qsizetype>(this->cursorPlace) - 1, 1);
					}
					this->cursorPlace--;
					this->currentTemp = -1;
				}
				break;
			case Qt::Key_Return:
				if (!this->strInput.isEmpty()) {
					if (this->commandTemp.isEmpty() || (this->commandTemp.last() != this->strInput)) {
						this->commandTemp.append(this->strInput);
					}
				}
				this->doString(this->strInput);
				this->currentTemp = -1;
				break;
			case Qt::Key_QuoteLeft:
				this->strInput.insert(this->cursorPlace, QChar('`'));
				this->cursorPlace++;
				this->currentTemp = -1;
				break;
			case Qt::Key_Apostrophe:
				this->strInput.insert(this->cursorPlace, QString("\'\'"));
				this->cursorPlace++;
				this->currentTemp = -1;
				break;
			case Qt::Key_Comma:
				this->strInput.insert(this->cursorPlace, QChar(','));
				this->cursorPlace++;
				this->currentTemp = -1;
				break;
			case Qt::Key_Minus:
				this->strInput.insert(this->cursorPlace, QChar('-'));
				this->cursorPlace++;
				this->currentTemp = -1;
				break;
			case Qt::Key_Period:
				this->strInput.insert(this->cursorPlace, QChar('.'));
				this->cursorPlace++;
				this->currentTemp = -1;
				break;
			case Qt::Key_Slash:
				this->strInput.insert(this->cursorPlace, QChar('/'));
				this->cursorPlace++;
				this->currentTemp = -1;
				break;
			case Qt::Key_Semicolon:
				this->strInput.insert(this->cursorPlace, QChar(';'));
				this->cursorPlace++;
				this->currentTemp = -1;
				break;
			case Qt::Key_Equal:
				this->strInput.insert(this->cursorPlace, QChar('='));
				this->cursorPlace++;
				this->currentTemp = -1;
				break;
			case Qt::Key_BracketLeft:
				this->strInput.insert(this->cursorPlace, QString("[]"));
				this->cursorPlace++;
				this->currentTemp = -1;
				break;
			case Qt::Key_Backslash:
				this->strInput.insert(this->cursorPlace, QChar('\\'));
				this->cursorPlace++;
				this->currentTemp = -1;
				break;
			case Qt::Key_BracketRight:
				if (!((this->cursorPlace < this->strInput.size()) && (this->strInput.at(this->cursorPlace) == QChar(']')))) {
					this->strInput.insert(this->cursorPlace, QChar(']'));
				}
				this->cursorPlace++;
				this->currentTemp = -1;
				break;
			default:
				break;
			}
		}
		this->goDown();
		this->curTimer.stop();
		this->showCursor = true;
		this->curTimer.start(1000 / cursor_speed);
		this->update();
	}
	else if (event->modifiers() == Qt::KeyboardModifier::ShiftModifier) {
		Qt::Key key = static_cast<Qt::Key>(event->key());
		if (key >= Qt::Key::Key_A && key <= Qt::Key::Key_Z) {
			this->strInput.insert(this->cursorPlace, QChar('A' + key - Qt::Key::Key_A));
			this->cursorPlace++;
		}
		else {
			switch (key)
			{
			case Qt::Key_Exclam:
				this->strInput.insert(this->cursorPlace, QChar('!'));
				this->cursorPlace++;
				this->currentTemp = -1;
				break;
			case Qt::Key_At:
				this->strInput.insert(this->cursorPlace, QChar('@'));
				this->cursorPlace++;
				this->currentTemp = -1;
				break;
			case Qt::Key_NumberSign:
				this->strInput.insert(this->cursorPlace, QChar('#'));
				this->cursorPlace++;
				this->currentTemp = -1;
				break;
			case Qt::Key_Dollar:
				this->strInput.insert(this->cursorPlace, QChar('$'));
				this->cursorPlace++;
				this->currentTemp = -1;
				break;
			case Qt::Key_Percent:
				this->strInput.insert(this->cursorPlace, QChar('%'));
				this->cursorPlace++;
				this->currentTemp = -1;
				break;
			case Qt::Key_AsciiCircum:
				this->strInput.insert(this->cursorPlace, QChar('^'));
				this->cursorPlace++;
				this->currentTemp = -1;
				break;
			case Qt::Key_Ampersand:
				this->strInput.insert(this->cursorPlace, QChar('&'));
				this->cursorPlace++;
				this->currentTemp = -1;
				break;
			case Qt::Key_Asterisk:
				this->strInput.insert(this->cursorPlace, QChar('*'));
				this->cursorPlace++;
				this->currentTemp = -1;
				break;
			case Qt::Key_ParenLeft:
				this->strInput.insert(this->cursorPlace, QString("()"));
				this->cursorPlace++;
				this->currentTemp = -1;
				break;
			case Qt::Key_ParenRight:
				if (!((this->cursorPlace < this->strInput.size()) && (this->strInput.at(this->cursorPlace) == QChar(')')))) {
					this->strInput.insert(this->cursorPlace, QChar(')'));
				}
				this->cursorPlace++;
				this->currentTemp = -1;
				break;
			case Qt::Key_AsciiTilde:
				this->strInput.insert(this->cursorPlace, QChar('~'));
				this->cursorPlace++;
				this->currentTemp = -1;
				break;
			case Qt::Key_QuoteDbl:
				this->strInput.insert(this->cursorPlace, QString("\"\""));
				this->cursorPlace++;
				this->currentTemp = -1;
				break;
			case Qt::Key_Less:
				this->strInput.insert(this->cursorPlace, QChar('<'));
				this->cursorPlace++;
				this->currentTemp = -1;
				break;
			case Qt::Key_Underscore:
				this->strInput.insert(this->cursorPlace, QChar('_'));
				this->cursorPlace++;
				this->currentTemp = -1;
				break;
			case Qt::Key_Greater:
				if (!((this->cursorPlace < this->strInput.size()) && (this->strInput.at(this->cursorPlace) == QChar('>')))) {
					this->strInput.insert(this->cursorPlace, QChar('>'));
				}
				this->cursorPlace++;
				this->currentTemp = -1;
				break;
			case Qt::Key_Question:
				this->strInput.insert(this->cursorPlace, QChar('?'));
				this->cursorPlace++;
				this->currentTemp = -1;
				break;
			case Qt::Key_Colon:
				this->strInput.insert(this->cursorPlace, QChar(':'));
				this->cursorPlace++;
				this->currentTemp = -1;
				break;
			case Qt::Key_Plus:
				this->strInput.insert(this->cursorPlace, QChar('+'));
				this->cursorPlace++;
				this->currentTemp = -1;
				break;
			case Qt::Key_BraceLeft:
				this->strInput.insert(this->cursorPlace, QString("{}"));
				this->cursorPlace++;
				this->currentTemp = -1;
				break;
			case Qt::Key_Bar:
				this->strInput.insert(this->cursorPlace, QChar('|'));
				this->cursorPlace++;
				this->currentTemp = -1;
				break;
			case Qt::Key_BraceRight:
				if (!((this->cursorPlace < this->strInput.size()) && (this->strInput.at(this->cursorPlace) == QChar('}')))) {
					this->strInput.insert(this->cursorPlace, QChar('}'));
				}
				this->cursorPlace++;
				this->currentTemp = -1;
				break;
			default:
				break;
			}
		}
		this->goDown();
		this->curTimer.stop();
		this->showCursor = true;
		this->curTimer.start(1000 / cursor_speed);
		this->update();
	}
}

void ConsoleWidget::resizeAll()
{
	QSize screenSize = Infinity_global::getScreenSize();

	double scoll_width = 0.02;
	StyleContainer::getContainer().getStyleObject()["console"].Get("scoll-width", scoll_width);

	double fps = 10, cursor_speed = 2;
	StyleContainer::getContainer().getStyleObject()["console"].Get("fps", fps);
	StyleContainer::getContainer().getStyleObject()["console"].Get("cursor-speed", cursor_speed);

	int scoll_width_i = screenSize.width() * scoll_width;

	this->scoller->move(this->width() - scoll_width_i, 0);
	this->scoller->resize(scoll_width_i, this->height());
	this->scoller->raise();
	this->scoller->show();

	if (this->curTimer.isActive()) {
		this->curTimer.stop();
		this->curTimer.start(1000 / cursor_speed);
	}
	if (this->refreshTimer.isActive()) {
		this->refreshTimer.stop();
		this->refreshTimer.start(1000 / fps);
	}

	this->reSplit();
}

void ConsoleWidget::on_ScollValueChanged(double sp, double ep)
{
	Q_UNUSED(ep);
	int line_size = 25;
	StyleContainer::getContainer().getStyleObject()["console"].Get("line-size", line_size);

	int lTop = qRound((double)(this->lineSplit.size() + line_size) * sp);
	lTop = qMax(lTop, 0);

	this->currentTopLine = lTop;

	this->update();
}

void ConsoleWidget::doString(QString command)
{
	this->strInput.clear();
	this->cursorPlace = 0;
	this->linesMutex.lock();
	this->lines.append(qMakePair(command, LineState::Input));
	this->linesMutex.unlock();
	emit this->command(command);
	this->haveChange = true;
}

void ConsoleWidget::on_luaMessage(QString message)
{
	QStringList messList = message.split('\n', Qt::KeepEmptyParts);
	for (auto& s : messList) {
		this->linesMutex.lock();
		this->lines.append(qMakePair(s, LineState::Output));
		this->linesMutex.unlock();
	}
	this->haveChange = true;
}

void ConsoleWidget::on_luaError(QString message)
{
	QStringList messList = message.split('\n', Qt::KeepEmptyParts);
	for (auto& s : messList) {
		this->linesMutex.lock();
		this->lines.append(qMakePair(s, LineState::Error));
		this->linesMutex.unlock();
	}
	this->haveChange = true;
}

void ConsoleWidget::on_luaClear()
{
	this->sThread->clear();

	this->linesMutex.lock();
	this->lines.clear();
	this->linesMutex.unlock();

	this->lineSplit.clear();
	this->scoller->setTips({});
	QPair<double, double> value = this->scoller->setValue(0, 1);
	this->currentTopLine = 0;
	
	this->update();
}

void ConsoleWidget::reSplit()
{
	QSize screenSize = Infinity_global::getScreenSize();

	int line_size = 25;
	StyleContainer::getContainer().getStyleObject()["console"].Get("line-size", line_size);
	double scoll_width = 0.02;
	StyleContainer::getContainer().getStyleObject()["console"].Get("scoll-width", scoll_width);
	double font_height = 0.6;
	StyleContainer::getContainer().getStyleObject()["console"].Get("font-height", font_height);
	double margin = 0.02;
	StyleContainer::getContainer().getStyleObject()["console"].Get("margin", margin);

	int scoll_width_i = screenSize.width() * scoll_width;

	int windWidth = this->width() - scoll_width_i;

	int paintableWidth = windWidth * (1 - margin * 2);

	int lineHeight = this->height() / line_size;
	int fontPixelSize = lineHeight * font_height;

	QFont font;
	font.setPixelSize(fontPixelSize);
	QFontMetrics fontM(font);
	
	this->linesMutex.lock();
	this->lineSplit.clear();
	
	for (auto& p : this->lines) {
		LineState state = p.second;
		QString str = p.first;
		
		if (state == LineState::Input) {
			str.prepend(this->inputMask);
		}
		
		QString temp;
		while (str.length() > 0) {
			if (fontM.horizontalAdvance(temp + str.at(0)) > paintableWidth) {
				this->lineSplit.append(qMakePair(temp, state));
				temp.clear();
			}
			temp.append(str.at(0));
			str.remove(0, 1);
		}
		if (!temp.isEmpty()) {
			this->lineSplit.append(qMakePair(temp, state));
		}
	}
	this->linesMutex.unlock();
}

void ConsoleWidget::on_timerTimeOut()
{
	this->showCursor = !this->showCursor;
	this->update();
}

void ConsoleWidget::goDown()
{
	int line_size = 25;
	StyleContainer::getContainer().getStyleObject()["console"].Get("line-size", line_size);

	int lTop = this->currentTopLine;
	lTop = qMax(lTop, 0);
	int lBottom = lTop + line_size;

	if (static_cast<long long>(lBottom) - 1 < this->lineSplit.size()) {
		lTop = this->lineSplit.size();
		lBottom = lTop + line_size;

		this->currentTopLine = lTop;
		QPair<double, double> value = this->scoller->setValue((double)lTop / (double)(this->lineSplit.size() + line_size), (double)lBottom / (double)(this->lineSplit.size() + line_size));

		this->update();
	}
}

void ConsoleWidget::wheelEvent(QWheelEvent* event)
{
	this->on_WheelChanged(event->angleDelta().y());
}

void ConsoleWidget::on_WheelChanged(int delta)
{
	int line_size = 25;
	StyleContainer::getContainer().getStyleObject()["console"].Get("line-size", line_size);

	int lTop = this->currentTopLine;
	
	lTop -= delta / 50;

	lTop = qMax(lTop, 0);
	lTop = qMin(lTop, this->lineSplit.size());
	int lBottom = lTop + line_size;

	this->currentTopLine = lTop;
	QPair<double, double> value = this->scoller->setValue((double)lTop / (double)(this->lineSplit.size() + line_size), (double)lBottom / (double)(this->lineSplit.size() + line_size));

	this->update();
}

void ConsoleWidget::on_refreshTimeOut()
{
	if (this->haveChange) {
		this->haveChange = false;

		this->reSplit();

		int line_size = 25;
		StyleContainer::getContainer().getStyleObject()["console"].Get("line-size", line_size);

		QVector<double> tipPlace;
		for (int i = 0; i < this->lineSplit.size(); i++) {
			if (this->lineSplit.at(i).second == LineState::Error) {
				tipPlace.append((double)i / (double)(this->lineSplit.size() + line_size));
			}
		}
		this->scoller->setTips(tipPlace);

		QPair<double, double> value = this->scoller->getValue();
		int lTop = (this->lineSplit.size() + line_size) * value.first;
		lTop = qMax(lTop, 0);
		int lBottom = lTop + line_size;

		this->currentTopLine = lTop;
		value = this->scoller->setValue((double)lTop / (double)(this->lineSplit.size() + line_size), (double)lBottom / (double)(this->lineSplit.size() + line_size));
		this->update();
	}
}

void ConsoleWidget::showEvent(QShowEvent* event)
{
	Q_UNUSED(event);
	double fps = 10, cursor_speed = 2;
	StyleContainer::getContainer().getStyleObject()["console"].Get("fps", fps);
	StyleContainer::getContainer().getStyleObject()["console"].Get("cursor-speed", cursor_speed);

	this->curTimer.start(1000 / cursor_speed);
	this->refreshTimer.start(1000 / fps);
}

void ConsoleWidget::hideEvent(QHideEvent* event)
{
	Q_UNUSED(event);
	this->curTimer.stop();
	this->refreshTimer.stop();
}

void ConsoleWidget::closeEvent(QCloseEvent* event)
{
	Q_UNUSED(event);
	this->curTimer.stop();
	this->refreshTimer.stop();
}
