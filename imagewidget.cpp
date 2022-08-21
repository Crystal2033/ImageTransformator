/***************************************************************************
 *                                                                         *
 *   Copyright (C) 15.08.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "imagewidget.h"
#include "imagefunctions.h"
#include "exceptions.h"
#include <QMessageBox>
#include <QListIterator>

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
    notify();
}

QImage *&ImageWidget::getImage()
{
    if(img_ptr){
        return img_ptr;
    }
    QMessageBox::critical(nullptr, "Image existance error", "You don`t have a result image to save it.");
    throw ImageExistanceError("There is no image in widget");

}

QSize &ImageWidget::getPictureSize()
{
    return pictureSize;
}

void ImageWidget::addObserver(InterfaceObserver *observer)
{
    observers.append(observer);
}

void ImageWidget::removeObserver(InterfaceObserver *observer)
{

    QList<InterfaceObserver*>::ConstIterator it = observers.constBegin();
    for ( ; it != observers.constEnd(); ++it ) {
        if(*it == observer){
            observers.erase(it);
            return;
        }
    }

    qDebug() << "Observer wasn`t found" << Qt::endl;
}

void ImageWidget::notify()
{
    repaint();
    for(auto obs : observers){
        obs->update(*img_ptr);
    }
}

ImageWidget::~ImageWidget()
{
    for(auto obs : observers){
        removeObserver(obs);
    }
    delete painter;
}


//QImage& ImageWidget::drawRect(const QImage& img)
//{
//    return ImageFunctions::fillRect(img);
//}

