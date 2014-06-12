#pragma once
#include "../main.h"
#include "SortReports.h"
#include "../Report/Report.h"

// To define own comparators, you must put them in table below (don't forget to increment the numberOfComparators constant).
// Write all definitions in file SortingFunctions.cpp, here you may (and should) change only this one integer constant.
const int numberOfComparators = 3;
extern Comparator arrayOfComparators[numberOfComparators];
