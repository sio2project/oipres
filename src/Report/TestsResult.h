#pragma once
#include "../main.h"
#include "Tests.h"
#include "TestGroupResult.h"

class TestsResult
{
	/* This class deletes every TestGroupResult that was given to it */
public:
	TestsResult(const Tests *tests = nullptr);
	TestsResult(const TestsResult &testsResult) = delete;
	TestsResult &operator=(const TestsResult &testsResult) = delete;
	~TestsResult();

	void setTests(const Tests *newTests);
	void addGroupResult(TestGroupResult *newTestGroupResult);

	int getResult() const;
	const Tests *getTests() const;
	const QList<const TestGroupResult*> getGroupResults() const;

	int estimatedTime(qreal speed) const;

private:
	const Tests *tests;
	QList<TestGroupResult*> groupResults;
};
