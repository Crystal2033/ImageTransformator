/***************************************************************************
 *                                                                         *
 *   Copyright (C) 20.08.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "singlepixeltransforms.h"

SinglePixelTransforms::SinglePixelTransforms()
{

}

void SinglePixelTransforms::negativeTransformation(const QImage &image, ImageWidget *& imgWidget, Histogram *& hist) const
{
    QImage* transformedImage = new QImage(image);
    uchar* px = transformedImage->bits();
    const int pixelsQuo = image.width() * image.height();
    int newBrightness;
    for(int i = 0; i < pixelsQuo; ++i){
        newBrightness = BRIGHTNESS_MAX - *px - 1;
        *px++ = *px++ = *px++ = newBrightness;
        px += 1;
    }

    imgWidget->setImage(*transformedImage, transformedImage->size());
    hist->createHistogram(imgWidget->getImage(), imgWidget->size());
    imgWidget->repaint();
    hist->repaint();
    //imgWidget->setImage(*transformedImage, transformedImage->size());
    //Need to think about histogramm and visitor pattern

}

SinglePixelTransforms::~SinglePixelTransforms()
{

}
