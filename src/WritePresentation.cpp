#include "WritePresentation.h"

void writeOptions(const Presentation *presentation, QTextStream &out)
{
	out << "<oipresentation>";
	out << "<timetoseecomments>" << presentation->getTimeToSeeComments() << "</timetoseecomments>";
	out << "<timetoseetests>" << presentation->getTimeToSeeTests() << "</timetoseetests>";
	out << "<speed>" << presentation->getSpeed() << "</speed>";
	out << "</oipresentation>";
}

void writeTest(const Test *test, QTextStream &out)
{
	if(test == nullptr)
		return;
	out << "<testname>" << test->getName() << "</testname>";
	out << "<testtimelimit>" << test->getTimeLimit().toString() << "</testtimelimit>";
	out << "<testmaxpoints>" << test->getMaxPoints() << "</testmaxpoints>";
}

void writeTestResult(const TestResult *testResult, bool beginGroup, QTextStream &out)
{
	if(testResult == nullptr)
		return;
	out << "<test";
	if(beginGroup)
		out << " newgroup=\"1\"";
	out << ">";

	writeTest(testResult->getTest(), out);

	out << "<testresult>" << testResult->getStatus() << "</testresult>";
	out << "<testtime>" << testResult->getTime().toString() << "</testtime>";
	out << "<testpoints>" << testResult->getResult() << "</testpoints>";
	out << "<testcomment>" << testResult->getComment() << "</testcomment>";

	out << "</test>";
}

void writeTestGroupResult(const TestGroupResult *testGroupResult, QTextStream &out)
{
	if(testGroupResult == nullptr || !testGroupResult->isVisible())
		return;
	bool first = true;
	for(const TestResult *testResult : testGroupResult->getTestResults())
	{
		writeTestResult(testResult, first, out);
		first = false;
	}
}

void writeTestsResult(const TestsResult *testsResult, QTextStream &out)
{
	if(testsResult == nullptr)
		return;
	for(const TestGroupResult *testGroupResult : testsResult->getGroupResults())
		writeTestGroupResult(testGroupResult, out);
}

void writeTask(const Task *task, QTextStream &out)
{
	if(task == nullptr || !task->isVisible())
		return;
	out << "<taskid>" << task->getTaskID() << "</taskid>";
	out << "<taskname>" << task->getName() << "</taskname>";
	out << "<taskpoints>" << task->getMaxPoints() << "</taskpoints>";
}

void writeTaskResult(const TaskResult *taskResult, QTextStream &out)
{
	if(taskResult == nullptr || !taskResult->isVisible())
		return;
	out << "<task>";
	writeTask(taskResult->getTask(), out);
	out << "<taskresult>" << taskResult->getResult() << "</taskresult>";
	out << "<code>" << QUrl::toPercentEncoding(taskResult->getCode()) << "</code>";
	out << "<codefile>" << "file" << taskResult->getLanguageExtension() << "</codefile>";
	writeTestsResult(taskResult->getTestsResult(), out);
	out << "</task>";
}

void writeContestant(const Contestant *contestant, QTextStream &out)
{
	if(contestant == nullptr)
		return;
	out << "<userno>" << contestant->getUserID() << "</userno>";
	out << "<user>" << contestant->getName() << " (" << contestant->getUsername() << ")</user>";
}

void writeReport(const Report *report, QTextStream &out)
{
	if(report == nullptr || !report->isVisible())
		return;
	out << "<rpt>";
	writeContestant(report->getContestant(), out);
	out << "<raportno>" << report->getReportID() << "</raportno>";
	out << "<result>" << report->getResult() << "</result>";
	for(const TaskResult *taskResult : report->getTaskResults())
		writeTaskResult(taskResult, out);
	out << "</rpt>";
}

void writePresentation(const Presentation *presentation, QTextStream &out)
{
	out << "<?xml version=\"1.0\" encoding=\"utf-8\" ?>";
	out << "<siorpt>";
	writeOptions(presentation, out);
	for(const Report *report : presentation->getReports())
		writeReport(report, out);
	out << "</siorpt>";
}
