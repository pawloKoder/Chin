#include "charactermatcher.h"

#include <QChar>
#include <QGraphicsScene>
#include <QImage>
#include <QPainter>
#include <qmath.h>
#include "imageutils.h"


static QImage imageOfCharacter(const CharacterMatcher & matcher, int i) {
	QGraphicsScene scene;
	matcher.appendCharacter(&scene, i);

	scene.clearSelection();
	scene.setSceneRect(scene.itemsBoundingRect());
	QImage image(scene.sceneRect().size().toSize(), QImage::Format_ARGB32);
	image.fill(Qt::white);
	QPainter painter(&image);
	scene.render(&painter);

	return image;
}


QGraphicsTextItem * CharacterMatcher::appendCharacter(QGraphicsScene * scene,
		int c, QPointF pos) const {
	QString str = characters.value(c);
	QGraphicsTextItem * text = scene->addText(str, characters.font());
	text->setDefaultTextColor(Qt::black);
	text->setPos(pos);
	return text;
}


CharacterMatcher::CharacterMatcher(CharacterSet c, int N, int M):
	xblocks(N),
	yblocks(M),
	characters(c)
{
	computeBlockValues();
}


static QList<qreal> computeBlockValuesImpl(QImage image, int N ,int M)
{
	int charX = image.width() / N;
	int charY = image.height() / M;
	QRect windowChar = QRect(0, 0, charX, charY);

	QList<qreal> result;
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < M; ++j) {
			windowChar.moveTo(i * charX, j * charY);
			qreal b = imageUtils::getValueFromImage(image, windowChar);
			result.append(b);
		}
	return result;
}


static qreal scale(qreal v, qreal min1, qreal max1, qreal min2, qreal max2) {
	qreal base = (v - min1)/(max1-min1);
	return min2 + base * (max2 - min2);
}


void CharacterMatcher::computeBlockValues()
{
	images_of_characters.clear();
	for (int i = 0; i < characters.count(); ++i)
		images_of_characters.insert(i, imageOfCharacter(*this, i));

	block_values.resize(characters.count());
	for (int i = 0; i < characters.count(); ++i)
		block_values[i] = computeBlockValuesImpl(images_of_characters[i], xblocks, yblocks);

	qreal min = 255;
	qreal max = 0;
	for (auto block: block_values)
		for (auto value: block) {
			min = qMin(min, value);
			max = qMax(max, value);
		}

	for(auto & block: block_values)
		for(auto & value: block)
			value = scale(value, min, max, 0, 255);
}


int CharacterMatcher::bestFit(QImage image) const
{
	int best_fit = 0;
	qreal diff = 1000000.0;

	auto part = computeBlockValuesImpl(image, xblocks, yblocks);
	for (int i = 0; i < block_values.size(); ++i) {
		qreal current_diff = 0;
		auto p1 = block_values[i].begin();
		for (auto p2 = part.begin(); p2 != part.end(); ++p2, ++p1) {
			current_diff += (*p1 - *p2) * (*p1 - *p2);
		}
		current_diff = qSqrt(current_diff);

		if (current_diff < diff) {
			best_fit = i;
			diff = current_diff;
		}
	}

	return best_fit;
}

