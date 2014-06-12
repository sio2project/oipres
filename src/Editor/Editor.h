#pragma once
#include "../main.h"
#include "../Presentation.h"
#include "TabsEditor.h"

class Editor : public QWidget
{
	Q_OBJECT;

public:
	Editor(QWidget *parent = nullptr);

	void setPresentation(Presentation *newPresentation);

	const Presentation *getPresentation() const;

	void paintEvent(QPaintEvent *paintEvent) override;
	void resizeEvent(QResizeEvent *resizeEvent) override;
	
private:
	Presentation *presentation;
	TabsEditor *tabsEditor;
};
