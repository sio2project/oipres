#include "TasksReader.h"
#include "../Report/Tests.h"
#include "../Report/TestGroup.h"
#include "../Report/Test.h"
#include "../Report/TimeInt.h"

Test *getTest(const QDomElement &testNode)
{
	Test *test = new Test();
	const QString testName = testNode.firstChildElement("testname").text();
	const QString testTimeLimit = testNode.firstChildElement("testtimelimit").text();
	const QString testMaxPoints = testNode.firstChildElement("testmaxpoints").text();
	test->setName(testName);
	test->setMaxPoints(testMaxPoints.toInt());
	test->setTimeLimit(TimeInt(testTimeLimit));
	return test;
}

Tests *readTests(const QDomElement &taskNode)
{
	Tests *tests = new Tests();
	TestGroup *testGroup = new TestGroup();
	QDomNodeList testNodes = taskNode.elementsByTagName("test");
	for(int i = 0; i < testNodes.length(); i++)
	{
		QDomElement testElement = testNodes.item(i).toElement();
		if(testElement.attribute("newgroup", "0") == "1")
		{
			if(!testGroup->isEmpty())
			{
				tests->addTestGroup(testGroup);
				testGroup = new TestGroup();
			}
		}
		testGroup->addTest(getTest(testElement));
	}
	if(!testGroup->isEmpty())
		tests->addTestGroup(testGroup);
	else
		delete testGroup;
	return tests;
}

QList<Task*> searchForTasks(const QDomDocument &document)
{
	QList<Task*> result;
	QSet<QString> usedIDs;
	QDomNodeList tasks = document.elementsByTagName("task");
	for(int i = 0; i < tasks.length(); i++)
	{
		QDomNode node = tasks.item(i);
		const QString taskID = node.firstChildElement("taskid").text();
		const QString taskName = node.firstChildElement("taskname").text();
		if(!usedIDs.contains(taskID))
		{
			usedIDs.insert(taskID);
			Task *task = new Task();
			task->setTaskID(taskID);
			task->setName(taskName);
			task->setTests(readTests(node.toElement()));
			result.push_back(task);
		}
	}
	return result;
}
