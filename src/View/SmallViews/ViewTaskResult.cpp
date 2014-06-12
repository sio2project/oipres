#include "ViewTaskResult.h"

ViewTaskResult::ViewTaskResult(const Task *task, QWidget *parent) : QWidget(parent), task(task), result(nullptr)
{
	this->setStyleSheet("background-color: #96f; border-style: outset; border-width: 2px; border-radius: 10px; border-color: #868686; font-weight: bold; font-size: 20px;");
	this->setAutoFillBackground(true);
}

void ViewTaskResult::setResult(const TaskResult *newTaskResult)
{
	this->result = newTaskResult;
	this->update();
}

const Task *ViewTaskResult::getTask() const
{
	return this->task;
}

const TaskResult *ViewTaskResult::getResult() const
{
	return this->result;
}

void ViewTaskResult::paintEvent(QPaintEvent *paintEvent)
{
	QStyleOption option;
	option.init(this);
	QPainter painter(this);
	this->style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);

	QRect upperRect(0, 0, this->rect().width(), this->rect().height() / 2);
	QRect lowerRect(0, this->rect().height() / 2, this->rect().width(), this->rect().height() / 2);

	this->style()->drawItemText(&painter, upperRect, Qt::AlignVCenter | Qt::AlignHCenter, QPalette(), true, this->task->getName());

	QString resultString = "??";
	if(this->result != nullptr)
		resultString = QString::number(this->result->getResult());

	int maxPoints = 0;
	const Tests *tests = this->task->getTests();
	if(tests != nullptr)
		maxPoints = tests->getMaxPoints();
	
	this->style()->drawItemText(&painter, lowerRect, Qt::AlignVCenter | Qt::AlignHCenter, QPalette(), true, resultString + "/" + QString::number(maxPoints));
}
