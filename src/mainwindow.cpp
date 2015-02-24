#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QAction>
#include "characterset.h"


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	createConnections();

	CharacterSet set = CharacterSet::chineseSmall();
}


MainWindow::~MainWindow()
{
	delete ui;
}


void MainWindow::createConnections()
{
	connect(ui->actionAbout_Qt, &QAction::triggered, [=](){QMessageBox::aboutQt(this);});
}
