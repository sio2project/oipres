#pragma once
#include "../../main.h"
#include "../../Report/Test.h"

class ViewTestName : public QWidget
{
	Q_OBJECT;

public:
	ViewTestName() = delete;
	ViewTestName(const Test *test, QWidget *parent = nullptr);

	void paintEvent(QPaintEvent *paintEvent) override;

private:
	const Test *test;
};
