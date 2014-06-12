#include "TestsResult.h"

TestsResult::TestsResult(const Tests *tests) : tests(tests), groupResults()
{
}

TestsResult::~TestsResult()
{
	for(TestGroupResult *testGroupResult : this->groupResults)
		delete testGroupResult;
}

void TestsResult::setTests(const Tests *newTests)
{
	this->tests = newTests;
}

void TestsResult::addGroupResult(TestGroupResult *newTestGroupResult)
{
	this->groupResults.push_back(newTestGroupResult);
}

int TestsResult::getResult() const
{
	int result = 0;
	for(TestGroupResult *testGroupResult : this->groupResults)
		result += testGroupResult->getResult();
	return result;
}

const Tests *TestsResult::getTests() const
{
	return this->tests;
}

const QList<const TestGroupResult*> TestsResult::getGroupResults() const
{
	QList<const TestGroupResult*> result;
	for(const TestGroupResult *testGroupResult : this->groupResults)
		result.push_back(testGroupResult);
	return result;
}


int TestsResult::estimatedTime(qreal speed) const
{
	int result = 0;
	for(TestGroupResult *testGroupResult : this->groupResults)
		result += testGroupResult->estimatedTime(speed);
	return result;
}
