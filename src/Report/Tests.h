#pragma once
#include "../main.h"
#include "TestGroup.h"
#include "../QListConstPointerIterator.h"

class Tests
{
	/* This class deletes every TestGroup that was given to it */
public:
	Tests();
	Tests(const Tests &tests) = delete;
	Tests &operator=(const Tests &tests) = delete;
	~Tests();

	void addTestGroup(TestGroup *newTestGroup);

	int getMaxPoints() const;
	const QList<const TestGroup*> getTestGroups() const;
	const QList<TestGroup*> getTestGroupList();
	QListConstPointerIterator<TestGroup> getTestGroupsIterator() const;

private:
	QList<TestGroup*> testGroups;
};
