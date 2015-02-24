#include "characterset.h"

#include <QFontDatabase>
#include <QFile>
#include <QDebug>
#include <QDirIterator>


QDataStream &operator<<(QDataStream &out, const CharacterSets &obj) {
	out << static_cast<typename std::underlying_type<CharacterSets>::type>(obj);
	return out;
}


QDataStream &operator>>(QDataStream &in, CharacterSets &obj) {
	in >> reinterpret_cast<typename std::underlying_type<CharacterSets>::type &>(obj);
	return in;
}


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


CharacterSet CharacterSet::latin()
{
	QFontDatabase fontDatabase;
	int f = fontDatabase.addApplicationFont(":/fonts/arial.ttf");
	QFont font = QFont(QFontDatabase::applicationFontFamilies(f).first(), 20);

	return CharacterSet(font, generateCharactersList(34, 126));
}


CharacterSet CharacterSet::create(CharacterSets type)
{
	switch(type) {
	case CharacterSets::CHINESE:
		return chinese();
	case CharacterSets::LATIN:
		return latin();
	case CharacterSets::CHINESE_REDUCED:
	default:
		return chineseSmall();
	}
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
