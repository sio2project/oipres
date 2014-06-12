#pragma once
#include "../main.h"
#include "TimeInt.h"

class Test
{
public:
	Test();
	void setName(const QString &newName);
	void setMaxPoints(const int newMaxPoints);
	void setTimeLimit(const TimeInt &newTimeLimit);

	QString getName() const;
	int getMaxPoints() const;
	TimeInt getTimeLimit() const;

private:
	QString name;
	int maxPoints;
	TimeInt timeLimit;
};
