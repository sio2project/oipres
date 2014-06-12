#pragma once
#include "../main.h"
#include "../Presentation.h"
#include "TaskEditor.h"
#include "OptionsEditor.h"

class TabsEditor : public QTabWidget
{
	Q_OBJECT;

public:
	TabsEditor(Presentation *presentation, QWidget *parent = nullptr);

	const Presentation *getPresentation() const;
	
private:
	Presentation *presentation;
};
