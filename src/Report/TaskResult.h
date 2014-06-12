#pragma once
#include "../main.h"
#include "Task.h"
#include "TestsResult.h"

class TaskResult
{
	/* This class deletes TaskResults that were given to it */
public:
	// constants for programming languages of source codes
	static const int langBegin = 0;
	static const int langUnknown = 0;
	static const int langC = 1;
	static const int langCpp = 2;
	static const int langPascal = 3;
	static const int langJava = 4;
	static const int langEnd = 5;

	TaskResult(const Task *task = nullptr, TestsResult *testsResult = nullptr);
	TaskResult(const TaskResult &taskResult) = delete;
	TaskResult &operator=(const TaskResult &taskResult) = delete;
	~TaskResult();

	void setTask(const Task *newTask);
	void setTestsResult(TestsResult *newTestsResult);
	void setCode(const QString &newCode); // source code
	void setLanguage(int newLanguage); // language of source code

	int getResult() const;
	const Task *getTask() const;
	const TestsResult *getTestsResult() const;
	QString getCode() const;
	QString getCommentsFromCode() const;
	int getLanguage() const;
	bool isVisible() const;
	QString getLanguageExtension() const;

	int estimatedTime(int timeToSeeComments, int timeToSeeTests, qreal speed);

private:
	QString getCComments() const;
	QString getPascalComments() const;

	const Task *task;
	TestsResult *testsResult;
	QString code;
	int language;
};
