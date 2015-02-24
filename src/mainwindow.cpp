#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QAction>
#include <QFileDialog>
#include <QSettings>
#include "characterset.h"
#include "charactermatcher.h"


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	createConnections();

	scene = new QGraphicsScene();
	ui->view->setScene(scene);

	CharacterSet set = CharacterSet::chineseSmall();
	matcher.reset(new CharacterMatcher(set, 2, 2));
}


MainWindow::~MainWindow()
{
	delete ui;
}


void MainWindow::createConnections()
{
	connect(ui->actionAbout_Qt, &QAction::triggered, [=](){QMessageBox::aboutQt(this);});
	connect(ui->action_Open_Image, &QAction::triggered, this, &MainWindow::loadImage);
	connect(ui->action_Save_Image, &QAction::triggered, this, &MainWindow::saveImage);
}


void MainWindow::loadImage()
{
	QSettings settings;
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open Image"), settings.value("path").toString(), tr("Image Files (*.png *.jpg *.bmp)"));

	if (fileName.isEmpty())
		return;

	QFileInfo nfo(fileName);
	settings.setValue("path", nfo.path());

	match(QImage(fileName));
}


void MainWindow::saveImage()
{
	QSettings settings;
	QString fileName = QFileDialog::getSaveFileName(this,
		tr("Open Image"), settings.value("path").toString(), tr("Image Files (*.png *.jpg *.bmp)"));

	if (fileName.isEmpty())
		return;

	QFileInfo nfo(fileName);
	settings.setValue("path", nfo.path());

	scene->clearSelection();
	scene->setSceneRect(scene->itemsBoundingRect());
	QImage image(scene->sceneRect().size().toSize(), QImage::Format_ARGB32);
	image.fill(Qt::white);

	QPainter painter(&image);
	scene->render(&painter);
	image.save(fileName);
}


void MainWindow::match(QImage img) {
	//TODO Remove magic numbers
	qreal size = 26;
	qreal window_size = 14;

	scene->clear();
	int W = img.width() / window_size;
	int H = img.height() / window_size;
	for (int i = 0; i < W; ++i){
		for (int j = 0; j < H; ++j) {
			QRect window = QRect(i * window_size, j * window_size, window_size, window_size);
			//TODO: Remove copying image.
			QImage subimage = img.copy(window);
			matcher->appendCharacter(scene, matcher->bestFit(subimage), QPointF(i * size, j * size));
		}
	}
}
