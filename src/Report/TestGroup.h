#pragma once
#include "../main.h"
#include "Test.h"

class TestGroup
{
	/* This class deleted every Test that was given to it */
public:
	TestGroup();
	TestGroup(const TestGroup &testGroup) = delete;
	TestGroup &operator=(const TestGroup &testGroup) = delete;
	~TestGroup();

	void addTest(Test *newTest);
	void setVisible(bool newVisibility);

	QString getName() const;
	int getMaxPoints() const;
	int getSize() const;
	bool isEmpty() const;
	const QList<const Test*> getTests() const;
	bool isVisible() const;

private:
	QList<Test*> tests;
	bool visible;
};
