#pragma once
#include "../main.h"
#include "../Report/Report.h"

typedef bool (*SortReportComparator)(const Report*, const Report*);
typedef QPair<QString, SortReportComparator> Comparator;

Comparator makeComparator(const char *name, SortReportComparator comparator);

#include "SortingFunctions.h"

class SortReports
{
public:
	SortReports();
	void sort(QList<Report*> &reports, const QString method);
	QList<QString> availableMethods();

private:
	QMap<QString, SortReportComparator> methods;
};
