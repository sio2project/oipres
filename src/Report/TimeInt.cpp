#include "TimeInt.h"

TimeInt::TimeInt() : milliseconds(0)
{
}

TimeInt::TimeInt(int milliseconds) : milliseconds(milliseconds)
{
}

TimeInt::TimeInt(const QString &stringTime) : milliseconds(0)
{
	this->setTime(stringTime);
}


void TimeInt::setTime(int newMilliseconds)
{
	this->milliseconds = newMilliseconds;
}

void TimeInt::setTime(const QString &newTime)
{
	QRegExp regex("^([0-9]+)\\.([0-9]+)s$");
	if(regex.exactMatch(newTime))
		this->milliseconds = regex.cap(1).toInt() * 1000 + regex.cap(2).toInt() * 10;
}


int TimeInt::getTime() const
{
	return this->milliseconds;
}

QString TimeInt::toString() const
{
	return QString::number(this->milliseconds / 1000) + "." + QString("%1").arg(QString::number((this->milliseconds % 1000) / 10), 2, QChar('0')) + "s";
}


bool TimeInt::operator<(const TimeInt &timeInt) const
{
	return this->milliseconds < timeInt.milliseconds;
}

bool TimeInt::operator<=(const TimeInt &timeInt) const
{
	return this->milliseconds <= timeInt.milliseconds;
}

bool TimeInt::operator>(const TimeInt &timeInt) const
{
	return this->milliseconds >= timeInt.milliseconds;
}

bool TimeInt::operator>=(const TimeInt &timeInt) const
{
	return this->milliseconds >= timeInt.milliseconds;
}

bool TimeInt::operator==(const TimeInt &timeInt) const
{
	return this->milliseconds == timeInt.milliseconds;
}

bool TimeInt::operator!=(const TimeInt &timeInt) const
{
	return this->milliseconds != timeInt.milliseconds;
}
