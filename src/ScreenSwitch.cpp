#include "ScreenSwitch.h"

ScreenSwitch::ScreenSwitch(QWidget *parent) : QWidget(parent), raised(nullptr)
{
}

void ScreenSwitch::addScreen(QWidget *newScreen)
{
	newScreen->move(0, 0);
	newScreen->resize(this->width(), this->height());
	this->screens.push_back(newScreen);
	this->switchTo(newScreen);
}

void ScreenSwitch::switchTo(QWidget *screenToRaise)
{
	for(QWidget *screen : this->screens)
	{
		if(screen == screenToRaise)
		{
			screen->raise();
			this->raised = screenToRaise;
		}
	}
}

bool ScreenSwitch::isSwitchedTo(QWidget *screenToCheck) const
{
	return screenToCheck == this->raised;
}

void ScreenSwitch::resizeEvent(QResizeEvent *resizeEvent)
{
	for(QWidget *screen : this->screens)
		screen->resize(resizeEvent->size());
}
