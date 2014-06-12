#include "TaskResult.h"

TaskResult::TaskResult(const Task *task, TestsResult *testsResult) : task(task), testsResult(testsResult), code(""), language(TaskResult::langUnknown)
{
}

TaskResult::~TaskResult()
{
	if(this->testsResult != nullptr)
		delete this->testsResult;
}

void TaskResult::setTask(const Task *newTask)
{
	this->task = newTask;
}

void TaskResult::setTestsResult(TestsResult *newTestsResult)
{
	if(this->testsResult != nullptr)
		delete this->testsResult;
	this->testsResult = newTestsResult;
}

void TaskResult::setCode(const QString &newCode)
{
	this->code = newCode;
}

void TaskResult::setLanguage(int newLanguage)
{
	if(newLanguage < TaskResult::langBegin || TaskResult::langEnd <= newLanguage)
		this->language = TaskResult::langUnknown;
	else
		this->language = newLanguage;
}

int TaskResult::getResult() const
{
	if(this->testsResult == nullptr)
		return 0;
	if(this->task == nullptr)
		return 0;
	if(!this->task->isVisible())
		return 0;
	return this->testsResult->getResult();
}

const Task *TaskResult::getTask() const
{
	return this->task;
}

const TestsResult *TaskResult::getTestsResult() const
{
	return this->testsResult;
}

QString TaskResult::getCode() const
{
	return this->code;
}

QString TaskResult::getCommentsFromCode() const
{
	if(this->language == TaskResult::langPascal)
		return this->getPascalComments();
	return this->getCComments();
}

int TaskResult::getLanguage() const
{
	return this->language;
}

QString TaskResult::getLanguageExtension() const
{
	switch(this->language)
	{
		case TaskResult::langC:
			return ".c";
		case TaskResult::langCpp:
			return ".cpp";
		case TaskResult::langPascal:
			return ".pas";
		case TaskResult::langJava:
			return ".java";
	}
	return ".unknown";
}

bool TaskResult::isVisible() const
{
	return this->task->isVisible();
}

QString TaskResult::getCComments() const
{
	bool openedMultilineComment = false;
	bool openedLineComment = false;
	bool openedString = false;
	QString stringDelimiters = "";
	QString result = "";
	QString openedComment = "";

	auto matches = [&] (int pos, const QString &word)
	{
		for(int i = 0; i < word.length(); i++)
		{
			if(pos + i >= this->code.length())
				return false;
			if(this->code[pos + i] != word[i])
				return false;
		}
		return true;
	};

	for(int i = 0; i < this->code.length(); i++)
	{
		if(openedMultilineComment)
		{
			if(matches(i, "*/"))
			{
				result += openedComment + "*/\n";
				openedComment = "";
				openedMultilineComment = false;
				i++;
			}
			else
			{
				openedComment += this->code[i];
			}
		}
		else if(openedLineComment)
		{
			if(matches(i, "\n"))
			{
				result += openedComment + "\n";
				openedComment = "";
				openedLineComment = false;
			}
			else if(matches(i, "\\\n"))
			{
				openedComment += "\\\n";
				i++;
			}
			else
			{
				openedComment += this->code[i];
			}
		}
		else if(openedString)
		{
			if(matches(i, stringDelimiters))
			{
				openedString = false;
			}
			else if(matches(i, "\\"))
			{
				bool skipped = false;
				for(i++; i < this->code.length(); i++)
				{
					if(this->code[i] != ' ' || this->code[i] != '\t')
						break;
					else
						skipped = true;
				}
				if(i < this->code.length())
				{
					if(skipped)
					{
						if(this->code[i] != '\n')
							i--;
					}
				}
			}
		}
		else
		{
			if(matches(i, "/*"))
			{
				i++;
				openedMultilineComment = true;
				openedComment = "/*";
			}
			else if(matches(i, "//"))
			{
				i++;
				openedLineComment = true;
				openedComment = "//";
			}
			else if(matches(i, "\""))
			{
				openedString = true;
				stringDelimiters = "\"";
			}
			else if(matches(i, "'"))
			{
				openedString = true;
				stringDelimiters = "'";
			}
		}
	}
	return result;
}

QString TaskResult::getPascalComments() const
{
	bool openedMultilineComment = false;
	bool openedLineComment = false;
	bool openedString = false;
	QString result = "";
	QString openedComment = "";

	auto matches = [&] (int pos, const QString &word)
	{
		for(int i = 0; i < word.length(); i++)
		{
			if(pos + i >= this->code.length())
				return false;
			if(this->code[pos + i] != word[i])
				return false;
		}
		return true;
	};

	for(int i = 0; i < this->code.length(); i++)
	{
		if(openedMultilineComment)
		{
			if(matches(i, "*)"))
			{
				result += openedComment + "*)\n";
				openedComment = "";
				openedMultilineComment = false;
				i++;
			}
			else if(matches(i, "}"))
			{
				result += openedComment + "}\n";
				openedComment = "";
				openedMultilineComment = false;
			}
			else
			{
				openedComment += this->code[i];
			}
		}
		else if(openedLineComment)
		{
			if(matches(i, "\n"))
			{
				result += openedComment + "\n";
				openedComment = "";
				openedLineComment = false;
			}
			else
			{
				openedComment += this->code[i];
			}
		}
		else if(openedString)
		{
			if(matches(i, "''"))
			{
				i++;
			}
			else if(matches(i, "'"))
			{
				openedString = false;
			}
		}
		else
		{
			if(matches(i, "(*"))
			{
				i++;
				openedMultilineComment = true;
				openedComment = "(*";
			}
			else if(matches(i, "{"))
			{
				openedMultilineComment = true;
				openedComment = "{";
			}
			else if(matches(i, "//"))
			{
				openedLineComment = true;
				openedComment = "//";
			}
			else if(matches(i, "'"))
			{
				openedString = true;
			}
		}
	}
	return result;
}


int TaskResult::estimatedTime(int timeToSeeComments, int timeToSeeTests, qreal speed)
{
	if(!this->isVisible())
		return 0;
	int result = timeToSeeTests;
	if(!this->getCommentsFromCode().isEmpty())
		result += timeToSeeComments;
	if(this->testsResult != nullptr)
		result += this->testsResult->estimatedTime(speed);
	return result;
}
