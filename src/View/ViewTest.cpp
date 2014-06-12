#include "ViewTest.h"

const qreal testViewHeight = 25;
const qreal testBorderWidth = 0;

const qreal testNamePercentage = 0.1;
const qreal testResultPercentage = 0.63;
const qreal testTimePercentage = 0.27;

ViewTest::ViewTest(const Test * test, QWidget *parent) : QWidget(parent), test(test), testResult(nullptr)
{
	this->setStyleSheet("background-color: white;");
	this->setAutoFillBackground(true);
	this->viewTestName = new ViewTestName(this->test, this);
	this->viewTestStatus = new ViewTestStatus(this->test, this);
	this->viewTestTime = new ViewTestTime(this->test, this);

	this->resize(this->width(), testViewHeight);

	this->updateWidths();
}

ViewTest::~ViewTest()
{
	delete this->viewTestName;
	delete this->viewTestStatus;
	delete this->viewTestTime;
}

void ViewTest::updateWidths()
{
	this->viewTestName->move(testBorderWidth, testBorderWidth);
	this->viewTestName->resize((this->width() - 4 * testBorderWidth) * testNamePercentage, this->height() - 2 * testBorderWidth);

	this->viewTestStatus->move(this->viewTestName->width() + 2 * testBorderWidth, testBorderWidth);
	this->viewTestStatus->resize((this->width() - 4 * testBorderWidth) * testResultPercentage, this->height() - 2 * testBorderWidth);

	this->viewTestTime->resize((this->width() - 4 * testBorderWidth) * testTimePercentage, this->height() - 2 * testBorderWidth);
	this->viewTestTime->move(this->width() - testBorderWidth - this->viewTestTime->width(), testBorderWidth);
}


void ViewTest::setResult(const TestResult *newTestResult)
{
	this->testResult = newTestResult;
	this->viewTestStatus->setResult(this->testResult);
	this->viewTestTime->setResult(this->testResult);
}


const Test *ViewTest::getTest() const
{
	return this->test;
}

const TestResult *ViewTest::getTestResult() const
{
	return this->testResult;
}


void ViewTest::paintEvent(QPaintEvent *paintEvent)
{
	QStyleOption option;
	option.init(this);
	QPainter painter(this);
	this->style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
}

void ViewTest::resizeEvent(QResizeEvent *resizeEvent)
{
	this->updateWidths();
	QWidget::resizeEvent(resizeEvent);
}


TimeInt ViewTest::getTimeInterval() const
{
	if(this->testResult == nullptr)
		return TimeInt(-1);
	return this->testResult->getTime();
}
