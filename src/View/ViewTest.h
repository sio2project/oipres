#pragma once
#include "../main.h"
#include "../Report/Test.h"
#include "../Report/TestResult.h"
#include "SmallViews/ViewTestName.h"
#include "SmallViews/ViewTestStatus.h"
#include "SmallViews/ViewTestTime.h"
#include "../Report/TimeInt.h"

class ViewTest : public QWidget
{
	Q_OBJECT;

public:
	ViewTest() = delete;
	ViewTest(const Test *test, QWidget *parent = nullptr);
	ViewTest(const ViewTest &viewTest) = delete;
	ViewTest &operator=(const ViewTest &viewTest) = delete;
	~ViewTest();

	void updateWidths();

	void setResult(const TestResult *newTestResult);

	const Test *getTest() const;
	const TestResult *getTestResult() const;

	void paintEvent(QPaintEvent *paintEvent) override;
	void resizeEvent(QResizeEvent *resizeEvent) override;

	TimeInt getTimeInterval() const;

private:
	const Test *test;
	const TestResult *testResult;
	ViewTestName *viewTestName;
	ViewTestStatus *viewTestStatus;
	ViewTestTime *viewTestTime;
};
