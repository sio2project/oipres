#include "View.h"

const QString menuViewString = QString::fromUtf8("Sterowanie");
const QString menuViewNextReportString = QString::fromUtf8("Następny raport");
const QString menuViewPreviousReportString = QString::fromUtf8("Poprzedni raport");
const QString menuViewNextTaskString = QString::fromUtf8("Następne zadanie");
const QString menuViewPreviousTaskString = QString::fromUtf8("Poprzednie zadanie");
const QString menuViewNextStepString = QString::fromUtf8("&Następny krok");
const QString menuViewPreviousStepString = QString::fromUtf8("&Poprzedni krok");

const QString menuViewShowAllTestsString = QString::fromUtf8("Pokaż wszystko");
const QString menuViewHideAllTestsString = QString::fromUtf8("Schowaj wszystko");

const QString menuViewSpeedUpString = QString::fromUtf8("Przyspiesz");
const QString menuViewSlowDownString = QString::fromUtf8("Zwolnij");

const QString menuViewPauseString = QString::fromUtf8("Zatrzymaj");

const QString viewEmptyPresentationString = QString::fromUtf8("Prezentacja jest pusta ;_;");

const qreal viewBorderWidth = 10;
const qreal titleHeight = 100;
const qreal taskResultHeight = 60;
const qreal taskResultWidth = 120;

const qreal viewMinSpeedFactor = 0;
const qreal viewMaxSpeedFactor = 3;
const qreal viewSpeedDelta = 0.03;

const qreal speedometerWidth = 50;
const qreal speedometerHeight = 2;


View::View(QWidget *parent) : QWidget(parent),
	activeViewTable(nullptr),
	presentation(nullptr),
	reportIterator(),
	taskResultIterator(),
	viewMenu(nullptr),
	tables(),
	taskResultViews(),
	speedFactor(1),
	timer(new QTimer(this))
{
	this->title = new QLabel(this);
	this->title->setGeometry(0, 0, this->width(), titleHeight);
	this->title->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
	QFont bigFont = QApplication::font();
	bigFont.setPointSize(40);
	this->title->setFont(bigFont);

	this->timer->setSingleShot(true);
	connect(this->timer, SIGNAL(timeout()), this, SLOT(nextStep()));

	this->setStyleSheet("background-color: #f2f5a9;");
	this->setAutoFillBackground(true);
}

void View::clear()
{
	this->presentation = nullptr;
	this->title->setText("");
	this->activeViewTable = nullptr;
	this->reportIterator = QListConstPointerIterator<Report>();
	this->taskResultIterator = QListConstPointerIterator<TaskResult>();

	for(ViewTable *viewTable : this->tables)
		delete viewTable;
	this->tables.clear();

	for(ViewTaskResult *viewTaskResult : this->taskResultViews)
		delete viewTaskResult;
	this->taskResultViews.clear();

	this->speedFactor = 1;
	this->timer->stop();

	this->disableMenu();
}

void View::setToBeginning()
{
	if(this->presentation == nullptr)
		return;
	this->initReportIterator();
	this->initTaskResultIterator();
	this->setActiveViewTable((*this->taskResultIterator)->getTask());
	this->updateTaskResultViews();
	this->pause();
	this->updateSpeed();
	this->update();
}

void View::setPresentation(const Presentation *newPresentation)
{
	if(this->presentation != nullptr)
		this->clear();
	
	this->presentation = newPresentation;

	if(this->presentation == nullptr)
		return;
	
	if(!this->presentation->isVisible())
		return this->setPresentation(nullptr);

	this->enableMenu();

	for(const Task *task : this->presentation->getTasks())
	{
		if(!task->isVisible())
			continue;

		if(task->getTests() != nullptr)
		{
			ViewTable *viewTable = new ViewTable(task, this);
			this->tables.push_back(viewTable);

			connect(viewTable, SIGNAL(reachedEnd()), this, SLOT(reachedEndOfTask()));
			connect(viewTable, SIGNAL(leftEnd()), this, SLOT(leftEndOfTask()));

			ViewTaskResult *viewTaskResult = new ViewTaskResult(task, this);
			viewTaskResult->resize(taskResultWidth, taskResultHeight);
			this->taskResultViews.push_back(viewTaskResult);
			viewTaskResult->show();
		}
	}

	this->setToBeginning();
}

void View::configureViewMenu(QMenu *menu)
{
	this->viewMenu = menu;

	menu->setTitle(menuViewString);

	QAction *nextStepAction = new QAction(menuViewNextStepString ,menu);
	nextStepAction->setShortcut(Qt::Key_Right);
	connect(nextStepAction, SIGNAL(triggered()), this, SLOT(nextStep()));

	this->addAction(nextStepAction);
	menu->addAction(nextStepAction);

	QAction *previousStepAction = new QAction(menuViewPreviousStepString ,menu);
	previousStepAction->setShortcut(Qt::Key_Left);
	connect(previousStepAction, SIGNAL(triggered()), this, SLOT(previousStep()));

	this->addAction(previousStepAction);
	menu->addAction(previousStepAction);

	QAction *nextTaskAction = new QAction(menuViewNextTaskString ,menu);
	nextTaskAction->setShortcut(Qt::Key_K);
	connect(nextTaskAction, SIGNAL(triggered()), this, SLOT(nextTask()));

	this->addAction(nextTaskAction);
	menu->addAction(nextTaskAction);

	QAction *previousTaskAction = new QAction(menuViewPreviousTaskString ,menu);
	previousTaskAction->setShortcut(Qt::Key_J);
	connect(previousTaskAction, SIGNAL(triggered()), this, SLOT(previousTask()));

	this->addAction(previousTaskAction);
	menu->addAction(previousTaskAction);
	
	QAction *nextReportAction = new QAction(menuViewNextReportString, menu);
	nextReportAction->setShortcut(Qt::Key_L);
	connect(nextReportAction, SIGNAL(triggered()), this, SLOT(nextReport()));

	this->addAction(nextReportAction);
	menu->addAction(nextReportAction);

	QAction *previousReportAction = new QAction(menuViewPreviousReportString ,menu);
	previousReportAction->setShortcut(Qt::Key_H);
	connect(previousReportAction, SIGNAL(triggered()), this, SLOT(previousReport()));

	this->addAction(previousReportAction);
	menu->addAction(previousReportAction);

	QAction *showAllAction = new QAction(menuViewShowAllTestsString, menu);
	showAllAction->setShortcut(Qt::Key_Down);
	connect(showAllAction, SIGNAL(triggered()), this, SLOT(makeAllSteps()));

	this->addAction(showAllAction);
	menu->addAction(showAllAction);

	QAction *hideAllAction = new QAction(menuViewHideAllTestsString, menu);
	hideAllAction->setShortcut(Qt::Key_Up);
	connect(hideAllAction, SIGNAL(triggered()), this, SLOT(undoAllSteps()));

	this->addAction(hideAllAction);
	menu->addAction(hideAllAction);

	QAction *pauseAction = new QAction(menuViewPauseString, menu);
	pauseAction->setShortcut(Qt::Key_P);
	connect(pauseAction, SIGNAL(triggered()), this, SLOT(pause()));

	this->addAction(pauseAction);
	menu->addAction(pauseAction);

	QAction *speedUpAction = new QAction(menuViewSpeedUpString, menu);
	speedUpAction->setShortcut(Qt::Key_Plus);
	connect(speedUpAction, SIGNAL(triggered()), this, SLOT(speedUp()));

	this->addAction(speedUpAction);
	menu->addAction(speedUpAction);

	QAction *slowDownAction = new QAction(menuViewSlowDownString, menu);
	slowDownAction->setShortcut(Qt::Key_Minus);
	connect(slowDownAction, SIGNAL(triggered()), this, SLOT(slowDown()));

	this->addAction(slowDownAction);
	menu->addAction(slowDownAction);

	this->disableMenu();
}

void View::enableMenu()
{
	if(this->presentation == nullptr)
		return;
	if(this->viewMenu == nullptr)
		return;
	for(QAction *action : this->viewMenu->actions())
		action->setEnabled(true);
}

void View::disableMenu()
{
	if(this->viewMenu == nullptr)
		return;
	for(QAction *action : this->viewMenu->actions())
		action->setDisabled(true);
}

void View::updateTable()
{
	const TaskResult *taskResult = *this->taskResultIterator;

	if(this->activeViewTable == nullptr)
		return;

	this->activeViewTable->show();
	this->activeViewTable->setResult(taskResult);

	const Report *report = *reportIterator;
	if(report != nullptr)
		this->title->setText(report->getContestant()->getName());

	this->update();
}


void View::updateTaskResultViews()
{
	for(ViewTaskResult* viewTaskResult : this->taskResultViews)
		viewTaskResult->setResult(nullptr);
	
	const Report *report = *this->reportIterator;

	for(ViewTaskResult *viewTaskResult : this->taskResultViews)
		viewTaskResult->hide();
		
	if(report != nullptr)
	{
		for(const TaskResult *taskResult : report->getTaskResults())
			this->showTaskResultView(taskResult->getTask());
	}
	
	QListConstPointerIterator<TaskResult> tmpIterator = this->taskResultIterator;

	if(this->activeViewTable != nullptr)
	{
		if(this->activeViewTable->isEnd())
			this->setTaskResultInTaskResultView(*tmpIterator, (*tmpIterator)->getTask());
	}
	
	while(tmpIterator--)
	{
		this->setTaskResultInTaskResultView(*tmpIterator, (*tmpIterator)->getTask());
	}

	this->placeInnerWidgets(this->size());
}


const Presentation *View::getPresentation() const
{
	return this->presentation;
}

void View::paintEvent(QPaintEvent *paintEvent)
{
	QStyleOption option;
	option.init(this);
	QPainter painter(this);
	this->style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);

	if(this->presentation == nullptr)
		this->style()->drawItemText(&painter, this->rect(), Qt::AlignHCenter | Qt::AlignVCenter, QPalette(), true, viewEmptyPresentationString);
	
	painter.drawRect(QRect(this->width() - speedometerWidth - viewBorderWidth, this->height() - speedometerHeight - viewBorderWidth, speedometerWidth, speedometerHeight));
	painter.setBrush(QBrush(QColor(0, 0, 0)));
	qreal coloredWidth = ((this->speedFactor - viewMinSpeedFactor) / (viewMaxSpeedFactor - viewMinSpeedFactor)) * speedometerWidth;
	painter.drawRect(QRect(this->width() - speedometerWidth - viewBorderWidth, this->height() - speedometerHeight - viewBorderWidth, coloredWidth, speedometerHeight));
}

void View::resizeEvent(QResizeEvent *resizeEvent)
{
	this->placeInnerWidgets(resizeEvent->size());
}


qreal View::getSpeed() const
{
	return this->presentation->getSpeed() * this->speedFactor;
}

qreal View::getTimeToSeeComments() const
{
	return this->presentation->getTimeToSeeComments() * this->speedFactor;
}

qreal View::getTimeToSeeTests() const
{
	return this->presentation->getTimeToSeeTests() * this->speedFactor;
}



bool View::nextStep()
{
	if(this->presentation == nullptr)
		return true;

	this->timer->stop();
	if(this->activeViewTable == nullptr)
		return this->nextTask();

	if(this->activeViewTable->nextStep())
		return this->nextTask();

	return false;
}

bool View::previousStep()
{
	if(this->presentation == nullptr)
		return true;

	this->timer->stop();
	if(this->activeViewTable == nullptr)
		return this->previousTask();
	
	if(this->activeViewTable->previousStep())
	{
		if(this->previousTask())
			return true;
		this->makeAllSteps();
	}
	
	return false;
}

bool View::nextTask()
{
	if(this->presentation == nullptr)
		return true;

	this->timer->stop();
	if(this->nextTaskResultIterator())
	{
		this->setActiveViewTable((*this->taskResultIterator)->getTask());
		this->updateTaskResultViews();
		return false;
	}
	this->previousTaskResultIterator();
	return this->nextReport();
}

bool View::previousTask()
{
	if(this->presentation == nullptr)
		return true;

	this->timer->stop();
	if(this->previousTaskResultIterator())
	{
		this->setActiveViewTable((*this->taskResultIterator)->getTask());
		this->updateTaskResultViews();
		return false;
	}
	return this->previousReport();
}

bool View::nextReport()
{
	if(this->presentation == nullptr)
		return true;

	this->timer->stop();
	if(this->nextReportIterator())
	{
		this->initTaskResultIterator();
		this->setActiveViewTable((*this->taskResultIterator)->getTask());
		this->updateTaskResultViews();
		return false;
	}
	this->previousReportIterator();
	this->initTaskResultIterator();
	this->lastTaskResultIterator();
	this->updateTaskResultViews();
	return true;
}

bool View::previousReport()
{
	if(this->presentation == nullptr)
		return true;

	this->timer->stop();
	if(this->previousReportIterator())
	{
		this->initTaskResultIterator();
		this->lastTaskResultIterator();
		this->setActiveViewTable((*this->taskResultIterator)->getTask());
		this->updateTaskResultViews();
		return false;
	}
	this->initTaskResultIterator();
	this->updateTaskResultViews();
	return true;
}


void View::makeAllSteps()
{
	if(this->presentation == nullptr)
		return;

	if(this->activeViewTable != nullptr)
		this->activeViewTable->makeAllSteps();
} 
void View::undoAllSteps()
{
	if(this->presentation == nullptr)
		return;

	if(this->activeViewTable != nullptr)
		this->activeViewTable->undoAllSteps();
	
	this->pause();
}


void View::speedUp()
{
	this->speedFactor = qMax(this->speedFactor - viewSpeedDelta, viewMinSpeedFactor);
	this->updateSpeed();
}

void View::slowDown()
{
	this->speedFactor = qMin(this->speedFactor + viewSpeedDelta, viewMaxSpeedFactor);
	this->updateSpeed();
}


void View::reachedEndOfTask()
{
	this->updateTaskResultViews();
	this->timer->setInterval(this->getTimeToSeeTests());
	this->timer->start();
}

void View::leftEndOfTask()
{
	this->updateTaskResultViews();
}

void View::pause()
{
	this->timer->stop();
	if(this->activeViewTable != nullptr)
		this->activeViewTable->stop();
}


void View::hideActiveViewTable()
{
	if(this->activeViewTable != nullptr)
		this->activeViewTable->hide();
}

void View::showActiveViewTable()
{
	if(this->activeViewTable != nullptr)
		this->activeViewTable->show();
}


void View::setActiveViewTable(ViewTable *newActiveViewTable)
{
	if(this->activeViewTable != nullptr)
		this->activeViewTable->hide();

	this->activeViewTable = newActiveViewTable;
	this->updateTable();

	if(this->activeViewTable != nullptr)
		this->activeViewTable->show();
}

void View::setActiveViewTable(const Task *taskOfNewActiveViewTable)
{
	for(ViewTable *viewTable : this->tables)
	{
		if(viewTable->getTask() == taskOfNewActiveViewTable)
		{
			this->setActiveViewTable(viewTable);
			return;
		}
	}
	this->setActiveViewTable((ViewTable*) nullptr);
}


void View::setTaskResultInTaskResultView(const TaskResult *taskResult, const Task *task)
{
	for(ViewTaskResult *viewTaskResult : this->taskResultViews)
		if(viewTaskResult->getTask() == task)
			viewTaskResult->setResult(taskResult);
}


void View::showTaskResultView(const Task *task)
{
	for(ViewTaskResult *viewTaskResult : this->taskResultViews)
		if(viewTaskResult->getTask() == task)
			viewTaskResult->show();
}


void View::placeInnerWidgets(const QSize &size)
{
	this->title->resize(size.width(), this->title->height());

	QRect viewTableRect;
	viewTableRect.setY(titleHeight + taskResultHeight + 2 * viewBorderWidth);
	viewTableRect.setHeight(size.height() - titleHeight - taskResultHeight - 3 * viewBorderWidth);
	viewTableRect.setWidth(qMin(size.width() - 2 * viewBorderWidth, viewTableRect.height() * (qreal) 3 / 2));
	viewTableRect.setX(viewBorderWidth + (size.width() - viewTableRect.width() - 2 * viewBorderWidth) / 2);
	viewTableRect.setWidth(qMin(size.width() - 2 * viewBorderWidth, viewTableRect.height() * (qreal) 3 / 2));

	for(ViewTable *viewTable : this->tables)
		viewTable->setGeometry(viewTableRect);

	int countVisibleTaskViews = 0;
	for(ViewTaskResult *viewTaskResult : this->taskResultViews)
		if(viewTaskResult->isVisible())
			countVisibleTaskViews++;
	
	qreal pos = (size.width() - (taskResultWidth + viewBorderWidth) * countVisibleTaskViews + viewBorderWidth) / 2;
	for(ViewTaskResult *viewTaskResult : this->taskResultViews)
	{
		if(viewTaskResult->isVisible())
		{
			viewTaskResult->move(pos, titleHeight + viewBorderWidth);
			pos += taskResultWidth + viewBorderWidth;
		}
	}
}


void View::updateSpeed()
{
	qreal speed = this->getSpeed();
	qreal timeToSeeComments = this->getTimeToSeeComments();
	for(ViewTable *viewTable : this->tables)
	{
		viewTable->setSpeed(speed);
		viewTable->setTimeToSeeComments(timeToSeeComments);
	}
	this->update();
}


bool View::nextTaskResultIterator()
{
	while(true)
	{
		if(!this->taskResultIterator++)
			return false;
		if((*this->taskResultIterator)->getTask()->isVisible())
			return true;
	}
	return false;
}

bool View::previousTaskResultIterator()
{
	while(true)
	{
		if(!this->taskResultIterator--)
			return false;
		if((*this->taskResultIterator)->isVisible())
			return true;
	}
	return false;
}

void View::initTaskResultIterator()
{
	this->taskResultIterator = (*this->reportIterator)->getTaskResultIterator();
	while(!this->taskResultIterator.isEnd())
	{
		if((*this->taskResultIterator)->isVisible())
			break;
		this->taskResultIterator++;
	}
}

void View::lastTaskResultIterator()
{
	this->taskResultIterator.toLastElement();
	while(!this->taskResultIterator.isEnd())
	{
		if((*this->taskResultIterator)->isVisible())
			break;
		this->taskResultIterator--;
	}
}


bool View::nextReportIterator()
{
	while(true)
	{
		if(!this->reportIterator++)
			return false;
		if((*this->reportIterator)->isVisible())
			return true;
	}
	return false;
}

bool View::previousReportIterator()
{
	while(true)
	{
		if(!this->reportIterator--)
			return false;
		if((*this->reportIterator)->isVisible())
			return true;
	}
	return false;
}

void View::initReportIterator()
{
	this->reportIterator = this->presentation->getReportIterator();
	while(!this->reportIterator.isEnd())
	{
		if((*this->reportIterator)->isVisible())
			break;
		this->reportIterator++;
	}
}
