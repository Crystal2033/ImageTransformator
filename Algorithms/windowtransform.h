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
#include "MenuAndTools/transformoptions.h"
#define MIN_WINDOW_SIZE 3
typedef enum { AVERAGE, GAUSS, MEDIAN, LAPLASS, GRADIENT } TransformMatrixes;

class WindowTransform
{
private:
    TransformMatrixes matrixType;
    QVector<QVector<double>> matrix;
    double averageMatrixCoeff = 1.0;
    void setMatrixOptions(const int matrixSize, const int mode);
    void createWindowTransfOnPix(const QImage& originalImage, QImage& image, const int i, const int j);
    uchar* getPixByWindow(uchar* startImagePx, const int i, const int j, const int k, const int p, const QSize& size) const;
    void clearMatrix();
    void setMatrixSize(const int matrixSize);
    double gauss(const int gamma, const int x, const int y);
public:
    WindowTransform(const TransformMatrixes type);
    void transform(const QImage& image, ImageWidget*& imageWidget, const TransformOptions* options = nullptr);


};

#endif // WINDOWTRANSFORM_H
