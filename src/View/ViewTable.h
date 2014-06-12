#pragma once
#include "../main.h"
#include "../Report/TestGroup.h"
#include "../Report/Task.h"
#include "../Report/TaskResult.h"
#include "ViewTestGroup.h"
#include "ViewComments.h"
#include "ViewFrame.h"
#include "../Report/TimeInt.h"

class ViewTable : public QWidget
{
	Q_OBJECT;

public:
	ViewTable() = delete;
	ViewTable(const Task *task, QWidget *parent = nullptr);

	void addTestGroup(const TestGroup *testGroup);

	void updateViewTestGroupWidths();
	void updateViewTestGroupPositions();
	void updateScroll();
	void setScroll(const qreal newScroll);

	const Task *getTask() const;

	void setResult(const TaskResult *newTaskResult);

	bool isEnd();

	void paintEvent(QPaintEvent *paintEvent) override;
	void resizeEvent(QResizeEvent *resizeEvent) override;

	void setSpeed(qreal newSpeed);
	void setTimeToSeeComments(int newTimeToSeeComments); // in milliseconds

public slots:
	bool nextStep(); // returns true if next step is unavailable
	bool previousStep();
	void makeAllSteps();
	void undoAllSteps();

	void stop();

signals:
	void reachedEnd();
	void leftEnd();

private slots:
	void skipGroup();
	void undoGroup();

private:
	bool nextStepWithoutComments();
	bool previousStepWithoutComments();

	const TestResult *getNextTest();

	void setTimerForTests();
	void setTimerForComments();

	const Task *task;
	const TaskResult *taskResult;
	QList<ViewTestGroup*>::iterator nextToShow;
	QList<ViewTestGroup*> viewTestGroups;

	ViewFrame *viewFrame;
	ViewComments *viewComments;

	qreal scroll;

	QTimer *timer;

	qreal speed;
	int timeToSeeComments;
};
