#pragma once
#include "../main.h"
#include "../Report/TestGroup.h"
#include "../Report/TestGroupResult.h"

class ViewGroupPoints : public QWidget
{
	Q_OBJECT;

public:
	ViewGroupPoints() = delete;
	ViewGroupPoints(const TestGroup *testGroup, QWidget *parent = nullptr);

	void setResult(const TestGroupResult *newTestGroupResult);

	void paintEvent(QPaintEvent *paintEvent) override;

signals:
	void reachedEnd();

private:
	const TestGroup *testGroup;
	const TestGroupResult *testGroupResult;
};
