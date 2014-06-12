#pragma once
#include "../main.h"

class ViewFrame : public QWidget
{
public:
	ViewFrame(int width, QWidget *parent = nullptr);

	void resizeEvent(QResizeEvent *resizeEvent) override;

private:
	int width;
};
