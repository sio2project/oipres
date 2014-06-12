#include "OptionsEditor.h"

const QString optionsEditorTimeToSeeCommentsLabel = QString::fromUtf8("Czas na oglądanie komentarzy (w milisekundach)");
const QString optionsEditorTimeToSeeTestsLabel = QString::fromUtf8("Czas na oglądanie wyników testów (w milisekundach)");

const QString optionsEditorSpeedLabel = QString::fromUtf8("Prędkość pokazywania testów (szybciej <---> wolniej)");

const int optionsEditorSpeedSliderSize = 1000;

const QString optionsEditorEstimatedTimeLabel = QString::fromUtf8("Szacowany czas prezentacji");

const QString secondsString = QString::fromUtf8("s");
const QString minutesString = QString::fromUtf8("min");
const QString hoursString = QString::fromUtf8("g");
const QString infinityString = QString::fromUtf8("nieskończoność");

const QString optionsEditorSortLabel = QString::fromUtf8("Metoda sortowania raportów");

const QString optionsEditorEstimatedTimeRecalculationInProgress = QString::fromUtf8("Trwają obliczenia...");
const int optionsEditorTimeToWaitForEstimatedTimeRecalculation = 1000; // millseconds


OptionsEditor::OptionsEditor(Presentation *presentation, QWidget *parent) : QWidget(parent), presentation(presentation), sortReports(new SortReports()), timer(new QTimer(this))
{
	QFormLayout *layout = new QFormLayout();

	// time to see comments
	QLineEdit *timeToSeeComments = new QLineEdit(QString::number(presentation->getTimeToSeeComments()), this);
	timeToSeeComments->setValidator(new QIntValidator(presentation->minTimeToSeeComments, presentation->maxTimeToSeeComments, this));
	connect(timeToSeeComments, SIGNAL(textChanged(const QString&)), this, SLOT(timeToSeeCommentsChanged(const QString&)));
	layout->addRow(optionsEditorTimeToSeeCommentsLabel, timeToSeeComments);

	// time to see tests
	QLineEdit *timeToSeeTests = new QLineEdit(QString::number(presentation->getTimeToSeeTests()), this);
	timeToSeeTests->setValidator(new QIntValidator(presentation->minTimeToSeeTests, presentation->maxTimeToSeeTests, this));
	connect(timeToSeeTests, SIGNAL(textChanged(const QString&)), this, SLOT(timeToSeeTestsChanged(const QString&)));
	layout->addRow(optionsEditorTimeToSeeTestsLabel, timeToSeeTests);

	// speed
	QSlider *speedSlider = new QSlider(Qt::Horizontal, this);
	speedSlider->setRange(0, optionsEditorSpeedSliderSize);
	speedSlider->setSingleStep(1);
	speedSlider->setSliderPosition((int) (this->presentation->getSpeed() * optionsEditorSpeedSliderSize));
	connect(speedSlider, SIGNAL(valueChanged(int)), this, SLOT(speedValueChanged(int)));
	layout->addRow(optionsEditorSpeedLabel, speedSlider);

	QLabel *estimatedTime = new QLabel("", this);
	connect(this, SIGNAL(estimatedTimeChanged(const QString&)), estimatedTime, SLOT(setText(const QString&)));
	layout->addRow(optionsEditorEstimatedTimeLabel, estimatedTime);

	// sort
	QComboBox *sortMethods = new QComboBox(this);
	connect(sortMethods, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(sortMethodChanged(const QString&)));
	for(QString method : this->sortReports->availableMethods())
		sortMethods->addItem(method);
	layout->addRow(optionsEditorSortLabel, sortMethods);

	this->setLayout(layout);

	this->timer->setInterval(optionsEditorTimeToWaitForEstimatedTimeRecalculation);
	connect(this->timer, SIGNAL(timeout()), this, SLOT(updateEstimatedTime()));
	this->timer->setSingleShot(true);

	this->updateEstimatedTime();
}

OptionsEditor::~OptionsEditor()
{
	delete this->sortReports;
}

const Presentation *OptionsEditor::getPresentation() const
{
	return this->presentation;
}


void OptionsEditor::paintEvent(QPaintEvent *paintEvent)
{
	QStyleOption option;
	option.init(this);
	QPainter painter(this);
	this->style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
}


void OptionsEditor::timeToSeeCommentsChanged(const QString &newTimeToSeeComments)
{
	this->presentation->setTimeToSeeComments(newTimeToSeeComments.toInt());
	this->recalculateEstimatedTime();
}

void OptionsEditor::timeToSeeTestsChanged(const QString &newTimeToSeeTests)
{
	this->presentation->setTimeToSeeTests(newTimeToSeeTests.toInt());
	this->recalculateEstimatedTime();
}

void OptionsEditor::speedValueChanged(int newValue)
{
	this->presentation->setSpeed(((qreal) newValue) / optionsEditorSpeedSliderSize);
	this->recalculateEstimatedTime();
}

void OptionsEditor::recalculateEstimatedTime()
{
	emit estimatedTimeChanged(optionsEditorEstimatedTimeRecalculationInProgress);
	this->timer->start();
}

void OptionsEditor::updateEstimatedTime()
{
	int time = this->presentation->estimatedTime() / 1000;
	QString timeString = QString::number(time % 60) + secondsString;
	time /= 60;
	if(time)
		timeString = QString::number(time % 60) + minutesString + " " + timeString;
	time /= 60;
	if(time)
		timeString = QString::number(time % 24) + hoursString + " " + timeString;
	time /= 24;
	if(time)
		timeString = infinityString;
	emit estimatedTimeChanged(timeString);
}

void OptionsEditor::sortMethodChanged(const QString &newSortMethod)
{
	this->presentation->sortReports(this->sortReports, newSortMethod);
}
