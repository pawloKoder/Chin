#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QAction>


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	createConnections();
}


MainWindow::~MainWindow()
{
	delete ui;
}


void MainWindow::createConnections()
{
	connect(ui->actionAbout_Qt, &QAction::triggered, [=](){QMessageBox::aboutQt(this);});
}
