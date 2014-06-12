#include "ViewTable.h"

const qreal viewTableBorderWidth = 6;

ViewTable::ViewTable(const Task *task, QWidget *parent)
	: QWidget(parent),
	task(task),
	taskResult(nullptr),
	nextToShow(),
	viewTestGroups(),
	viewFrame(new ViewFrame(viewTableBorderWidth, this)),
	viewComments(nullptr),
	scroll(0),
	timer(new QTimer(this)),
	speed(1)
{
	this->viewComments = new ViewComments(task, this);
	this->viewComments->move(viewTableBorderWidth, viewTableBorderWidth);

	this->resize(this->width(), viewTableBorderWidth);

	const Tests *tests = this->task->getTests();
	if(tests != nullptr)
	{
		for(const TestGroup *testGroup : tests->getTestGroups())
			this->addTestGroup(testGroup);
	}

	this->nextToShow = this->viewTestGroups.begin();

	this->timer->setSingleShot(true);
	connect(this->timer, SIGNAL(timeout()), this, SLOT(nextStep()));
}

void ViewTable::addTestGroup(const TestGroup *testGroup)
{
	if(!testGroup->isVisible())
		return;
	ViewTestGroup *viewTestGroup = new ViewTestGroup(testGroup, this);
	viewTestGroups.push_back(viewTestGroup);

	connect(viewTestGroup, SIGNAL(reachedEnd()), this, SLOT(skipGroup()));

	viewTestGroup->move(viewTableBorderWidth, this->height());

	this->resize(this->width(), this->height() + viewTestGroup->height() + viewTableBorderWidth);

	this->updateViewTestGroupWidths();

	this->nextToShow = this->viewTestGroups.begin();

	this->viewFrame->raise();
}

void ViewTable::updateViewTestGroupWidths()
{
	for(ViewTestGroup *viewTestGroup : this->viewTestGroups)
		viewTestGroup->resize(this->width() - 2 * viewTableBorderWidth, viewTestGroup->height());
}

void ViewTable::updateViewTestGroupPositions()
{
	qreal position = this->scroll + viewTableBorderWidth;
	for(ViewTestGroup *viewTestGroup : this->viewTestGroups)
	{
		viewTestGroup->move(viewTestGroup->x(), position);
		position += viewTableBorderWidth + viewTestGroup->height();
	}
}

void ViewTable::updateScroll()
{
	if(this->viewTestGroups.isEmpty())
		return;
	QList<ViewTestGroup*>::iterator lastViewTestGroup = this->nextToShow;
	if(lastViewTestGroup == this->viewTestGroups.end() || ((*lastViewTestGroup)->isStepAtTheBeginning() && lastViewTestGroup != this->viewTestGroups.begin()))
		lastViewTestGroup--;
	qreal bottomLine = (*lastViewTestGroup)->y() + (*lastViewTestGroup)->height() + viewTableBorderWidth;

	if(bottomLine - this->scroll <= this->height())
		this->setScroll(0);
	else
		this->setScroll(this->height() - bottomLine + this->scroll);
}

void ViewTable::setScroll(const qreal newScroll)
{
	this->scroll = newScroll;
	this->updateViewTestGroupPositions();
}

const Task *ViewTable::getTask() const
{
	return this->task;
}

void ViewTable::setResult(const TaskResult *newTaskResult)
{
	if(newTaskResult != nullptr)
		if(newTaskResult->getTask() != this->task)
			newTaskResult = nullptr;
	this->taskResult = newTaskResult;
	if(this->taskResult == nullptr)
	{
		for(ViewTestGroup *viewTestGroup : this->viewTestGroups)
			viewTestGroup->setResult(nullptr);
		return;
	}
	const TestsResult *testsResult = this->taskResult->getTestsResult();
	if(testsResult == nullptr)
	{
		this->setResult(nullptr);
		return;
	}

	const QList<const TestGroupResult*> testGroupResults = testsResult->getGroupResults();

	for(ViewTestGroup *viewTestGroup : this->viewTestGroups)
	{
		for(const TestGroupResult *testGroupResult : testGroupResults)
		{
			if(viewTestGroup->getTestGroup() == testGroupResult->getTestGroup())
				viewTestGroup->setResult(testGroupResult);
		}
	}

	for(ViewTestGroup* viewTestGroup : this->viewTestGroups)
		viewTestGroup->hide();
	this->nextToShow = this->viewTestGroups.begin();
	if(this->nextToShow != this->viewTestGroups.end())
		(*this->nextToShow)->show();

	this->viewComments->setResult(this->taskResult);
	this->viewComments->show();

	if(this->viewComments->isEmpty())
	{
		this->viewComments->hide();
		this->setTimerForTests();
	}
	else
		this->setTimerForComments();
}


bool ViewTable::nextStep()
{
	this->stop();
	if(this->viewComments->isVisible())
		this->viewComments->hide();
	if(this->viewTestGroups.empty())
	{
		this->setTimerForTests();
		return true;
	}
	const bool noNext = this->nextStepWithoutComments();
	if(!noNext)
		this->setTimerForTests();
	return noNext;
}

bool ViewTable::previousStep()
{
	this->stop();
	if(this->viewComments->isVisible())
		return true;
	if(this->previousStepWithoutComments())
	{
		if(this->viewComments->isEmpty())
			return true;
		this->viewComments->show();
		this->setTimerForComments();
	}
	else
		this->setTimerForTests();
	return false;
}

void ViewTable::makeAllSteps()
{
	while(!this->nextStep())
		;
}

void ViewTable::undoAllSteps()
{
	while(!this->previousStep())
		;
}


void ViewTable::stop()
{
	this->timer->stop();
}


bool ViewTable::isEnd()
{
	return this->nextToShow == this->viewTestGroups.end();
}


void ViewTable::paintEvent(QPaintEvent *paintEvent)
{
	QStyleOption option;
	option.init(this);
	QPainter painter(this);
	this->style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
}

void ViewTable::resizeEvent(QResizeEvent *resizeEvent)
{
	this->viewFrame->resize(resizeEvent->size());
	this->viewComments->resize(resizeEvent->size().width() - 2 * viewTableBorderWidth, resizeEvent->size().height() - 2 * viewTableBorderWidth);
	this->updateScroll();
	this->updateViewTestGroupWidths();
	QWidget::resizeEvent(resizeEvent);
}


void ViewTable::setSpeed(qreal newSpeed)
{
	this->speed = newSpeed;
}

void ViewTable::setTimeToSeeComments(int newTimeToSeeComments)
{
	this->timeToSeeComments = newTimeToSeeComments;
}


void ViewTable::skipGroup()
{
	this->nextToShow++;
	if(this->nextToShow == this->viewTestGroups.end())
		emit reachedEnd();
	else
		(*this->nextToShow)->show();
}

void ViewTable::undoGroup()
{
	if(this->nextToShow != this->viewTestGroups.end())
		(*this->nextToShow)->hide();
	this->nextToShow--;
}


bool ViewTable::nextStepWithoutComments()
{
	if(this->nextToShow == this->viewTestGroups.end())
		return true;
	(*this->nextToShow)->nextStep();
	this->updateScroll();
	return false;
}

bool ViewTable::previousStepWithoutComments()
{
	if(this->nextToShow == this->viewTestGroups.end())
	{
		this->undoGroup();
		emit leftEnd();
	}
	if((*this->nextToShow)->previousStep())
	{
		if(this->nextToShow == this->viewTestGroups.begin())
			return true;
		this->undoGroup();
		(*this->nextToShow)->previousStep();
		return false;
	}
	this->updateScroll();
	return false;
}


const TestResult *ViewTable::getNextTest()
{
	if(this->nextToShow == this->viewTestGroups.end())
		return nullptr;
	const TestResult *nextTest = (*this->nextToShow)->getNextTest();
	if(nextTest == nullptr)
	{
		this->nextToShow++;
		if(this->nextToShow != this->viewTestGroups.end())
			nextTest = (*this->nextToShow)->getNextTest();
	}
	return nextTest;
}

void ViewTable::setTimerForTests()
{
	const TestResult *testResult = this->getNextTest();
	if(testResult == nullptr)
	{
		emit reachedEnd();
		return;
	}
	this->timer->setInterval(testResult->estimatedTime(this->speed));
	this->timer->start();
}

void ViewTable::setTimerForComments()
{
	this->timer->setInterval(this->timeToSeeComments);
	this->timer->start();
}
