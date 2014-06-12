#include "OptionsReader.h"

void readOptions(const QDomDocument &document, Presentation *presentation)
{
	QDomElement siorpt = document.firstChildElement("siorpt");
	QDomElement oipresentation = siorpt.firstChildElement("oipresentation");
	if(oipresentation.isNull())
		return;
	const QString timeToSeeCommentsString = oipresentation.firstChildElement("timetoseecomments").text();
	const QString timeToSeeTestsString = oipresentation.firstChildElement("timetoseetests").text();
	const QString speedString = oipresentation.firstChildElement("speed").text();

	presentation->setTimeToSeeComments(timeToSeeCommentsString.toInt());
	presentation->setTimeToSeeTests(timeToSeeTestsString.toInt());
	presentation->setSpeed(speedString.toDouble());
}
