#pragma once
#include "../main.h"
#include "Test.h"
#include "TimeInt.h"

class TestResult
{
public:
	// contstants for status
	static const int statusInComment = 0; // unknown error, details are located in comments and should be shown on presentation
	static const int statusOK = 1; // ok
	static const int statusWA = 2; // wrong answer
	static const int statusTLE = 3; // time limit exceeded
	static const int statusRTE = 5; // runtime error

	TestResult();

	void setResult(const int newResult);
	void setTest(const Test *newTest);
	void setTime(const TimeInt &newTime);
	void setStatus(const int newStatus);
	void setComment(const QString &newComment);

	int getResult() const;
	const Test *getTest() const;
	TimeInt getTime() const;
	int getStatus() const;
	QString getStatusColor() const; // colors that will be visible on the presentation
	QString getStatusString() const;
	QString getComment() const;

	int estimatedTime(qreal speed) const;

private:
	int result;
	TimeInt time;
	const Test *test;
	int status;
	QString comment;
};
