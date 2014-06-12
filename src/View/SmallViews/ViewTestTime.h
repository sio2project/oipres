#pragma once
#include "../../main.h"
#include "../../Report/Test.h"
#include "../../Report/TestResult.h"

class ViewTestTime : public QWidget
{
	Q_OBJECT;

public:
	ViewTestTime() = delete;
	ViewTestTime(const Test *test, QWidget *parent = nullptr);

	void setResult(const TestResult *newTestResult);

	void paintEvent(QPaintEvent *paintEvent) override;

private:
	const Test *test;
	const TestResult *testResult;
};
