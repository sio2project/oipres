#include "TaskEditor.h"

const QString taskEditorTaskMessage = QString::fromUtf8("Pokaż zadanie %1.");
const QString taskEditorTestGroupMessage = QString::fromUtf8("Wybierz podzbiór testów, które zostaną pokazane na prezentacji:");

const int taskEditorSpacing = 25;


TaskEditor::TaskEditor(Task *task, const Presentation *presentation, QWidget *parent) : QWidget(parent), task(task), presentation(presentation)
{
	QVBoxLayout *vBoxLayout = new QVBoxLayout();

	QCheckBox *taskVisibility = new QCheckBox(taskEditorTaskMessage.arg(this->task->getName()), this);
	taskVisibility->setCheckState(this->task->isVisible() ? Qt::Checked : Qt::Unchecked);
	connect(taskVisibility, SIGNAL(stateChanged(int)), this, SLOT(taskVisibilityStateChanged(int)));
	vBoxLayout->addWidget(taskVisibility);

	vBoxLayout->addSpacing(taskEditorSpacing);

	vBoxLayout->addWidget(new QLabel(taskEditorTestGroupMessage, this));

	const Tests *tests = task->getTests();
	if(tests != nullptr)
	{
		for(const TestGroup* testGroup: tests->getTestGroups())
		{
			QHBoxLayout *hBoxLayout = new QHBoxLayout();
			QCheckBox *checkBox = new QCheckBox(testGroup->getName(), this);
			checkBox->setCheckState(testGroup->isVisible() ? Qt::Checked : Qt::Unchecked);
			hBoxLayout->addWidget(checkBox);

			for(const Test *test : testGroup->getTests())
			{
				if(test->getName() == testGroup->getName())
					continue;
				QLabel *testLabel = new QLabel(test->getName(), this);
				testLabel->setBuddy(checkBox);
				hBoxLayout->addWidget(testLabel);
			}

			hBoxLayout->addStretch();
			vBoxLayout->addLayout(hBoxLayout);
			connect(checkBox, SIGNAL(stateChanged(int)), this, SLOT(stateChanged(int)));
		}
	}

	vBoxLayout->addStretch();

	this->setLayout(vBoxLayout);
}

const Task *TaskEditor::getTask() const
{
	return this->task;
}


void TaskEditor::paintEvent(QPaintEvent *paintEvent)
{
	QStyleOption option;
	option.init(this);
	QPainter painter(this);
	this->style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
}


void TaskEditor::stateChanged(int state)
{
	QCheckBox *checkBox = qobject_cast<QCheckBox*>(this->sender());
	if(checkBox == nullptr)
		return;
	Tests *tests = task->getTests();
	if(tests == nullptr)
		return;
	for(TestGroup *testGroup : tests->getTestGroupList())
	{
		if(testGroup->getName() == checkBox->text())
		{
			if(state == Qt::Checked)
				testGroup->setVisible(true);
			else
				testGroup->setVisible(false);
		}
	}
}


void TaskEditor::taskVisibilityStateChanged(int state)
{
	if(state == Qt::Checked)
		this->task->setVisible(true);
	else
		this->task->setVisible(false);
}

