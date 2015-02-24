#include "characterset.h"

#include <QFontDatabase>
#include <QFile>
#include <QDebug>
#include <QDirIterator>


CharacterSet::CharacterSet(QFont font, QStringList c) :
	currentFont(font),
	characters(c)
{}


static QStringList generateCharactersList(int begin, int end)
{
	QStringList result;
	for (int i = begin; i < end; ++i) {
		QString c = QChar(i);
		result.append(c);
	}
	return result;
}


CharacterSet CharacterSet::chinese()
{
	QFontDatabase fontDatabase;
	int f = fontDatabase.addApplicationFont(":/fonts/wt006.ttf");
	QFont font = QFont(QFontDatabase::applicationFontFamilies(f).first(), 20);

	return CharacterSet(font, generateCharactersList(19968, 40869));
}


CharacterSet CharacterSet::chineseSmall()
{
	QFontDatabase fontDatabase;
	int f = fontDatabase.addApplicationFont(":/fonts/wt006.ttf");
	QFont font = QFont(QFontDatabase::applicationFontFamilies(f).first(), 20);

	return CharacterSet(font, generateCharactersList(19968, 24869));
}


QString CharacterSet::value(int i) const
{
	return characters.value(i);
}


int CharacterSet::count() const
{
	return characters.size();
}


QFont CharacterSet::font() const
{
	return currentFont;
}
