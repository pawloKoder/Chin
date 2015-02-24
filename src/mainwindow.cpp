#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QAction>
#include <QFileDialog>
#include <QSettings>
#include "characterset.h"
#include "charactermatcher.h"
#include "matchercreationdialog.h"


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	initSettings();

	ui->setupUi(this);
	createConnections();

	scene = new QGraphicsScene();
	ui->view->setScene(scene);

	createMatcher();
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
	connect(ui->actionCharacter_set, &QAction::triggered, this, &MainWindow::matcherSettings);
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


void MainWindow::match(QImage img)
{
	QSettings settings;
	qreal size = settings.value("charSize").toDouble();
	qreal window_size = settings.value("windowSize").toDouble();

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


void MainWindow::initSettings(bool force)
{
	QSettings settings;

	auto setDefault = [&](const QString & key, const QVariant & value) {
		if (!settings.contains(key) || force)
			settings.setValue(key, value);
	};

	setDefault("charSize", 26);
	setDefault("windowSize", 14);
	setDefault("xblocks", 2);
	setDefault("yblocks", 2);
	settings.sync();
}


void MainWindow::createMatcher()
{
	QSettings settings;
	auto setType = settings.value("characterSet");
	CharacterSet set = CharacterSet::create(setType.value<CharacterSets>());
	matcher.reset(new CharacterMatcher(set, settings.value("xblocks").toInt(), settings.value("yblocks").toInt()));
}


void MainWindow::matcherSettings()
{

	MatcherCreationDialog dialog;
	if (dialog.exec()) {
		QSettings settings;
		settings.setValue("xblocks", dialog.xblocks());
		settings.setValue("yblocks", dialog.yblocks());
		settings.setValue("windowSize", dialog.windowSize());
		settings.setValue("characterSet",  qVariantFromValue(dialog.set()));
		settings.sync();
	}
	createMatcher();
}
