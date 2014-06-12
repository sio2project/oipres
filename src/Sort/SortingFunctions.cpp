#include "SortingFunctions.h"

bool lexicographicalOrder(const Report *reportA, const Report *reportB)
{
	QStringList listA = reportA->getContestant()->getName().split(" ", QString::SkipEmptyParts);
	QStringList listB = reportB->getContestant()->getName().split(" ", QString::SkipEmptyParts);
	if(listA.empty())
		return false;
	if(listB.empty())
		return true;
	int cmp = QString::localeAwareCompare(listA.back(), listB.back());
	if(cmp < 0)
		return true;
	if(cmp > 0)
		return false;
	for(int i = 0; i < qMin(listA.size(), listB.size()); i++)
	{
		cmp = QString::localeAwareCompare(listA[i], listB[i]);
		if(cmp < 0)
			return true;
		if(cmp > 0)
			return false;
	}
	return listA.size() < listB.size();
}

bool reverseLexicographicalOrder(const Report *reportA, const Report *reportB)
{
	return lexicographicalOrder(reportB, reportA);
}

// definition of the array, containing all comparators associated with their names (names are automaitcally encoded in utf-8)
Comparator arrayOfComparators[numberOfComparators] = {
	makeComparator("Bez sortowania", nullptr),
	makeComparator("Porządek leksykograficzny", lexicographicalOrder),
	makeComparator("Odwrotny porządek leksykograficzny", reverseLexicographicalOrder),
};
