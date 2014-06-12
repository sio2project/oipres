#include "Task.h"

Task::Task() : taskID(""), name(""), tests(nullptr), visible(true)
{
}

Task::~Task()
{
	if(this->tests != nullptr)
		delete this->tests;
}

void Task::setTaskID(const QString &newTaskID)
{
	this->taskID = newTaskID;
}

void Task::setName(const QString &newName)
{
	this->name = newName;
}

void Task::setTests(Tests *newTests)
{
	if(this->tests != nullptr)
		delete this->tests;
	this->tests = newTests;
}

void Task::setVisible(bool newVisibility)
{
	this->visible = newVisibility;
}

QString Task::getTaskID() const
{
	return this->taskID;
}

QString Task::getName() const
{
	return this->name;
}

int Task::getMaxPoints() const
{
	if(this->tests == nullptr)
		return 0;
	return this->tests->getMaxPoints();
}

const Tests *Task::getTests() const
{
	return this->tests;
}

Tests *Task::getTests()
{
	return this->tests;
}

bool Task::isVisible() const
{
	return this->visible;
}
