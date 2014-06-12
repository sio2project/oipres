#include "SortReports.h"

Comparator makeComparator(const char *name, SortReportComparator comparator)
{
	return qMakePair(QString::fromUtf8(name), comparator);
}

SortReports::SortReports()
{
	for(int i = 0; i < numberOfComparators; i++)
		this->methods[arrayOfComparators[i].first] = arrayOfComparators[i].second;
}

void SortReports::sort(QList<Report*> &reports, const QString method)
{
	SortReportComparator cmp = this->methods[method];
	if(cmp != nullptr)
		qSort(reports.begin(), reports.end(), cmp);
}

QList<QString> SortReports::availableMethods()
{
	QList<QString> list;
	for(int i = 0; i < numberOfComparators; i++)
		list.push_back(arrayOfComparators[i].first);
	return list;
}
