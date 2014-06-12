#include "TabsEditor.h"

const QString tabsEditorOptionsString = QString::fromUtf8("Ustawienia");


TabsEditor::TabsEditor(Presentation *presentation, QWidget *parent) : QTabWidget(parent), presentation(presentation)
{
	const QList<Task*> tasks = presentation->getTaskList();
	QScrollArea *optionsScrollArea = new QScrollArea(this);
	optionsScrollArea->setWidget(new OptionsEditor(presentation, this));
	this->addTab(optionsScrollArea, tabsEditorOptionsString);
	for(Task *task : tasks)
	{
		QScrollArea *scrollArea = new QScrollArea(this);
		scrollArea->setWidget(new TaskEditor(task, this->presentation, this));
		this->addTab(scrollArea, task->getName());
	}
}


const Presentation *TabsEditor::getPresentation() const
{
	return this->presentation;
}
