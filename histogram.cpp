/***************************************************************************
 *                                                                         *
 *   Copyright (C) 15.08.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "histogram.h"
#include <QPaintEvent>

void Histogram::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    painter.begin(this);
    painter.drawPicture(0, 0, picture);
    painter.end();
}

void Histogram::paintHistogram()
{

    picture = QPicture();
    painter.begin(&picture);
    painter.setRenderHint(QPainter::Antialiasing, true);

    drawAxis();
    painter.setPen(histPen);

    for(int i = 0; i < BRIGHTNESS_MAX; ++i){
        if(histogram[i] != 0){
            painter.drawLine(i * histPen.width(), height(), i * histPen.width(), height() - ( (double)histogram[i]/maxHeight * height()) );
        }
    }
    painter.end();
    repaint();
}

void Histogram::clearHistogram()
{
    memset(histogram, 0, sizeof(histogram));
    maxHeight = 0;
}

void Histogram::drawAxis()
{
    painter.setPen(borderPen);
    painter.drawLine(0, 0, 0, height());
    painter.drawLine(width(), height(), 0, height());
    painter.translate(axisWidthShift/2, -axisWidthShift/2);

}

void Histogram::update(const QImage& img)
{
    createHistogram(img, img.size());
    repaint();
}


Histogram::Histogram(const QRect& screenSize, QWidget *parent) : QWidget(parent)
{

    histPen.setColor(Qt::darkCyan);
    histPen.setWidth(ceil((double)(screenSize.width() / (3 * BRIGHTNESS_MAX))));
    borderPen.setColor(Qt::black);
    borderPen.setWidth(4);
    axisWidthShift = borderPen.width();
    setFixedSize((double)histPen.width() * BRIGHTNESS_MAX, (double)screenSize.height() / 5);
    clearHistogram();
}

void Histogram::createHistogram(const QImage &img, const QSize& size)
{
    Q_UNUSED(size);

    clearHistogram();
    const uchar* px = img.bits();
    valueOfPixels = img.height() * img.width();
    //int r, g, b;
    int brightness;
    for(unsigned int i = 0; i < valueOfPixels; i++){
        //ImageFunctions::getRGB(const_cast<uchar*&>(px), r, g, b);
        //brightness = ImageFunctions::getBrightness(r, g, b);
        brightness = *px;
        px+=4;
        histogram[brightness]++;

        if (histogram[brightness] > maxHeight){
            maxHeight =  histogram[brightness];
        }
    }
    paintHistogram();
}

