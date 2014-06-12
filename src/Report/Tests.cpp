#include "Tests.h"

Tests::Tests() : testGroups()
{
}

Tests::~Tests()
{
	for(TestGroup *testGroup : this->testGroups)
		delete testGroup;
}

void Tests::addTestGroup(TestGroup *newTestGroup)
{
	this->testGroups.push_back(newTestGroup);
}

int Tests::getMaxPoints() const
{
	int result = 0;
	for(TestGroup *testGroup : this->testGroups)
		result += testGroup->getMaxPoints();
	return result;
}

const QList<const TestGroup*> Tests::getTestGroups() const
{
	QList<const TestGroup*> result;
	for(const TestGroup *testGroup : this->testGroups)
		result.push_back(testGroup);
	return result;
}

const QList<TestGroup*> Tests::getTestGroupList()
{
	QList<TestGroup*> result;
	for(TestGroup *testGroup : this->testGroups)
		result.push_back(testGroup);
	return result;
}

QListConstPointerIterator<TestGroup> Tests::getTestGroupsIterator() const
{
	return QListConstPointerIterator<TestGroup>(this->testGroups.begin(), this->testGroups.end());
}
