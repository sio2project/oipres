#include "Editor.h"

const QString editorEmptyPresentationString = QString::fromUtf8("Prezentacja jest pusta ;_;");


Editor::Editor(QWidget *parent) : QWidget(parent), presentation(nullptr), tabsEditor(nullptr)
{
}

void Editor::setPresentation(Presentation *newPresentation)
{
	if(this->tabsEditor != nullptr)
	{
		delete this->tabsEditor;
		this->tabsEditor = nullptr;
	}
	this->presentation = newPresentation;
	if(this->presentation != nullptr)
	{
		this->tabsEditor = new TabsEditor(this->presentation, this);
		this->tabsEditor->resize(this->size());
		this->tabsEditor->show();
	}
	
	this->update();
}

const Presentation *Editor::getPresentation() const
{
	return this->presentation;
}


void Editor::paintEvent(QPaintEvent *paintEvent)
{
	QStyleOption option;
	option.init(this);
	QPainter painter(this);
	this->style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);

	if(this->presentation == nullptr)
		this->style()->drawItemText(&painter, this->rect(), Qt::AlignVCenter | Qt::AlignHCenter, QPalette(), true, editorEmptyPresentationString);
}

void Editor::resizeEvent(QResizeEvent *resizeEvent)
{
	if(this->tabsEditor != nullptr)
		this->tabsEditor->resize(resizeEvent->size());
}
