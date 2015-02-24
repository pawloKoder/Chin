#include "include/matchercreationdialog.h"
#include "ui_matchercreationdialog.h"

#include <QSettings>


MatcherCreationDialog::MatcherCreationDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::MatcherCreationDialog)
{
	ui->setupUi(this);
	QSettings settings;
	ui->xblocks->setValue(settings.value("xblocks").toInt());
	ui->yblocks->setValue(settings.value("yblocks").toInt());
	ui->window_size->setValue(settings.value("windowSize").toInt());

	switch(settings.value("characterSet").value<CharacterSets>()) {
	case CharacterSets::CHINESE:
		ui->set->setCurrentIndex(1);
		break;
	case CharacterSets::LATIN:
		ui->set->setCurrentIndex(2);
		break;
	case CharacterSets::CHINESE_REDUCED:
	default:
		ui->set->setCurrentIndex(0);
		break;
	}
}


MatcherCreationDialog::~MatcherCreationDialog()
{
	delete ui;
}


int MatcherCreationDialog::xblocks()
{
	return ui->xblocks->value();
}


int MatcherCreationDialog::yblocks()
{
	return ui->yblocks->value();
}


int MatcherCreationDialog::windowSize()
{
	return ui->window_size->value();
}


CharacterSets MatcherCreationDialog::set()
{
	switch(ui->set->currentIndex()) {
	case 1:
		return CharacterSets::CHINESE;
	case 2:
		return CharacterSets::LATIN;
	case 0:
	default:
		return CharacterSets::CHINESE_REDUCED;
	}
}
