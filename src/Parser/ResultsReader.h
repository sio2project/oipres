#pragma once
#include "../main.h"
#include "../Report/Task.h"

QList<Report*> searchForResults(const QDomDocument &document, const QList<Task*> &tasks);
