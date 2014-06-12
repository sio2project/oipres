#include "ViewFrame.h"

ViewFrame::ViewFrame(int width, QWidget *parent) : QWidget(parent), width(width)
{
	this->resize(0, 0);
	this->setStyleSheet("background-color: rgba(66, 66, 66, 200);");
	this->setAutoFillBackground(true);
}

void ViewFrame::resizeEvent(QResizeEvent *resizeEvent)
{
	this->setMask(
		QRegion(
			QRect(0, 0, resizeEvent->size().width(), resizeEvent->size().height())
		).subtracted(
			QRegion(
				QRect(width, width, resizeEvent->size().width() - 2 * this->width, resizeEvent->size().height() - 2 * this->width)
			)
		)
	);
}
