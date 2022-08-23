/***************************************************************************
 *                                                                         *
 *   Copyright (C) 21.08.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef OPTIONSTOOL_H
#define OPTIONSTOOL_H

#include <QObject>
#include <QDialog>
#include <QBoxLayout>
#include <QLCDNumber>
#include <QSlider>
#include <QPushButton>
#include <QLabel>
#include <QScrollBar>
#include "transformoptions.h"
#include "imagewidget.h"
#include <QImage>
#include "transformations.h"


class OptionsTool : public QDialog
{
    Q_OBJECT
private:
    QHBoxLayout* horConstantDataLay = nullptr;
    QLabel* constantLabel = nullptr;
    QLCDNumber* digitalGadget = nullptr;
    QVBoxLayout* vertLayout = nullptr;
    QHBoxLayout* acceptCancelHorLay = nullptr;
    QPushButton* acceptBtn = nullptr;
    QPushButton* cancelBtn = nullptr;
    QSlider* constantSlider = nullptr;


    QHBoxLayout* horGammaConstantLay;
    QLabel* gammaLabel = nullptr;
    QLCDNumber* digitalGadget2 = nullptr;
    QSlider* gammaSlider = nullptr;


    TransformOptions* options = nullptr;
    SinglePixelTransforms* transformator = nullptr;
    ImageWidget* imageWidget = nullptr;
    QImage* image = nullptr;

    ~OptionsTool();

public:
    explicit OptionsTool(QWidget *parent = nullptr);
    TransformOptions& getOptions();
    void setTransformImageData(QImage*& image, ImageWidget*&  imageWidget, SinglePixelTransforms* const& transformator);

    void setContrastSet();
    void setLogarythmSet();
    void setGammaSet();
    void setAreaCutSet();


signals:

private slots:
    void onConstantValueChanged(int val);
    void onGammaValueChanged(int val);

};

#endif // OPTIONSTOOL_H
