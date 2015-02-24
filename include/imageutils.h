#ifndef IMAGEUTILS_H
#define IMAGEUTILS_H

#include <QImage>

namespace imageUtils
{
	qreal getValueFromImage(QImage image, QRect region = QRect());
}

#endif // IMAGEUTILS_H
