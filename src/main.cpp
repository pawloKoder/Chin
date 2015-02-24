#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QCoreApplication::setOrganizationName("Pawlo");
	QCoreApplication::setApplicationName("Chin");

	MainWindow w;
	w.show();


	return a.exec();
}
