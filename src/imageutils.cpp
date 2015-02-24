#include "imageutils.h"

#include <QDebug>


qreal imageUtils::getValueFromImage(QImage image, QRect region) {
	if (!region.isValid())
		region = image.rect();

	qreal value = 0.0;
	for (int x = region.left(); x < region.right(); ++x)
		for (int y = region.top(); y < region.bottom(); ++y)
			value += qGray(image.pixel(x, y));

	value /= region.width()*region.height();
	return value;
}
