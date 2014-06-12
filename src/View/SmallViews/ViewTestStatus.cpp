#include "ViewTestStatus.h"

ViewTestStatus::ViewTestStatus(const Test *test, QWidget *parent) : QWidget(parent), test(test), testResult(nullptr)
{
	this->setAutoFillBackground(true);
	this->setResult(nullptr);
}


void ViewTestStatus::setResult(const TestResult *newTestResult)
{
	this->testResult = newTestResult;
	if(this->testResult != nullptr)
		this->setStyleSheet(QString("background-color: %1;").arg(this->testResult->getStatusColor()));
	this->update();
}


void ViewTestStatus::paintEvent(QPaintEvent *paintEvent)
{
	QStyleOption option;
	option.init(this);
	QPainter painter(this);
	this->style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);

	QString status = "\?\?\?";
	if(this->testResult != nullptr)
		status = this->testResult->getStatusString();
	this->style()->drawItemText(&painter, this->rect(), Qt::AlignVCenter | Qt::AlignHCenter, QPalette(), true, status);
}
