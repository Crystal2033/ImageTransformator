/***************************************************************************
 *                                                                         *
 *   Copyright (C) 20.08.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "transformations.h"

unsigned int SinglePixelTransforms::transformationHook(uchar *&px, TransformOptions * const &options) const
{
    Q_UNUSED(px);
    Q_UNUSED(options);
    return 0;
}

void SinglePixelTransforms::transform(const QImage &image, ImageWidget *&imgWidget, TransformOptions * const &options) const
{
    QImage* transformedImage = new QImage(image);
    uchar* px = transformedImage->bits();
    const int pixelsQuo = image.width() * image.height();
    int newBrightness;
    for(int i = 0; i < pixelsQuo; ++i){
        newBrightness = transformationHook(px, options);
        *px++ = *px++ = *px++ = newBrightness;
        px++;
    }

    imgWidget->setImage(*transformedImage, transformedImage->size());
}


unsigned int NegativeTransform::transformationHook(uchar *&px, TransformOptions * const &options) const
{
    Q_UNUSED(options);
    return BRIGHTNESS_MAX - *px - 1;
}


unsigned int ContrastTransform::transformationHook(uchar *&px, TransformOptions * const &options) const
{
    return (*px > options->getConstant()) ? BRIGHTNESS_MAX - 1 : *px;
}
