#pragma once
#include "main.h"

class ScreenSwitch : public QWidget
{
	Q_OBJECT;

public:
	ScreenSwitch(QWidget *parent = nullptr);
	void addScreen(QWidget *newScreen);
	void switchTo(QWidget *screenToRaise);

	bool isSwitchedTo(QWidget *screenToCheck) const;

	void resizeEvent(QResizeEvent *resizeEvent) override;

private:
	QList<QWidget*> screens;
	QWidget *raised;
};
