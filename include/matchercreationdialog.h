#ifndef MATCHERCREATIONDIALOG_H
#define MATCHERCREATIONDIALOG_H


#include <QDialog>
#include "characterset.h"


namespace Ui {
class MatcherCreationDialog;
}

class MatcherCreationDialog : public QDialog
{
	Q_OBJECT
	
public:
	explicit MatcherCreationDialog(QWidget *parent = 0);
	~MatcherCreationDialog();

	int xblocks();
	int yblocks();
	int windowSize();
	CharacterSets set();
	
private:
	Ui::MatcherCreationDialog *ui;
};

#endif // MATCHERCREATIONDIALOG_H
