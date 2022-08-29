/***************************************************************************
 *                                                                         *
 *   Copyright (C) 29.08.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef FOURIERTRANSFORM_H
#define FOURIERTRANSFORM_H

#include "MainWidgets/imagewidget.h"
#include <QImage>
#include "MenuAndTools/transformoptions.h"
#include "ImageMiscellaneous/imagefunctions.h"
#include <complex>
#include <cmath>
#include <iostream>
#include <QProgressBar>
using namespace std::complex_literals;


class FourierTransform
{
private:
    QProgressBar* progressBar = nullptr;
    int makeFourierTransform(const QImage& image, const int u, const int v) const;
public:
    FourierTransform();
    void transform(const QImage &image, ImageWidget *& imgWidget, TransformOptions* const& options = nullptr) const;
};

#endif // FOURIERTRANSFORM_H
