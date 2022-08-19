/***************************************************************************
 *                                                                         *
 *   Copyright (C) 15.08.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef HISTOGRAM_H
#define HISTOGRAM_H
#define BRIGHTNESS_MAX 256

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QPicture>
#include "imagefunctions.h"

class Histogram : public QWidget
{
    Q_OBJECT
private:
    unsigned int histogram[BRIGHTNESS_MAX];
    unsigned int maxHeight, valueOfPixels;
    QPainter painter;
    QPicture picture;
    QPen histPen, borderPen;
    int horShift=20, vertShift=20, axisWidthShift;

    void paintEvent(QPaintEvent *event);
    void paintHistogram();

    void drawAxis();

public:
    explicit Histogram(QWidget *parent = nullptr);
    void createHistogram(const QImage& img, const QSize& size);

signals:

};

#endif // HISTOGRAM_H
