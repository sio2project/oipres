#include "Test.h"

Test::Test() : name(""), maxPoints(0), timeLimit()
{
}

void Test::setName(const QString &newName)
{
	this->name = newName;
}

void Test::setMaxPoints(const int newMaxPoints)
{
	this->maxPoints = newMaxPoints;
}

void Test::setTimeLimit(const TimeInt &newTimeLimit)
{
	this->timeLimit = newTimeLimit;
}

QString Test::getName() const
{
	return this->name;
}

int Test::getMaxPoints() const
{
	return this->maxPoints;
}

TimeInt Test::getTimeLimit() const
{
	return this->timeLimit;
}
