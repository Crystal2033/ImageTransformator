/***************************************************************************
 *                                                                         *
 *   Copyright (C) 15.08.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H


#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QDebug>
#include "histogram.h"


class ImageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ImageWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent* event);
    void setImage(const QImage& img, const QSize& size);
    QImage& getImage();
    QImage& drawRect(const QImage& img);
    QSize& getPictureSize();
    ~ImageWidget();


private:
    QPainter* painter = nullptr;
    QImage* img_ptr = nullptr;
    QSize pictureSize;

signals:

};

#endif // IMAGEWIDGET_H
