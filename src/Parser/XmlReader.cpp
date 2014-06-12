#include "XmlReader.h"
#include "../Report/Task.h"
#include "TasksReader.h"
#include "ResultsReader.h"
#include "OptionsReader.h"

const QString parserCouldNotOpenTheXmlFile = QString::fromUtf8("Otworzenie pliku Xml się nie powiodło.");
const QString parserBrokenFile = QString::fromUtf8("Podany plik zbyt mało przypomina wymagany format raportów.");

bool compareTasks(Task *a, Task *b)
{
	return QString::localeAwareCompare(a->getName(), b->getName()) < 0;
}

bool parseXmlFile(QString path, Presentation *presentation)
{
	QFile xmlFile(path);

	if(!xmlFile.open(QIODevice::ReadOnly))
	{
		QMessageBox msgBox;
		msgBox.setText(parserCouldNotOpenTheXmlFile);
		msgBox.exec();
		return false;
	}
	
	QDomDocument document("siorpt");
	if(!document.setContent(&xmlFile))
	{
		xmlFile.close();
		QMessageBox msgBox;
		msgBox.setText(parserBrokenFile);
		msgBox.exec();
		return false;
	}
	xmlFile.close();

	QList<Task*> tasks = searchForTasks(document);
	qSort(tasks.begin(), tasks.end(), compareTasks);

	for(Task *task : tasks)
		presentation->addTask(task);

	QList<Report*> reports = searchForResults(document, tasks);
	for(Report *report : reports)
		presentation->addReport(report);
	
	readOptions(document, presentation);

	return true;
}
