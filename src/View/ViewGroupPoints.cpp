#include "ViewGroupPoints.h"

ViewGroupPoints::ViewGroupPoints(const TestGroup *testGroup, QWidget *parent) : QWidget(parent), testGroup(testGroup), testGroupResult(nullptr)
{
	this->setStyleSheet("background-color: #424242; color: #f2f2f2; font-weight: bold; font-size: 30px;");
	this->setAutoFillBackground(true);
}


void ViewGroupPoints::setResult(const TestGroupResult *newTestGroupResult)
{
	this->testGroupResult = newTestGroupResult;
}


void ViewGroupPoints::paintEvent(QPaintEvent *paintEvent)
{
	QStyleOption option;
	option.init(this);
	QPainter painter(this);
	this->style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);

	QString pointsString = "\?\?/";
	if(this->testGroupResult != nullptr)
		pointsString = QString::number(this->testGroupResult->getResult()) + "/";
	pointsString += QString::number(this->testGroup->getMaxPoints());

	this->style()->drawItemText(&painter, this->rect(), Qt::AlignVCenter | Qt::AlignHCenter, QPalette(), true, pointsString);
}
