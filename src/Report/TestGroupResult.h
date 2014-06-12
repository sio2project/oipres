#pragma once
#include "../main.h"
#include "TestGroup.h"
#include "TestResult.h"

class TestGroupResult
{
public:
	TestGroupResult(const TestGroup *testGroup = nullptr);
	TestGroupResult(const TestGroupResult &testGroupResult) = delete;
	TestGroupResult &operator=(const TestGroupResult &testGroupResult) = delete;
	~TestGroupResult();

	void setTestGroup(const TestGroup *newTestGroup);
	void addTestResult(TestResult *newTestResult);

	int getResult() const;
	const TestGroup *getTestGroup() const;
	const QList<const TestResult*> getTestResults() const;
	bool isEmpty() const;
	bool isVisible() const;

	int estimatedTime(qreal speed) const;

private:
	const TestGroup *testGroup;
	QList<TestResult*> testResults;
};
