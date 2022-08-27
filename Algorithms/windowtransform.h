/***************************************************************************
 *                                                                         *
 *   Copyright (C) 27.08.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef WINDOWTRANSFORM_H
#define WINDOWTRANSFORM_H
#include <QVector>
#include <QImage>
#include "MainWidgets/imagewidget.h"
typedef enum { AVERAGE, GAUSS, MEDIAN, LAPLASS, GRADIENT } TransformMatrixes;

class WindowTransform
{
private:
    QVector<QVector<int>> matrix;
    double matrixCoeff;
public:
    WindowTransform(const TransformMatrixes type);
    void transform(const QImage& image, ImageWidget*& imageWidget);

};

#endif // WINDOWTRANSFORM_H
