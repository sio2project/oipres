#include "ViewTestGroup.h"

const qreal pointsWidthPercentage = 0.1;
const qreal borderWidth = 2;


ViewTestGroup::ViewTestGroup(const TestGroup *testGroup, QWidget *parent) : QWidget(parent), testGroup(testGroup), testGroupResult(nullptr), nextToShow(), viewTests()
{
	this->setStyleSheet("background-color: #424242;");
	this->setAutoFillBackground(true);

	qreal pos = borderWidth;
	for(const Test *test : testGroup->getTests())
	{
		ViewTest *viewTest = new ViewTest(test, this);
		viewTests.push_back(viewTest);
		viewTest->move(borderWidth, pos);
		pos += viewTest->height() + borderWidth;
	}
	this->setMaximumHeight(pos);

	this->resize(this->width(), pos);

	this->viewGroupPoints = new ViewGroupPoints(this->testGroup, this);

	this->updateTestWidths();
}


ViewTestGroup::~ViewTestGroup()
{
	for(ViewTest *viewTest : this->viewTests)
		delete viewTest;
	delete this->viewGroupPoints;
}


void ViewTestGroup::updateTestWidths()
{
	for(ViewTest *viewTest : this->viewTests)
		viewTest->resize((this->width() - 3 * borderWidth) * (1 - pointsWidthPercentage), viewTest->height());
	
	this->viewGroupPoints->move((this->width() - 3 * borderWidth) * (1 - pointsWidthPercentage) + 2 * borderWidth, borderWidth);

	this->viewGroupPoints->resize((this->width() - 3 * borderWidth) * pointsWidthPercentage, this->height() - 2 * borderWidth);
}

void ViewTestGroup::updateMyHeight()
{
	if(this->nextToShow == this->viewTests.begin())
		this->resize(this->width(), 0);
	else
	{
		QList<ViewTest*>::iterator lastShown = this->nextToShow;
		lastShown--;
		this->resize(this->width(), (*lastShown)->y() + (*lastShown)->height() + borderWidth);
	}
}


void ViewTestGroup::setResult(const TestGroupResult *newTestGroupResult)
{
	this->testGroupResult = newTestGroupResult;
	if(this->testGroupResult == nullptr)
	{
		for(ViewTest *viewTest : this->viewTests)
			viewTest->setResult(nullptr);
		this->viewGroupPoints->setResult(nullptr);
		return;
	}

	const QList<const TestResult*> testResults = this->testGroupResult->getTestResults();

	for(const TestResult *testResult : testResults)
	{
		for(ViewTest *viewTest : this->viewTests)
		{
			if(testResult->getTest() == viewTest->getTest())
				viewTest->setResult(testResult);
		}
	}

	viewGroupPoints->setResult(this->testGroupResult);

	this->nextToShow = this->viewTests.begin();
}


bool ViewTestGroup::nextStep()
{
	if(this->nextToShow == this->viewTests.end())
		return true;
	this->nextToShow++;
	if(this->nextToShow == this->viewTests.end())
		emit reachedEnd();
	this->updateMyHeight();
	return false;
}

bool ViewTestGroup::previousStep()
{
	if(this->nextToShow == this->viewTests.begin()) return true; this->nextToShow--; this->updateMyHeight(); return false; }

bool ViewTestGroup::isStepAtTheBeginning() const
{
	return this->nextToShow == this->viewTests.begin();
}


const TestGroup *ViewTestGroup::getTestGroup() const
{
	return this->testGroup;
}


void ViewTestGroup::resizeEvent(QResizeEvent *resizeEvent)
{
	this->updateTestWidths();
	QWidget::resizeEvent(resizeEvent);
}


void ViewTestGroup::paintEvent(QPaintEvent *paintEvent)
{
	QStyleOption option;
	option.init(this);
	QPainter painter(this);
	this->style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
}


const TestResult *ViewTestGroup::getNextTest()
{
	if(this->nextToShow == this->viewTests.end())
		return nullptr;
	return (*this->nextToShow)->getTestResult();
}


void ViewTestGroup::show()
{
	this->resize(this->width(), 0);
	this->nextToShow = this->viewTests.begin();
	QWidget::show();
}
