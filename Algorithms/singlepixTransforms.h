/***************************************************************************
 *                                                                         *
 *   Copyright (C) 20.08.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef SINGLEPIXTRANSFORMS_H
#define SINGLEPIXTRANSFORMS_H

#include "MainWidgets/imagewidget.h"
#include <QObject>
#include <QWidget>
#include "MenuAndTools/transformoptions.h"
#include <QtMath>

#define GAMMA_COEFF 25

class SinglePixelTransforms
{
public:
    SinglePixelTransforms() = default;
    virtual unsigned int transformationHook(uchar*& px, TransformOptions* const& options = nullptr) const;
    virtual void transform(const QImage &image, ImageWidget *& imgWidget, TransformOptions* const& options = nullptr) const;
    virtual ~SinglePixelTransforms() = default;
};

class NegativeTransform : public SinglePixelTransforms
{
public:
    NegativeTransform() = default;
    ~NegativeTransform() = default;
    unsigned int transformationHook(uchar*& px, TransformOptions* const& options = nullptr) const override;
    //void transform(const QImage &image, ImageWidget *& imgWidget, TransformOptions* const& options = nullptr) const override ;
};

class ContrastTransform : public SinglePixelTransforms
{
public:
    ContrastTransform() = default;
    ~ContrastTransform() = default;
    unsigned int transformationHook(uchar*& px, TransformOptions* const& options = nullptr) const override;
     //void transform(const QImage &image, ImageWidget *& imgWidget, TransformOptions* const& options = nullptr) const override ;
};

class LogarythmTransform : public SinglePixelTransforms
{
public:
    LogarythmTransform() = default;
    ~LogarythmTransform() = default;
    unsigned int transformationHook(uchar*& px, TransformOptions* const& options = nullptr) const override;
     //void transform(const QImage &image, ImageWidget *& imgWidget, TransformOptions* const& options = nullptr) const override ;
};

class GammaCorrection : public SinglePixelTransforms
{
public:
    GammaCorrection() = default;
    ~GammaCorrection() = default;
    unsigned int transformationHook(uchar*& px, TransformOptions* const& options = nullptr) const override;
     //void transform(const QImage &image, ImageWidget *& imgWidget, TransformOptions* const& options = nullptr) const override ;
};

class AreaCutting : public SinglePixelTransforms
{
public:
    AreaCutting() = default;
    ~AreaCutting() = default;
    unsigned int transformationHook(uchar*& px, TransformOptions* const& options = nullptr) const override;
     //void transform(const QImage &image, ImageWidget *& imgWidget, TransformOptions* const& options = nullptr) const override ;
};

#endif // SINGLEPIXTRANSFORMS_H
