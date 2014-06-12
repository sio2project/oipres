#pragma once
#include "../main.h"
#include "Contestant.h"
#include "TaskResult.h"
#include "../QListConstPointerIterator.h"

class Report
{
	/* This class deletes Contestants and TaskResults that were given to it */
public:
	Report();
	Report(const Report &report) = delete;
	Report &operator=(const Report &report) = delete;
	~Report();

	void setReportID(const QString &newID);
	void setDate(const QDateTime &newDate);
	void addTaskResult(TaskResult *newTaskResult);
	void setContestant(Contestant *newContestant);

	QString getReportID() const;
	QDateTime getDate() const;
	int getResult() const;
	const Contestant *getContestant() const;
	bool isVisible() const; // checks if any task result from this report is visible

	const QList<const TaskResult*> getTaskResults() const;
	QListConstPointerIterator<TaskResult> getTaskResultIterator() const;

	int estimatedTime(int timeToSeeComments, int timeToSeeTests, qreal speed) const;

private:
	QString reportID;
	QDateTime date;

	Contestant *contestant;

	QList<TaskResult*> taskResults;
};
