#pragma once
#include "../main.h"
#include "../Report/Task.h"
#include "../Presentation.h"

class TaskEditor : public QWidget
{
	Q_OBJECT;

public:
	TaskEditor(Task *task, const Presentation *presentation, QWidget *parent = nullptr);

	const Task *getTask() const;

	void paintEvent(QPaintEvent *paintEvent) override;

public slots:
	void stateChanged(int state);
	void taskVisibilityStateChanged(int state);
	
private:
	Task *task;
	const Presentation *presentation;
};
