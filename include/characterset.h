#ifndef CHARACTERSET_H
#define CHARACTERSET_H


#include <QFont>
#include <QStringList>
#include <QMetaType>
#include <type_traits>


enum class CharacterSets {
	CHINESE_REDUCED,
	CHINESE,
	LATIN
};

QDataStream &operator<<(QDataStream &out, const CharacterSets &obj);
QDataStream &operator>>(QDataStream &in, CharacterSets &obj);

Q_DECLARE_METATYPE(CharacterSets);


class CharacterSet
{
public:
	CharacterSet(QFont font, QStringList characters);

	static CharacterSet chinese();
	static CharacterSet latin();
	static CharacterSet chineseSmall();
	static CharacterSet create(CharacterSets);

	QString value(int i) const;
	int count() const;
	QFont font() const;

private:
	QFont currentFont;
	QStringList characters;
};

#endif // CHARACTERSET_H
