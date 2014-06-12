#pragma once
#include "../main.h"

class TimeInt
{
public:
	TimeInt();
	TimeInt(int milliseconds);
	TimeInt(const QString &stringTime);

	void setTime(int newMilliseconds);
	void setTime(const QString &newTime);

	int getTime() const;
	QString toString() const;

	bool operator<(const TimeInt &timeInt) const;
	bool operator<=(const TimeInt &timeInt) const;
	bool operator>(const TimeInt &timeInt) const;
	bool operator>=(const TimeInt &timeInt) const;
	bool operator==(const TimeInt &timeInt) const;
	bool operator!=(const TimeInt &timeInt) const;

private:
	int milliseconds;
};
