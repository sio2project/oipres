#include "ViewTestTime.h"

ViewTestTime::ViewTestTime(const Test *test, QWidget *parent) : QWidget(parent), test(test), testResult(nullptr)
{
	this->setAutoFillBackground(true);
}


void ViewTestTime::setResult(const TestResult *newTestResult)
{
	this->testResult = newTestResult;
	if(this->testResult != nullptr)
		this->setStyleSheet(QString("background-color: %1;").arg(this->testResult->getStatusColor()));
	this->update();
}


void ViewTestTime::paintEvent(QPaintEvent *paintEvent)
{
	QStyleOption option;
	option.init(this);
	QPainter painter(this);
	this->style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);

	QString time = "??.??s";
	if(this->testResult != nullptr)
		time = this->testResult->getTime().toString();

	this->style()->drawItemText(&painter, this->rect(), Qt::AlignVCenter | Qt::AlignHCenter, QPalette(), true, time + "/" + this->test->getTimeLimit().toString());
}
