#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <QMainWindow>
#include <QGraphicsScene>
#include "charactermatcher.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void loadImage();
	void saveImage();
	void matcherSettings();

private:
	Ui::MainWindow *ui;
	QGraphicsScene * scene;
	std::unique_ptr<CharacterMatcher> matcher;

	void createConnections();
	void match(QImage);
	void initSettings(bool force = false);
	void createMatcher();
};

#endif // MAINWINDOW_H
