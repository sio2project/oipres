#include "ViewComments.h"

ViewComments::ViewComments(const Task *task, QWidget *parent) : QTextEdit(parent), task(task), taskResult(nullptr), comments("")
{
	this->setReadOnly(true);
	this->setStyleSheet("background-color: #424242; color: #f2f2f2;");
}


void ViewComments::setResult(const TaskResult *newTaskResult)
{
	this->taskResult = newTaskResult;
	if(this->taskResult == nullptr)
		this->setComments("");
	else
		this->setComments(this->taskResult->getCommentsFromCode());
}

void ViewComments::setComments(const QString &newComments)
{
	this->comments = newComments;
	this->setText(this->comments);
}


const Task *ViewComments::getTask() const
{
	return this->task;
}

const TaskResult *ViewComments::getResult() const
{
	return this->taskResult;
}

QString ViewComments::getComments() const
{
	return this->comments;
}

bool ViewComments::isEmpty() const
{
	return this->comments.isEmpty();
}

void ViewComments::mousePressEvent(QMouseEvent *mouseEvent)
{
	mouseEvent->ignore(); // prevent widget from having focus
}
