#include "charactermatcher.h"

#include <QChar>
#include <QGraphicsScene>
#include <QImage>
#include <QPainter>
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
	min_value = 255;
	max_value = 0;

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


void CharacterMatcher::computeBlockValues()
{
	images_of_characters.clear();
	for (int i = 0; i < characters.count(); ++i)
		images_of_characters.insert(i, imageOfCharacter(*this, i));

	block_values.resize(characters.count());
	for (int i = 0; i < characters.count(); ++i)
		block_values[i] = computeBlockValuesImpl(images_of_characters[i], xblocks, yblocks);
}
