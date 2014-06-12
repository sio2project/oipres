#pragma once
#include "../main.h"
#include "../Presentation.h"
#include "../Sort/SortReports.h"

class OptionsEditor : public QWidget
{
	Q_OBJECT;

public:
	OptionsEditor(Presentation *presentation, QWidget *parent = nullptr);
	OptionsEditor(const OptionsEditor &optionsEditor) = delete;
	OptionsEditor &operator=(const OptionsEditor &optionsEditor) = delete;
	~OptionsEditor();

	const Presentation *getPresentation() const;

	void paintEvent(QPaintEvent *paintEvent) override;

	void recalculateEstimatedTime();

public slots:
	void timeToSeeCommentsChanged(const QString &newTimeToSeeComments);
	void timeToSeeTestsChanged(const QString &newTimeToSeeTests);
	void speedValueChanged(int newValue);
	void sortMethodChanged(const QString &newSortMethod);
	void updateEstimatedTime();

signals:
	void estimatedTimeChanged(const QString &newEstimatedTime);
	
private:
	Presentation *presentation;
	SortReports *sortReports;

	QTimer *timer; // gives time for the user to type or change the slider when the presentation is big and comupation of estimated time takes much time
};
