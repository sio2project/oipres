#include "main.h"
#include "MainWindow.h"

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	int fontID = QFontDatabase::addApplicationFont(":/res/Monospace.ttf");
	QString family = QFontDatabase::applicationFontFamilies(fontID).at(0);
	QFont monospaceFont(family);
	QApplication::setFont(monospaceFont);

	MainWindow window;
	window.show();

	return app.exec();
}
