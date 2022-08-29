/***************************************************************************
 *                                                                         *
 *   Copyright (C) 29.08.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "fouriertransform.h"

int FourierTransform::makeFourierTransform(const QImage& image,  const int u, const int v) const
{
    std::complex<double> result = 0.0;
    double pixelRes = 0.0;
    uchar* px = const_cast<uchar*>(image.bits());
    for(int x = 0; x < image.height(); x++)
    {
        for(int y = 0; y < image.width(); y++)
        {
            result = result + double(*ImageFunctions::getPixByIndexes(px, x, y, image.width()))
                    * std::exp(-2i*M_PI *
                               ((u*x)/double(image.height()) + (v*y)/double(image.width())));
        }
    }
    pixelRes = std::sqrt(std::pow(result.real(), 2) + std::pow(result.imag(), 2));
    return ((int)pixelRes > BRIGHTNESS_MAX - 1) ? BRIGHTNESS_MAX - 1 : (int)pixelRes;

}

FourierTransform::FourierTransform()
{
    //progressBar = new QProgressBar();
}

void FourierTransform::transform(const QImage &image, ImageWidget *&imgWidget, TransformOptions * const &options) const
{
    Q_UNUSED(options);
    qDebug() << "Transforming..." << Qt::endl;
    QImage* transformedImage = new QImage(image);
    uchar* px = transformedImage->bits();
    int newBrightness;
    int currentProgress = 0;
    for(int u = 0; u < image.height(); u++)
    {
        for(int v = 0; v < image.width(); v++)
        {
            newBrightness = makeFourierTransform(image, u, v);
            *px++ = *px++ = *px++ = newBrightness;
            px++;
            currentProgress++;

        }
    }
    qDebug() << "Done." << Qt::endl;
    imgWidget->setImage(*transformedImage, transformedImage->size());
    delete transformedImage;
}
