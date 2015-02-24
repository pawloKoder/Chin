#ifndef CHARACTERSET_H
#define CHARACTERSET_H


#include <QFont>
#include <QStringList>


class CharacterSet
{
public:
	CharacterSet(QFont font, QStringList characters);

	static CharacterSet chinese();
	static CharacterSet chineseSmall();

	QString value(int i) const;
	int count() const;
	QFont font() const;

private:
	QFont currentFont;
	QStringList characters;
};

#endif // CHARACTERSET_H
