#include "CentralWidget.h"

CentralWidget::CentralWidget(QWidget *parent)
	: RefreshableWidget(parent)
{
	while (trackw == nullptr) {
		trackw = new(std::nothrow) TrackWidget(this);
		if (trackw == nullptr) {
			QMessageBox::Button result = QMessageBox::critical(this, "Infinity Studio 0", "Application can't alloc memory for object \"trackw\" on heap!\nPlease check your memory then retry or abort this application!", QMessageBox::Retry | QMessageBox::Button::Abort, QMessageBox::Abort);
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
	while (notew == nullptr) {
		notew = new(std::nothrow) NoteWidget(this);
		if (notew == nullptr) {
			QMessageBox::Button result = QMessageBox::critical(this, "Infinity Studio 0", "Application can't alloc memory for object \"notew\" on heap!\nPlease check your memory then retry or abort this application!", QMessageBox::Retry | QMessageBox::Button::Abort, QMessageBox::Abort);
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
	while (paramw == nullptr) {
		paramw = new(std::nothrow) ParamWidget(this);
		if (paramw == nullptr) {
			QMessageBox::Button result = QMessageBox::critical(this, "Infinity Studio 0", "Application can't alloc memory for object \"paramw\" on heap!\nPlease check your memory then retry or abort this application!", QMessageBox::Retry | QMessageBox::Button::Abort, QMessageBox::Abort);
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

	this->setMouseTracking(true);

	connect(this, &CentralWidget::centralFastReady, &(Infinity_Events::getClass()), &Infinity_Events::on_central_ready);
}

CentralWidget::~CentralWidget()
{
	paramw->deleteLater();
	paramw = nullptr;

	notew->deleteLater();
	notew = nullptr;

	trackw->deleteLater();
	trackw = nullptr;
}

void CentralWidget::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);
	QPainter painter(this);

	QSize screenSize = Infinity_global::getScreenSize();

	double split_height = 0.01;
	StyleContainer::getContainer().getStyleObject()["central"].Get("split-height", split_height);

	int split_height_i = (double)(screenSize.height() * split_height);

	QColor color_split = GetStyle::parseStringToColor(QString::fromStdString(StyleContainer::getContainer().getStyleObject()["central"]("color-split")));

	if (this->state == CentralState::AllState) {
		QRect sRect1(0, (double)(this->splitLine.at(0) * this->height()) - (double)(split_height_i / 2), this->width(), split_height_i);
		QRect sRect2(0, (double)(this->splitLine.at(1) * this->height()) - (double)(split_height_i / 2), this->width(), split_height_i);
		painter.fillRect(sRect1, color_split);
		painter.fillRect(sRect2, color_split);
	}
	else if (this->state == CentralState::TrackAndNoteState || this->state == CentralState::NoteAndParamState || this->state == CentralState::TrackAndParamState) {
		QRect sRect(0, (double)(this->splitLine.at(0) * this->height()) - (double)(split_height_i / 2), this->width(), split_height_i);
		painter.fillRect(sRect, color_split);
	}
	else {

	}
}

void CentralWidget::resizeAll()
{
	QSize screenSize = Infinity_global::getScreenSize();

	double split_height = 0.01;
	StyleContainer::getContainer().getStyleObject()["central"].Get("split-height", split_height);

	int split_height_i = (double)(screenSize.height() * split_height);

	int countFlag = 0;

	if (static_cast<CentralState>(this->state | CentralState::TrackViewState) == this->state) {
		if (this->state == CentralState::TrackViewState) {
			this->trackw->move(0, 0);
			this->trackw->resize(this->width(), this->height());
		}
		else {
			this->trackw->move(0, 0);
			this->trackw->resize(this->width(), (double)(this->splitLine.at(0) * this->height()) - (double)(split_height_i / 2));
		}
		this->trackw->show();
		this->trackw->raise();
		countFlag++;
	}
	else {
		this->trackw->hide();
	}
	if (static_cast<CentralState>(this->state | CentralState::NoteViewState) == this->state) {
		if (countFlag == 0) {
			this->notew->move(0, 0);
		}
		else {
			this->notew->move(0, (double)(this->splitLine.at(0) * this->height()) + (double)(split_height_i / 2));
		}
		if (static_cast<CentralState>(this->state | CentralState::ParamViewState) == this->state) {
			if (countFlag == 0) {
				this->notew->resize(this->width(), (double)(this->splitLine.at(0) * this->height()) - (double)(split_height_i / 2) - this->notew->geometry().y());
			}
			else {
				this->notew->resize(this->width(), (double)(this->splitLine.at(1) * this->height()) - (double)(split_height_i / 2) - this->notew->geometry().y());
			}
		}
		else {
			this->notew->resize(this->width(), this->height() - this->notew->geometry().y());
		}
		this->notew->show();
		this->notew->raise();
		countFlag++;
	}
	else {
		this->notew->hide();
	}
	if (static_cast<CentralState>(this->state | CentralState::ParamViewState) == this->state) {
		if (countFlag == 0) {
			this->paramw->move(0, 0);
		}
		else if(countFlag == 1) {
			this->paramw->move(0, (double)(this->splitLine.at(0) * this->height()) + (double)(split_height_i / 2));
		}
		else {
			this->paramw->move(0, (double)(this->splitLine.at(1) * this->height()) + (double)(split_height_i / 2));
		}
		this->paramw->resize(this->width(), this->height() - this->paramw->geometry().y());
		this->paramw->show();
		this->paramw->raise();
		countFlag++;
	}
	else {
		this->paramw->hide();
	}
}

void CentralWidget::on_viewShow(QString id, bool checked)
{
	QSize screenSize = Infinity_global::getScreenSize();

	double block_minimum_height = 0.1;
	StyleContainer::getContainer().getStyleObject()["central"].Get("block-minimum-height", block_minimum_height);

	int block_minimum_height_i = (double)(screenSize.height() * block_minimum_height);

	double block_minimum_height_d = (double)((double)block_minimum_height_i / (double)this->height());
	if (id == "button-track_view") {
		if (checked) {
			if (this->state == CentralState::NoteViewState || this->state == ParamViewState) {
				this->splitLine[0] = 0.5;
				this->trackw->setStateTop(true);
				this->notew->setStateTop(false);
				this->paramw->setStateTop(false);
			}
			else if (this->state == CentralState::NoteAndParamState) {
				this->splitLine[1] = 0.5 + 0.5 * this->splitLine.at(0);
				this->splitLine[1] = qMax(0.5 + block_minimum_height_d, this->splitLine.at(1));
				this->splitLine[1] = qMin(1 - block_minimum_height_d, this->splitLine.at(1));
				this->splitLine[0] = 0.5;
				this->trackw->setStateTop(true);
				this->notew->setStateTop(false);
				this->paramw->setStateTop(false);
			}
			else {
				this->trackw->setStateTop(true);
				this->notew->setStateTop(false);
				this->paramw->setStateTop(false);
				this->trackw->setStateBottom(true);
				this->notew->setStateBottom(false);
				this->paramw->setStateBottom(false);
			}
			this->state = static_cast<CentralState>(this->state | CentralState::TrackViewState);
		}
		else {
			if (this->state == CentralState::AllState) {
				this->splitLine[0] = (double)(this->splitLine.at(1) - this->splitLine.at(0)) / (double)(1 - this->splitLine.at(0));
				this->splitLine[0] = qMax(block_minimum_height_d, this->splitLine.at(0));
				this->splitLine[0] = qMin(1 - block_minimum_height_d, this->splitLine.at(0));
				this->splitLine[1] = 0;
				this->trackw->setStateTop(false);
				this->notew->setStateTop(true);
				this->paramw->setStateTop(false);
			}
			else if (this->state == CentralState::TrackAndNoteState || this->state == CentralState::TrackAndParamState) {
				this->splitLine[0] = 0;
				this->trackw->setStateTop(false);
				if (this->state == CentralState::TrackAndNoteState) {
					this->notew->setStateTop(true);
					this->paramw->setStateTop(false);
				}
				else if (this->state == CentralState::TrackAndParamState) {
					this->notew->setStateTop(false);
					this->paramw->setStateTop(true);
				}
			}
			else {
				this->trackw->setStateTop(false);
				this->notew->setStateTop(false);
				this->paramw->setStateTop(false);
				this->trackw->setStateBottom(false);
				this->notew->setStateBottom(false);
				this->paramw->setStateBottom(false);
			}
			this->state = static_cast<CentralState>(this->state & ~CentralState::TrackViewState);
		}
	}
	else if (id == "button-note_view") {
		if (checked) {
			if (this->state == CentralState::TrackViewState || this->state == ParamViewState) {
				this->splitLine[0] = 0.5;
				if (this->state == CentralState::TrackViewState) {
					this->trackw->setStateBottom(false);
					this->notew->setStateBottom(true);
					this->paramw->setStateBottom(false);
				}
				else if (this->state == CentralState::ParamViewState) {
					this->trackw->setStateTop(false);
					this->notew->setStateTop(true);
					this->paramw->setStateTop(false);
				}
			}
			else if (this->state == CentralState::TrackAndParamState) {
				this->splitLine[1] = this->splitLine.at(0) + 0.5 * (1 - this->splitLine.at(0));
				this->splitLine[1] = qMax(2 * block_minimum_height_d, this->splitLine.at(1));
				this->splitLine[1] = qMin(1 - block_minimum_height_d, this->splitLine.at(1));
				this->splitLine[0] = qMin(this->splitLine.at(0), this->splitLine.at(1) - block_minimum_height_d);
			}
			else {
				this->trackw->setStateTop(false);
				this->notew->setStateTop(true);
				this->paramw->setStateTop(false);
				this->trackw->setStateBottom(false);
				this->notew->setStateBottom(true);
				this->paramw->setStateBottom(false);
			}
			this->state = static_cast<CentralState>(this->state | CentralState::NoteViewState);
		}
		else {
			if (this->state == CentralState::AllState) {
				this->splitLine[1] = 0;
			}
			else if (this->state == CentralState::TrackAndNoteState || this->state == CentralState::NoteAndParamState) {
				this->splitLine[0] = 0;
				if (this->state == CentralState::TrackAndNoteState) {
					this->trackw->setStateBottom(true);
					this->notew->setStateBottom(false);
					this->paramw->setStateBottom(false);
				}
				else if (this->state == CentralState::NoteAndParamState) {
					this->trackw->setStateTop(false);
					this->notew->setStateTop(false);
					this->paramw->setStateTop(true);
				}
			}
			else {
				this->trackw->setStateTop(false);
				this->notew->setStateTop(false);
				this->paramw->setStateTop(false);
				this->trackw->setStateBottom(false);
				this->notew->setStateBottom(false);
				this->paramw->setStateBottom(false);
			}
			this->state = static_cast<CentralState>(this->state & ~CentralState::NoteViewState);
		}
	}
	else if (id == "button-parameter_view") {
		if (checked) {
			if (this->state == CentralState::TrackViewState || this->state == NoteViewState) {
				this->splitLine[0] = 0.5;
				this->trackw->setStateBottom(false);
				this->notew->setStateBottom(false);
				this->paramw->setStateBottom(true);
			}
			else if (this->state == CentralState::TrackAndNoteState) {
				this->splitLine[1] = this->splitLine.at(0) + 0.5 * (1 - this->splitLine.at(0));
				this->splitLine[1] = qMax(2 * block_minimum_height_d, this->splitLine.at(1));
				this->splitLine[1] = qMin(1 - block_minimum_height_d, this->splitLine.at(1));
				this->splitLine[0] = qMin(this->splitLine.at(0), this->splitLine.at(1) - block_minimum_height_d);
				this->trackw->setStateBottom(false);
				this->notew->setStateBottom(false);
				this->paramw->setStateBottom(true);
			}
			else {
				this->trackw->setStateTop(false);
				this->notew->setStateTop(false);
				this->paramw->setStateTop(true);
				this->trackw->setStateBottom(false);
				this->notew->setStateBottom(false);
				this->paramw->setStateBottom(true);
			}
			this->state = static_cast<CentralState>(this->state | CentralState::ParamViewState);
		}
		else {
			if (this->state == CentralState::AllState) {
				this->splitLine[1] = 0;
				this->trackw->setStateBottom(false);
				this->notew->setStateBottom(true);
				this->paramw->setStateBottom(false);
			}
			else if (this->state == CentralState::TrackAndParamState || this->state == CentralState::NoteAndParamState) {
				this->splitLine[0] = 0;
				if (this->state == CentralState::TrackAndParamState) {
					this->trackw->setStateBottom(true);
					this->notew->setStateBottom(false);
					this->paramw->setStateBottom(false);
				}
				else if (this->state == CentralState::NoteAndParamState) {
					this->trackw->setStateBottom(false);
					this->notew->setStateBottom(true);
					this->paramw->setStateBottom(false);
				}
			}
			else {
				this->trackw->setStateTop(false);
				this->notew->setStateTop(false);
				this->paramw->setStateTop(false);
				this->trackw->setStateBottom(false);
				this->notew->setStateBottom(false);
				this->paramw->setStateBottom(false);
			}
			this->state = static_cast<CentralState>(this->state & ~CentralState::ParamViewState);
		}
	}
	else {

	}
	emit this->centralFastReady(this->state != CentralState::OffState);
	this->resizeAll();
	this->update();
}

void CentralWidget::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::MouseButton::LeftButton) {
		QSize screenSize = Infinity_global::getScreenSize();

		double split_height = 0.01;
		StyleContainer::getContainer().getStyleObject()["central"].Get("split-height", split_height);

		int split_height_i = (double)(screenSize.height() * split_height);

		int py = event->pos().y();

		int s1 = this->splitLine[0] * this->height();
		int s2 = this->splitLine[1] * this->height();

		if (this->state == CentralState::AllState) {
			if (py >= s1 - split_height_i / 2 && py <= s1 + split_height_i / 2) {
				this->splitTemp = this->splitLine[0];
				this->pressedY = py;
				this->splitState = SplitState::Split0;
			}
			else if (py >= s2 - split_height_i / 2 && py <= s2 + split_height_i / 2) {
				this->splitTemp = this->splitLine[1];
				this->pressedY = py;
				this->splitState = SplitState::Split1;
			}
		}
		else if (this->state == CentralState::NoteAndParamState || this->state == CentralState::TrackAndNoteState || this->state == CentralState::TrackAndParamState) {
			if (py >= s1 - split_height_i / 2 && py <= s1 + split_height_i / 2) {
				this->splitTemp = this->splitLine[0];
				this->pressedY = py;
				this->splitState = SplitState::Split0;
			}
		}
	}
}

void CentralWidget::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::MouseButton::LeftButton) {
		if (this->splitState == SplitState::Split0 || this->splitState == SplitState::Split1) {
			QSize screenSize = Infinity_global::getScreenSize();

			double split_height = 0.01;
			StyleContainer::getContainer().getStyleObject()["central"].Get("split-height", split_height);

			int split_height_i = (double)(screenSize.height() * split_height);

			int py = event->pos().y();

			int s1 = this->splitLine[0] * this->height();
			int s2 = this->splitLine[1] * this->height();

			this->pressedY = 0;
			this->splitTemp = 0;
			this->splitState = SplitState::Normal;
			if (this->state == CentralState::AllState) {
				if ((py >= s1 - split_height_i / 2 && py <= s1 + split_height_i / 2) || (py >= s2 - split_height_i / 2 && py <= s2 + split_height_i / 2)) {
					this->setCursor(Qt::CursorShape::SizeVerCursor);
				}
				else {
					this->setCursor(Qt::CursorShape::ArrowCursor);
				}
			}
			else if (this->state == CentralState::NoteAndParamState || this->state == CentralState::TrackAndNoteState || this->state == CentralState::TrackAndParamState) {
				if (py >= s1 - split_height_i / 2 && py <= s1 + split_height_i / 2) {
					this->setCursor(Qt::CursorShape::SizeVerCursor);
				}
				else {
					this->setCursor(Qt::CursorShape::ArrowCursor);
				}
			}
			else {
				this->setCursor(Qt::CursorShape::ArrowCursor);
			}
			this->resizeAll();
		}
	}
}

void CentralWidget::mouseMoveEvent(QMouseEvent* event)
{
	QSize screenSize = Infinity_global::getScreenSize();

	double split_height = 0.01;
	StyleContainer::getContainer().getStyleObject()["central"].Get("split-height", split_height);

	int split_height_i = (double)(screenSize.height() * split_height);

	int py = event->pos().y();

	int s1 = this->splitLine[0] * this->height();
	int s2 = this->splitLine[1] * this->height();

	if (this->splitState == SplitState::Normal) {
		if (this->state == CentralState::AllState) {
			if ((py >= s1 - split_height_i / 2 && py <= s1 + split_height_i / 2) || (py >= s2 - split_height_i / 2 && py <= s2 + split_height_i / 2)) {
				this->setCursor(Qt::CursorShape::SizeVerCursor);
			}
			else {
				this->setCursor(Qt::CursorShape::ArrowCursor);
			}
		}
		else if (this->state == CentralState::NoteAndParamState || this->state == CentralState::TrackAndNoteState || this->state == CentralState::TrackAndParamState) {
			if (py >= s1 - split_height_i / 2 && py <= s1 + split_height_i / 2) {
				this->setCursor(Qt::CursorShape::SizeVerCursor);
			}
			else {
				this->setCursor(Qt::CursorShape::ArrowCursor);
			}
		}
		else {
			this->setCursor(Qt::CursorShape::ArrowCursor);
		}
	}
	else {
		this->setCursor(Qt::CursorShape::SizeVerCursor);

		double block_minimum_height = 0.01;
		StyleContainer::getContainer().getStyleObject()["central"].Get("block-minimum-height", block_minimum_height);

		double spTemp = this->splitTemp + ((double)(py - this->pressedY) / (double)this->height());

		if (this->splitState == SplitState::Split0) {
			if (this->state == CentralState::AllState) {
				spTemp = qMax(spTemp, block_minimum_height);
				spTemp = qMin(spTemp, this->splitLine[1] - block_minimum_height);
			}
			else if (this->state == CentralState::NoteAndParamState || this->state == CentralState::TrackAndNoteState || this->state == CentralState::TrackAndParamState) {
				spTemp = qMax(spTemp, block_minimum_height);
				spTemp = qMin(spTemp, 1 - block_minimum_height);
			}
			this->splitLine[0] = spTemp;
		}
		else if (this->splitState == SplitState::Split1) {
			if (this->state == CentralState::AllState) {
				spTemp = qMax(spTemp, this->splitLine[0] + block_minimum_height);
				spTemp = qMin(spTemp, 1 - block_minimum_height);
			}
			else if (this->state == CentralState::NoteAndParamState || this->state == CentralState::TrackAndNoteState || this->state == CentralState::TrackAndParamState) {
				spTemp = qMax(spTemp, block_minimum_height);
				spTemp = qMin(spTemp, 1 - block_minimum_height);
			}
			this->splitLine[1] = spTemp;
		}
		this->resizeAll();
	}
}

void CentralWidget::leaveEvent(QEvent* event)
{
	this->setCursor(Qt::CursorShape::ArrowCursor);
	if (this->splitState == SplitState::Split0 || this->splitState == SplitState::Split1) {
		this->pressedY = 0;
		this->splitTemp = 0;
		this->splitState = SplitState::Normal;
		this->resizeAll();
	}
}
