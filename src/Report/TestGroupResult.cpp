#include "TestGroupResult.h"

TestGroupResult::TestGroupResult(const TestGroup *testGroup) : testGroup(testGroup), testResults()
{
}

TestGroupResult::~TestGroupResult()
{
	for(TestResult *testResult : this->testResults)
		delete testResult;
}

void TestGroupResult::setTestGroup(const TestGroup *newTestGroup)
{
	this->testGroup = newTestGroup;
}

void TestGroupResult::addTestResult(TestResult *newTestResult)
{
	this->testResults.push_back(newTestResult);
}

int TestGroupResult::getResult() const
{
	if(this->testResults.empty())
		return 0;
	if(this->testGroup == nullptr)
		return 0;
	if(!this->testGroup->isVisible())
		return 0;
	int result = (*this->testResults.begin())->getResult();
	for(TestResult *testResult : this->testResults)
		result = qMin(result, testResult->getResult());
	return result;
}

const TestGroup *TestGroupResult::getTestGroup() const
{
	return this->testGroup;
}

const QList<const TestResult*> TestGroupResult::getTestResults() const
{
	QList<const TestResult*> result;
	for(const TestResult *testResult : this->testResults)
		result.push_back(testResult);
	return result;
}

bool TestGroupResult::isEmpty() const
{
	return this->testResults.isEmpty();
}

bool TestGroupResult::isVisible() const
{
	if(this->testGroup == nullptr)
		return false;
	return this->testGroup->isVisible();
}

int TestGroupResult::estimatedTime(qreal speed) const
{
	if(!this->isVisible())
		return 0;
	int result = 0;
	for(TestResult *testResult : this->testResults)
		result += testResult->estimatedTime(speed);
	return result;
}
