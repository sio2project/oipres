#include "ViewTestName.h"

ViewTestName::ViewTestName(const Test *test, QWidget *parent) : QWidget(parent), test(test)
{
	this->setStyleSheet("background-color: #646464; color: #f2f2f2;");
	this->setAutoFillBackground(true);
}

void ViewTestName::paintEvent(QPaintEvent *paintEvent)
{
	QStyleOption option;
	option.init(this);
	QPainter painter(this);
	this->style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);

	this->style()->drawItemText(&painter, this->rect(), Qt::AlignVCenter | Qt::AlignHCenter, QPalette(), true, this->test->getName());
}
