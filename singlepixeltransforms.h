/***************************************************************************
 *                                                                         *
 *   Copyright (C) 20.08.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef SINGLEPIXELTRANSFORMS_H
#define SINGLEPIXELTRANSFORMS_H

#include <imagewidget.h>
#include <QObject>
#include <QWidget>

class SinglePixelTransforms
{
public:
    SinglePixelTransforms();
    void negativeTransformation(const QImage &image, ImageWidget *& imgWidget, Histogram *& hist) const;
    ~SinglePixelTransforms();
};

#endif // SINGLEPIXELTRANSFORMS_H
