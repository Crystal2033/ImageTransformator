/***************************************************************************
 *                                                                         *
 *   Copyright (C) 20.08.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include <imagewidget.h>
#include <QObject>
#include <QWidget>

class Transformations
{
public:
    virtual ~Transformations() = default;
    virtual void transform(const QImage &image, ImageWidget *& imgWidget) const = 0;
};

class SinglePixelTransforms : public Transformations
{
public:
    SinglePixelTransforms() = default;
    void transform(const QImage &image, ImageWidget *& imgWidget) const override ;
    ~SinglePixelTransforms() = default;
};

#endif // TRANSFORMATIONS_H
