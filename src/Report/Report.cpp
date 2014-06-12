#include "Report.h"

Report::Report() : reportID(""), date(), contestant(nullptr), taskResults()
{
}

Report::~Report()
{
	for(TaskResult *taskResult : this->taskResults)
		delete taskResult;
	if(this->contestant != nullptr)
		delete this->contestant;
}

void Report::setReportID(const QString &newID)
{
	this->reportID = newID;
}

void Report::setDate(const QDateTime &newDate)
{
	this->date = newDate;
}

void Report::addTaskResult(TaskResult *newTaskResult)
{
	this->taskResults.push_back(newTaskResult);
}

void Report::setContestant(Contestant *newContestant)
{
	this->contestant = newContestant;
}


QString Report::getReportID() const
{
	return this->reportID;
}

QDateTime Report::getDate() const
{
	return this->date;
}

int Report::getResult() const
{
	int result = 0;
	for(TaskResult *taskResult : this->taskResults)
		result += taskResult->getResult();
	return result;
}

const Contestant *Report::getContestant() const
{
	return this->contestant;
}

bool Report::isVisible() const
{
	for(TaskResult *taskResult : this->taskResults)
		if(taskResult->isVisible())
			return true;
	return false;
}

const QList<const TaskResult*> Report::getTaskResults() const
{
	QList<const TaskResult*> result;
	for(TaskResult *taskResult : this->taskResults)
		result.push_back(taskResult);
	return result;
}

QListConstPointerIterator<TaskResult> Report::getTaskResultIterator() const
{
	return QListConstPointerIterator<TaskResult>(this->taskResults.begin(), this->taskResults.end());
}


int Report::estimatedTime(int timeToSeeComments, int timeToSeeTests, qreal speed) const
{
	if(!this->isVisible())
		return 0;
	int result = 0;
	for(TaskResult *taskResult : this->taskResults)
		result += taskResult->estimatedTime(timeToSeeComments, timeToSeeTests, speed);
	return result;
}
