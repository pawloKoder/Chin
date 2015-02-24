#include "include/matchercreationdialog.h"
#include "ui_matchercreationdialog.h"

MatcherCreationDialog::MatcherCreationDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::MatcherCreationDialog)
{
	ui->setupUi(this);
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
