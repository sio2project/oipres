#pragma once
#include "../main.h"
#include "../Presentation.h"
#include "../Report/Contestant.h"
#include "../QListConstPointerIterator.h"
#include "ViewTable.h"
#include "SmallViews/ViewTaskResult.h"

class View : public QWidget
{
	Q_OBJECT;

public:
	View(QWidget *parent = nullptr);

	const Presentation *getPresentation() const;
	void setPresentation(const Presentation *newPresentation);

	void clear();

	void configureViewMenu(QMenu *menu);
	void enableMenu();
	void disableMenu();

	void updateTable();
	void updateTaskResultViews();

	void paintEvent(QPaintEvent *paintEvent) override;
	void resizeEvent(QResizeEvent *resizeEvent) override;

	qreal getSpeed() const;
	qreal getTimeToSeeComments() const;
	qreal getTimeToSeeTests() const;

public slots:
	// the functions below return true, if next/previous something does not exist, and the step wasn't really done
	bool nextStep();
	bool previousStep();
	bool nextTask();
	bool previousTask();
	bool nextReport();
	bool previousReport();
	void makeAllSteps();
	void undoAllSteps();

	void setToBeginning();

	void speedUp();
	void slowDown();

	void reachedEndOfTask();
	void leftEndOfTask();

	void pause();

private:
	void setActiveViewTable(ViewTable *newActiveViewTable);
	void setActiveViewTable(const Task *taskOfNewActiveViewTable);
	void hideActiveViewTable();
	void showActiveViewTable();

	void setTaskResultInTaskResultView(const TaskResult *taskResult, const Task *task);
	void showTaskResultView(const Task *task);

	void placeInnerWidgets(const QSize &size);

	void updateSpeed();

	bool nextTaskResultIterator();
	bool previousTaskResultIterator();
	void initTaskResultIterator();
	void lastTaskResultIterator();

	bool nextReportIterator();
	bool previousReportIterator();
	void initReportIterator();

	QLabel *title;

	ViewTable *activeViewTable;

	const Presentation *presentation;
	QListConstPointerIterator<Report> reportIterator;
	QListConstPointerIterator<TaskResult> taskResultIterator;

	QMenu *viewMenu;

	QList<ViewTable*> tables;
	QList<ViewTaskResult*> taskResultViews;

	qreal speedFactor;

	QTimer *timer;
};
