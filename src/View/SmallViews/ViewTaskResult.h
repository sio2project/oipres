#pragma once
#include "../../main.h"
#include "../../Report/Task.h"
#include "../../Report/TaskResult.h"

class ViewTaskResult : public QWidget
{
	Q_OBJECT;

public:
	ViewTaskResult() = delete;
	ViewTaskResult(const Task *task, QWidget *parent = nullptr);

	void setResult(const TaskResult *newTaskResult);
	void unsetFocus();
	void setFocus();

	const Task *getTask() const;
	const TaskResult *getResult() const;

	void paintEvent(QPaintEvent *paintEvent) override;

private:
	const Task *task;
	const TaskResult *result;
};
