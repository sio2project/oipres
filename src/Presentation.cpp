#include "Presentation.h"

Presentation::Presentation()
	: reports(),
	tasks(),
	timeToSeeComments(Presentation::defaultTimeToSeeComments),
	timeToSeeTests(Presentation::defaultTimeToSeeTests),
	speed(Presentation::defaultSpeed)
{
}

Presentation::~Presentation()
{
	for(Report *report : this->reports)
		delete report;
	for(Task *task : this->tasks)
		delete task;
}


void Presentation::addReport(Report *newReport)
{
	this->reports.push_back(newReport);
}

void Presentation::addTask(Task *newTask)
{
	this->tasks.push_back(newTask);
}


const QList<const Report*> Presentation::getReports() const
{
	QList<const Report*> result;
	for(const Report *report : this->reports)
		result.push_back(report);
	return result;
}

const QList<const Task*> Presentation::getTasks() const
{
	QList<const Task*> result;
	for(const Task *task : this->tasks)
		result.push_back(task);
	return result;
}

const QList<Task*> Presentation::getTaskList()
{
	QList<Task*> result;
	for(Task *task : this->tasks)
		result.push_back(task);
	return result;
}

bool Presentation::isVisible() const
{
	for(Report *report : this->reports)
		if(report->isVisible())
			return true;
	return false;
}

QListConstPointerIterator<Report> Presentation::getReportIterator() const
{
	return QListConstPointerIterator<Report>(this->reports.begin(), this->reports.end());
}


// options

void Presentation::setTimeToSeeComments(int newTimeToSeeComments)
{
	this->timeToSeeComments = newTimeToSeeComments;
}

void Presentation::setTimeToSeeTests(int newTimeToSeeTests)
{
	this->timeToSeeTests = newTimeToSeeTests;
}

void Presentation::setSpeed(qreal newSpeed)
{
	// the value must be in range [0, 1]
	newSpeed = qMin(newSpeed, (qreal) 1);
	newSpeed = qMax(newSpeed, (qreal) 0);
	this->speed = newSpeed;
}


int Presentation::getTimeToSeeComments() const
{
	return this->timeToSeeComments;
}

int Presentation::getTimeToSeeTests() const
{
	return this->timeToSeeTests;
}

qreal Presentation::getSpeed() const
{
	return this->speed;
}

int Presentation::estimatedTime() const
{
	int result = 0;
	for(Report *report : this->reports)
		result += report->estimatedTime(this->timeToSeeComments, this->timeToSeeTests, this->speed);
	return result;
}

void Presentation::sortReports(SortReports *sortReports, const QString &method)
{
	sortReports->sort(this->reports, method);
}
