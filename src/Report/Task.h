#pragma once
#include "../main.h"
#include "Tests.h"

class Task
{
	/* This class deletes Tests that were given to it */
public:
	Task();
	Task(const Task &task) = delete;
	Task &operator=(const Task &task) = delete;
	~Task();

	void setTaskID(const QString &newTaskID);
	void setName(const QString &newName);
	void setTests(Tests *newTests);
	void setVisible(bool newVisibility);

	QString getTaskID() const;
	QString getName() const;
	int getMaxPoints() const;
	const Tests *getTests() const;
	Tests *getTests();
	bool isVisible() const;

private:
	QString taskID;
	QString name;
	Tests *tests;
	bool visible;
};
