#pragma once
#include "../main.h"
#include "../Report/Task.h"
#include "../Report/TaskResult.h"

class ViewComments : public QTextEdit
{
	Q_OBJECT;

public:
	ViewComments() = delete;
	ViewComments(const Task *task, QWidget *parent = nullptr);

	void setResult(const TaskResult *newTaskResult);
	void setComments(const QString &newComments);

	const Task *getTask() const;
	const TaskResult *getResult() const;
	QString getComments() const;

	bool isEmpty() const;

	void mousePressEvent(QMouseEvent *mouseEvent) override;

private:
	const Task *task;
	const TaskResult *taskResult;
	QString comments;
};
