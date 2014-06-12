#include "TestGroup.h"

TestGroup::TestGroup() : tests(), visible(true)
{
}

TestGroup::~TestGroup()
{
	for(Test *test : this->tests)
		delete test;
}

void TestGroup::addTest(Test *newTest)
{
	this->tests.push_back(newTest);
}

void TestGroup::setVisible(bool newVisibility)
{
	this->visible = newVisibility;
}

QString TestGroup::getName() const
{
	if(this->tests.empty())
		return QString("");
	Test *test = *this->tests.begin();
	return test->getName();
}

int TestGroup::getMaxPoints() const
{
	if(!this->isVisible())
		return 0;
	if(this->tests.empty())
		return 0;
	int result = (*this->tests.begin())->getMaxPoints();
	for(Test *test : this->tests)
		result = qMin(result, test->getMaxPoints());
	return result;
}

int TestGroup::getSize() const
{
	return this->tests.size();
} 
bool TestGroup::isEmpty() const
{
	return this->tests.isEmpty();
}

const QList<const Test*> TestGroup::getTests() const
{
	QList<const Test*> result;
	for(const Test *test : this->tests)
		result.push_back(test);
	return result;
}

bool TestGroup::isVisible() const
{
	return this->visible;
}
