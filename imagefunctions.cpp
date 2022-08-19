/***************************************************************************
 *                                                                         *
 *   Copyright (C) 15.08.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "imagefunctions.h"
using namespace ImageFunctions;

void ImageFunctions::setPixColor(uchar*& pix, int r, int g, int b)
{
    *pix = r;
    *++pix = g;
    *++pix = b;
    pix+=2;

}

//QImage& ImageFunctions::fillRect(const QImage& img)
//{
//    QImage* copy_image = new QImage(img.copy());
//    uchar *px = copy_image->bits();

//    int h = copy_image->height();
//    int w = copy_image->width();
//    qDebug() << w << Qt::endl;
//    qDebug() << h << Qt::endl;

//    //int pixelsQuo = h * w;
//    int rect_w = 100;
//    int rect_h = 400;
//    int rectArea = rect_w * rect_h;
//    uchar* startpos = px + 100*4*w + 30*4; //x = 30, y = 100 перенос указателя на начальную позицию прямоугольника (лев вер угол)

//    int line_counter = 0;
//     qDebug() << sizeof (int) << Qt::endl; // 4байта

//    for(int i = 0; i < rectArea; i++)
//    {
//        if (line_counter < rect_w) // иду по строке
//        {//отрисовка линии размером 100 серых пискелей
//            setPixColor(startpos, 0,255, 0);
//            line_counter++;
//        }
//        else
//        {
//            line_counter = 0;
//            startpos = startpos + w*4 - rect_w*4;
//            setPixColor(startpos, 0, 255, 0);
//            line_counter++;
//        }

//    }
//    return *copy_image;
//}

QImage& ImageFunctions::setToBrightnessMap(const QImage& img)
{
    QImage* copy_image = new QImage(img.copy());
    uchar *px = copy_image->bits();

    int h = img.height();
    int w = img.width();

    int pixelsQuo = h * w;

    int r, g, b;
    int brightness = 0;
    for (int i = 0; i < pixelsQuo; i++)
    {
        getRGB(px, r, g, b);
        px -= 4;

        brightness = getBrightness(r, g, b);

        *px = brightness;
        *++px = brightness;
        *++px = brightness;

        px += 2;
    }
    return *copy_image;
}

int ImageFunctions::getBrightness(const int r, const int g, const int b)
{
    int brightness = 0.3*r+0.59*g+0.11*b;
    if((brightness > BRIGHTNESS_MAX - 1) || (brightness < 0)){
        qDebug() << "brightness error. Brightness =  " << brightness;
        qDebug() << "r; g; b = "<<r << "; " << g << "; "<< b <<".";
        exit(-110);
    }
    return brightness;
}

void ImageFunctions::getRGB(uchar *&px, int &r, int &g, int &b)
{
    r = *px;
    g = *++px;
    b = *++px;
    px+=2;
}
