#pragma once
#include "main.h"
#include "Presentation.h"
#include "View/View.h"
#include "Editor/Editor.h"
#include "ScreenSwitch.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT;

public:
	MainWindow();
	MainWindow(const MainWindow &mainWindow) = delete;
	MainWindow &operator=(const MainWindow &mainWindow) = delete;
	~MainWindow();

	void openPresentationFromFile(const QString &fileName);
	void savePresentationToFile(const QString &fileName);

public slots:
	void openPresentation();
	void savePresentation();
	void closePresentation();
	void switchToView();
	void switchToEditor();
	void switchFullScreen();

private:
	Presentation *presentation;

	QMenuBar *menuBar;
	QAction *saveAction;
	QAction *closeAction;

	ScreenSwitch *screenSwitch;
	View *view;
	Editor *editor;
};
