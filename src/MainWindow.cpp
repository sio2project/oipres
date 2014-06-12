#include "MainWindow.h"
#include "Parser/XmlReader.h"
#include "WritePresentation.h"

const QString menuPresentationString = QString::fromUtf8("Prezentacja");
const QString menuCloseString = QString::fromUtf8("Zamknij prezentację");
const QString menuOpenString = QString::fromUtf8("Otwórz z pliku");
const QString menuSaveString = QString::fromUtf8("Zapisz do pliku");
const QString menuOpenFileString = QString::fromUtf8("Otwórz plik...");
const QString menuSaveFileString = QString::fromUtf8("Zapisz do pliku...");
const QString menuQuitString = QString::fromUtf8("Zakończ program");

const QString menuSwitchString = QString::fromUtf8("Widok");
const QString menuSwitchToViewString = QString::fromUtf8("Prezentacja");
const QString menuSwitchToEditorString = QString::fromUtf8("Edytor");
const QString menuSwitchFullScreenString = QString::fromUtf8("Pełny ekran");

const QString savePresentationCannotOpenFile = QString::fromUtf8("Otworzenie wybranego pliku w celu zapisu jest niemożliwe.");

const int mainWindowDefaultWidth = 500;
const int mainWindowDefaultHeight = 450;

MainWindow::MainWindow() : QMainWindow(), presentation(nullptr), screenSwitch(nullptr), view(nullptr), editor(nullptr)
{
	this->menuBar = new QMenuBar(this);

	this->screenSwitch = new ScreenSwitch(this);

	this->view = new View(screenSwitch);
	this->editor = new Editor(screenSwitch);
	this->screenSwitch->addScreen(this->view);
	this->screenSwitch->addScreen(this->editor);

	// Presentation menu
	this->closeAction = new QAction(menuCloseString, this->menuBar);
	this->closeAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Q));
	connect(this->closeAction, SIGNAL(triggered()), this, SLOT(closePresentation()));
	this->addAction(this->closeAction);
	this->closeAction->setEnabled(false);

	QAction *quitAction = new QAction(menuQuitString, this->menuBar);
	connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));
	this->addAction(quitAction);

	QAction *openAction = new QAction(menuOpenString, this->menuBar);
	openAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));
	connect(openAction, SIGNAL(triggered()), this, SLOT(openPresentation()));
	this->addAction(openAction);

	this->saveAction = new QAction(menuSaveString, this->menuBar);
	this->saveAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));
	connect(this->saveAction, SIGNAL(triggered()), this, SLOT(savePresentation()));
	this->addAction(this->saveAction);
	this->saveAction->setEnabled(false);

	QActionGroup *switchBetweenViewAndEditor = new QActionGroup(this->menuBar);
	switchBetweenViewAndEditor->setExclusive(true);

	QAction *switchToView = new QAction(menuSwitchToViewString, switchBetweenViewAndEditor);
	switchToView->setShortcut(Qt::Key_V);
	connect(switchToView, SIGNAL(triggered()), this, SLOT(switchToView()));
	switchToView->setCheckable(true);
	switchToView->setChecked(true);
	this->addAction(switchToView);

	switchBetweenViewAndEditor->addAction(switchToView);

	QAction *switchToEditor = new QAction(menuSwitchToEditorString, switchBetweenViewAndEditor);
	switchToEditor->setShortcut(Qt::Key_E);
	connect(switchToEditor, SIGNAL(triggered()), this, SLOT(switchToEditor()));
	switchToEditor->setCheckable(true);
	this->addAction(switchToEditor);

	QAction *fullScreen = new QAction(menuSwitchFullScreenString, this->menuBar);
	fullScreen->setShortcut(Qt::Key_F11);
	connect(fullScreen, SIGNAL(triggered()), this, SLOT(switchFullScreen()));
	fullScreen->setCheckable(true);
	this->addAction(fullScreen);

	switchBetweenViewAndEditor->addAction(switchToEditor);

	QMenu *presentationMenu = this->menuBar->addMenu(menuPresentationString);
	presentationMenu->addAction(openAction);
	presentationMenu->addAction(this->saveAction);
	presentationMenu->addAction(this->closeAction);
	presentationMenu->addAction(quitAction);

	QMenu *switchMenu = this->menuBar->addMenu(menuSwitchString);
	switchMenu->addAction(switchToView);
	switchMenu->addAction(switchToEditor);
	switchMenu->addAction(fullScreen);

	// View menu
	this->view->configureViewMenu(this->menuBar->addMenu(""));

	this->setMenuBar(this->menuBar);

	this->setCentralWidget(screenSwitch);
	this->screenSwitch->switchTo((QWidget*) this->view);

	this->resize(mainWindowDefaultWidth, mainWindowDefaultHeight);
}

MainWindow::~MainWindow()
{
	if(this->presentation != nullptr)
		delete this->presentation;
}


void MainWindow::openPresentationFromFile(const QString &fileName)
{
	this->view->setPresentation(nullptr);

	if(this->presentation != nullptr)
		delete this->presentation;

	this->presentation = new Presentation();
	if(!parseXmlFile(fileName, this->presentation))
	{
		delete this->presentation;
		this->presentation = nullptr;
	}

	if(this->screenSwitch->isSwitchedTo(this->view))
		this->view->setPresentation(this->presentation);
	this->editor->setPresentation(this->presentation);

	if(this->presentation != nullptr)
	{
		this->saveAction->setEnabled(true);
		this->closeAction->setEnabled(true);
	}
}

void MainWindow::savePresentationToFile(const QString &fileName)
{
	QFile file(fileName);
	if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QMessageBox msgBox;
		msgBox.setText(savePresentationCannotOpenFile);
		msgBox.exec();
		return;
	}
	QTextStream out(&file);
	writePresentation(this->presentation, out);
	file.close();
}


void MainWindow::closePresentation()
{
	if(this->presentation == nullptr)
		return;
	this->view->setPresentation(nullptr);
	this->editor->setPresentation(nullptr);
	delete this->presentation;
	this->presentation = nullptr;
	this->saveAction->setEnabled(false);
	this->closeAction->setEnabled(false);
}


void MainWindow::openPresentation()
{
	QString fileName = QFileDialog::getOpenFileName(this, menuOpenFileString, QString(), "");
	if(fileName != "")
		this->openPresentationFromFile(fileName);
}

void MainWindow::savePresentation()
{
	if(this->presentation == nullptr)
		return;
	QString fileName = QFileDialog::getSaveFileName(this, menuSaveFileString, QString(), "");
	if(fileName != "")
		this->savePresentationToFile(fileName);
}

void MainWindow::switchToView()
{
	this->view->setPresentation(this->presentation);
	this->view->enableMenu();
	this->screenSwitch->switchTo((QWidget*) this->view);
}

void MainWindow::switchToEditor()
{
	this->view->disableMenu();
	this->view->setPresentation(nullptr);
	this->screenSwitch->switchTo((QWidget*) this->editor);
}

void MainWindow::switchFullScreen()
{
	if(this->isFullScreen())
	{
		this->showNormal();
		this->menuBar->setVisible(true);
	}
	else
	{
		this->showFullScreen();
		this->menuBar->setVisible(false);
	}
}
