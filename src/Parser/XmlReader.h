#pragma once
#include "../main.h"
#include "../Presentation.h"

// creates presentation, based on the xml file
// if the input is incorrect, presentation may be partially filled, or left empty, but always there will appear a convenient message
// this function returns true if reading xml was successful, or false otherwise
bool parseXmlFile(QString path, Presentation *presentation);
