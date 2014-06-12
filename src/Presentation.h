#pragma once
#include "main.h"
#include "Report/Report.h"
#include "Report/Task.h"
#include "QListConstPointerIterator.h"
#include "Sort/SortReports.h"

class Presentation
{
	/* This class deletes every Report and Task that was given to it */
public:
	const static int defaultTimeToSeeComments = 3000; // milliseconds
	const static int defaultTimeToSeeTests = 3000; // milliseconds
	constexpr static qreal defaultSpeed = 0.3;
	const static int minTimeToSeeComments = 0; // milliseconds
	const static int maxTimeToSeeComments = 1000 * 1000 * 1000; // milliseconds
	const static int minTimeToSeeTests = 0; // milliseconds
	const static int maxTimeToSeeTests = 1000 * 1000 * 1000; // milliseconds

	Presentation();
	Presentation(const Presentation &presentation) = delete;
	Presentation &operator=(const Presentation &presentation) = delete;
	~Presentation();

	void addReport(Report *newReport);
	void addTask(Task *newTask);

	const QList<const Report*> getReports() const;
	const QList<const Task*> getTasks() const;
	const QList<Task*> getTaskList();
	bool isVisible() const;

	QListConstPointerIterator<Report> getReportIterator() const;

	// options
	void setTimeToSeeComments(int newTimeToSeeComments);
	void setTimeToSeeTests(int newTimeToSeeTests);
	void setSpeed(qreal newSpeed);

	int getTimeToSeeComments() const;
	int getTimeToSeeTests() const;
	qreal getSpeed() const;

	int estimatedTime() const;

	void sortReports(SortReports *sortReports, const QString &method);

private:
	QList<Report*> reports;
	QList<Task*> tasks;

	int timeToSeeComments; // in milliseconds
	int timeToSeeTests; // in milliseconds
	qreal speed; // real value from range [0, 1], the lesser value is, the faster presentation becomes
};
