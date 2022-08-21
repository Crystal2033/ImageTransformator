/***************************************************************************
 *                                                                         *
 *   Copyright (C) 20.08.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "transformations.h"

void NegativeTransform::transform(const QImage &image, ImageWidget *&imgWidget) const
{
    QImage* transformedImage = new QImage(image);
    uchar* px = transformedImage->bits();
    const int pixelsQuo = image.width() * image.height();
    int newBrightness;
    for(int i = 0; i < pixelsQuo; ++i){
        newBrightness = BRIGHTNESS_MAX - *px - 1;
        *px++ = *px++ = *px++ = newBrightness;
        px++;
    }
    imgWidget->setImage(*transformedImage, transformedImage->size());
}
