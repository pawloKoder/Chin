#ifndef CHARACTERMATCHER_H
#define CHARACTERMATCHER_H

#include <QGraphicsItem>
#include <QPointF>
#include "characterset.h"


/**
 * @brief Class used to find characters approximating an image.
 *        An image will be splitted into blocks.
 */
class CharacterMatcher
{
public:
	/**
	 * @brief CharacterMatcher
	 * @param N Number of vertical blocks
	 * @param M Number of horizontal blocks
	 */
	CharacterMatcher(CharacterSet, int N, int M);

	/**
	 * @brief appendCharacter
	 * @param pos Position of character
	 * @param num Identifier of character
	 * @return An item of the scene
	 */
	QGraphicsTextItem * appendCharacter(QGraphicsScene *, int num, QPointF pos = QPointF()) const;

	int bestFit(QImage) const;

private:
	int xblocks;
	int yblocks;
	CharacterSet characters;

	QMap<int, QImage> images_of_characters;
	QVector<QList<qreal>> block_values;

	void computeBlockValues();
};

#endif // CHARACTERMATCHER_H
