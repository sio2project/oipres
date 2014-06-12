#include "TasksReader.h"
#include "../Report/Tests.h"
#include "../Report/TestGroup.h"
#include "../Report/Test.h"
#include "../Report/TimeInt.h"
#include "../Report/TestResult.h"
#include "../Report/TestGroupResult.h"
#include "../Report/TestsResult.h"
#include "../Report/TaskResult.h"
#include "../Report/Contestant.h"
#include "../Report/Report.h"

TestResult *readTestResult(const QDomElement &testNode, const TestGroup *testGroup)
{
	if(testGroup == nullptr)
		return nullptr;
	const QString testName = testNode.firstChildElement("testname").text();
	const QString testResultString = testNode.firstChildElement("testpoints").text();
	const QString testTime = testNode.firstChildElement("testtime").text();
	const QString testComment = testNode.firstChildElement("testcomment").text();
	const QString testStatus = testNode.firstChildElement("testresult").text();
	const Test *test = nullptr;
	for(const Test *testP : testGroup->getTests())
	{
		if(testP->getName() == testName)
		{
			test = testP;
			break;
		}
	}
	if(test == nullptr)
		return nullptr;
	TestResult *testResult = new TestResult();
	testResult->setTest(test);
	testResult->setResult(testResultString.toInt());
	testResult->setTime(TimeInt(testTime));
	testResult->setStatus(testStatus.toInt());
	testResult->setComment(testComment);
	return testResult;
}

TestsResult *readTestsResult(const QDomElement &taskNode, const Task *task)
{
	if(task->getTests() == nullptr)
		return nullptr;

	const QList<const TestGroup*> testGroups = task->getTests()->getTestGroups();
	QList<const TestGroup*>::const_iterator nextGroup = testGroups.begin();

	TestsResult *testsResult = new TestsResult();
	testsResult->setTests(task->getTests());

	TestGroupResult *testGroupResult = new TestGroupResult();
	if(nextGroup != testGroups.end())
		testGroupResult->setTestGroup(*nextGroup);

	QDomNodeList testNodes = taskNode.elementsByTagName("test");

	for(int i = 0; i < testNodes.length(); i++)
	{
		QDomElement testElement = testNodes.item(i).toElement();
		if(testElement.attribute("newgroup", "0") == "1")
		{
			if(!testGroupResult->isEmpty())
			{
				testsResult->addGroupResult(testGroupResult);
				testGroupResult = new TestGroupResult();
				if(nextGroup != testGroups.end())
				{
					nextGroup++;
					if(nextGroup != testGroups.end())
						testGroupResult->setTestGroup(*nextGroup);
				}
			}
		}
		TestResult *testResult = readTestResult(testElement, testGroupResult->getTestGroup());
		if(testResult != nullptr)
			testGroupResult->addTestResult(testResult);
	}

	if(testGroupResult->isEmpty())
		delete testGroupResult;
	else
		testsResult->addGroupResult(testGroupResult);

	return testsResult;
}

TaskResult *readTaskResult(const QDomElement &taskNode, const QList<Task*> &tasks)
{
	const QString taskID = taskNode.firstChildElement("taskid").text();
	const QString code = taskNode.firstChildElement("code").text();
	const QString codeFile = taskNode.firstChildElement("codefile").text();
	Task *task = nullptr;
	for(Task *taskP :  tasks)
	{
		if(taskP->getTaskID() == taskID)
		{
			task = taskP;
			break;
		}
	}
	if(task == nullptr)
		return nullptr;
	TaskResult *taskResult = new TaskResult();
	taskResult->setTask(task);
	taskResult->setTestsResult(readTestsResult(taskNode, task));
	taskResult->setCode(QUrl::fromPercentEncoding(code.toAscii()));

	if(codeFile.endsWith(".c"))
		taskResult->setLanguage(TaskResult::langC);
	else if(codeFile.endsWith(".cpp"))
		taskResult->setLanguage(TaskResult::langCpp);
	else if(codeFile.endsWith(".pas"))
		taskResult->setLanguage(TaskResult::langPascal);
	else if(codeFile.endsWith(".java"))
		taskResult->setLanguage(TaskResult::langJava);

	return taskResult;
}

QString extractContestantName(const QString data)
{
	QRegExp regex("^\\s*([^\\s].*[^\\s])\\s*\\([^\\)\\(]*\\)\\s*$");
	if(!regex.exactMatch(data))
		return "";
	return regex.cap(1);
}

QString extractContestantUsername(const QString data)
{
	QRegExp regex("^.*\\(([^\\)\\(]*)\\)\\s*$");
	if(!regex.exactMatch(data))
		return "";
	return regex.cap(1);
}

bool compareTaskResults(TaskResult *a, TaskResult *b)
{
	if(a->getTask() == nullptr)
		return false;
	if(a->getTask() == nullptr)
		return true;
	return QString::localeAwareCompare(a->getTask()->getName(), b->getTask()->getName()) < 0;
}

Report *readReport(const QDomElement &reportNode, const QList<Task*> &tasks)
{
	Contestant *contestant = new Contestant();
	Report *report = new Report();
	report->setContestant(contestant);

	const QString userID = reportNode.firstChildElement("userno").text();
	const QString user = reportNode.firstChildElement("user").text();
	contestant->setUserID(userID.toInt());
	contestant->setName(extractContestantName(user));
	contestant->setUsername(extractContestantUsername(user));

	const QString reportID = reportNode.firstChildElement("raportno").text();

	report->setReportID(reportID);
	QDomNodeList taskNodes = reportNode.elementsByTagName("task");

	QList<TaskResult*> taskResults;
	for(int i = 0; i < taskNodes.length(); i++)
	{
		TaskResult *taskResult = readTaskResult(taskNodes.item(i).toElement(), tasks);
		if(taskResult != nullptr)
			taskResults.push_back(taskResult);
	}

	qSort(taskResults.begin(), taskResults.end(), compareTaskResults);

	for(TaskResult *taskResult : taskResults)
		report->addTaskResult(taskResult);

	return report;
}

QList<Report*> searchForResults(const QDomDocument &document, const QList<Task*> &tasks)
{
	QList<Report*> result;
	QDomNodeList reportNodes = document.elementsByTagName("rpt");
	for(int i = 0; i < reportNodes.length(); i++)
	{
		Report *report = readReport(reportNodes.item(i).toElement(), tasks);
		if(report != nullptr)
			result.push_back(report);
	}
	return result;
}
