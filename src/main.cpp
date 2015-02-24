#include "mainwindow.h"
#include <QApplication>

#include "characterset.h"

int main(int argc, char *argv[])
{
	qRegisterMetaTypeStreamOperators<CharacterSets>("CharacterSets");

	QApplication a(argc, argv);

	QCoreApplication::setOrganizationName("Pawlo");
	QCoreApplication::setApplicationName("Chin");

	MainWindow w;
	w.show();


	return a.exec();
}
