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
    virtual void transform(const QImage &image, ImageWidget *& imgWidget) const override = 0 ;
    virtual ~SinglePixelTransforms() = default;
};

class NegativeTransform : public SinglePixelTransforms
{
public:
    NegativeTransform() = default;
    ~NegativeTransform() = default;
     void transform(const QImage &image, ImageWidget *& imgWidget) const override ;
};

#endif // TRANSFORMATIONS_H
