/***************************************************************************
 *                                                                         *
 *   Copyright (C) 15.08.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef IMAGEFUNCTIONS_H
#define IMAGEFUNCTIONS_H
#include<QImage>
#include<QDebug>
#include "histogram.h"


namespace ImageFunctions {
    QImage& setToBrightnessMap(const QImage &img);
    int getBrightness(const int r, const int g, const int b);
    void getRGB(uchar*& px, int& r, int& g, int& b);
    //QImage& fillRect(const QImage& img);
    void setPixColor(uchar*& pix, int r, int g, int b);

}

#endif // IMAGEFUNCTIONS_H
