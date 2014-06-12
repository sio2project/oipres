#pragma once
#include "../main.h"
#include "../Report/TestGroup.h"
#include "../Report/TestGroupResult.h"
#include "ViewTest.h"
#include "ViewGroupPoints.h"
#include "../Report/TimeInt.h"

class ViewTestGroup : public QWidget
{
	Q_OBJECT;

public:
	ViewTestGroup() = delete;
	ViewTestGroup(const TestGroup *testGroup, QWidget *parent = nullptr);
	ViewTestGroup(const ViewTestGroup *viewTestGroup) = delete;
	ViewTestGroup &operator=(const ViewTestGroup *viewTestGroup) = delete;
	~ViewTestGroup();

	void updateTestWidths();
	void updateMyHeight();

	void setResult(const TestGroupResult *newTestGroupResult);

	bool nextStep(); // returns true if next step is unavailable
	bool previousStep(); // returns true, if previous step is unavailable
	bool isStepAtTheBeginning() const;

	const TestGroup *getTestGroup() const;

	void resizeEvent(QResizeEvent *resieEvent) override;
	void paintEvent(QPaintEvent *paintEvent) override;

	const TestResult *getNextTest();

	void show();

signals:
	void reachedEnd();

private:
	const TestGroup *testGroup;
	const TestGroupResult *testGroupResult;
	QList<ViewTest*>::iterator nextToShow;
	QList<ViewTest*> viewTests;
	ViewGroupPoints *viewGroupPoints;
};
