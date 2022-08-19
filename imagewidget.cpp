/***************************************************************************
 *                                                                         *
 *   Copyright (C) 15.08.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "imagewidget.h"
#include "imagefunctions.h"
#include <QMessageBox>

ImageWidget::ImageWidget(QWidget *parent) : QWidget(parent)
{
    //painter = new QPainter(this);
    /* QPainter не наследуется от QObject и не имеет метода setParent.
     *  Т.е. он не включается в объектную иерархию.
     *  И его нужно удалять самостоятельно, если он создавался динамически (через new).
     *  Смысла выделять его в дин. памяти в текущей задаче нет.
    */
    img_ptr = nullptr;
    painter = new QPainter;
    this->setBackgroundRole(QPalette::Dark);
}

void ImageWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    if (!img_ptr) return;

    painter->begin(this);
    painter->drawImage(0, 0, *img_ptr);
    painter->end();
}

void ImageWidget::setImage(const QImage& img, const QSize& size)
{
    pictureSize = img.size();
    if(img_ptr != nullptr){
        delete img_ptr;
    }

    img_ptr = new QImage(img.scaled(size.width(), size.height(), Qt::KeepAspectRatio).copy());
    this->setFixedSize(img_ptr->width(), img_ptr->height());
    repaint();
}

QImage &ImageWidget::getImage()
{
    if(img_ptr){
        qDebug() << "all is ok" << Qt::endl;
        return *img_ptr;
    }
    qDebug() << "all not is ok" << Qt::endl;
    QMessageBox::critical(nullptr, "Image existance error", "You don`t have a result image to save it.");

}

QSize &ImageWidget::getPictureSize()
{
    return pictureSize;
}

ImageWidget::~ImageWidget()
{
    delete painter;
}


//QImage& ImageWidget::drawRect(const QImage& img)
//{
//    return ImageFunctions::fillRect(img);
//}

