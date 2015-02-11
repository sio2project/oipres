#include "TestResult.h"

// translations
const QString statusToString[6] = {
	QString(),
	QString::fromUtf8("OK"),
	QString::fromUtf8("Zła odpowiedź"),
	QString::fromUtf8("Przekroczony limit czasu"),
	QString(),
	QString::fromUtf8("Błąd wykonania")
};

TestResult::TestResult() : result(0), time(), test(nullptr), status(0), comment("")
{
}

void TestResult::setResult(const int newResult)
{
	this->result = newResult;
}

void TestResult::setTest(const Test *newTest)
{
	this->test = newTest;
}

void TestResult::setTime(const TimeInt &newTime)
{
	this->time = newTime;
}

void TestResult::setStatus(const int newStatus)
{
	this->status = newStatus;
}

void TestResult::setComment(const QString &newComment)
{
	this->comment = newComment;
}

int TestResult::getResult() const
{
	return this->result;
}

const Test *TestResult::getTest() const
{
	return this->test;
}

TimeInt TestResult::getTime() const
{
	return this->time;
}

int TestResult::getStatus() const
{
	return this->status;
}

QString TestResult::getStatusColor() const
{
	QString colorName = "white";
	switch(this->status)
	{
		case TestResult::statusOK:
			colorName = "#5dab10";
			break;
		case TestResult::statusWA:
			colorName = "#ff6666";
			break;
		case TestResult::statusTLE:
			colorName = "#ff8000";
			break;
		case TestResult::statusRTE:
			colorName = "#ff8000";
			break;
		case TestResult::statusInComment:
			colorName = "#ff8000";
			break;
	}
	return colorName;
}

QString TestResult::getComment() const
{
	return this->comment;
}

QString TestResult::getStatusString() const
{
	if(this->status == 0)
		return this->comment;
	else if(0 < this->status && this->status < 6)
		return statusToString[this->status];
	return QString("");
}

int TestResult::estimatedTime(qreal speed) const
{
	// magic formula to make tests running more smoothly :)
	return (int) (qSqrt(qSqrt(qMax(this->time.getTime() / 1000.0, 0.01))) * speed * 1000.0);
}
