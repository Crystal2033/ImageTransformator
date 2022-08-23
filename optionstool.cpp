/***************************************************************************
 *                                                                         *
 *   Copyright (C) 21.08.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "optionstool.h"
#include "histogram.h"

OptionsTool::~OptionsTool()
{
    delete options;
}

OptionsTool::OptionsTool(QWidget *parent) //addBuilder
{
    Q_UNUSED(parent);
    options = new TransformOptions();

    vertLayout = new QVBoxLayout(this);
    horConstantDataLay = new QHBoxLayout;
    constantLabel = new QLabel("Constant C");
    digitalGadget = new QLCDNumber;
    constantSlider = new QSlider(Qt::Orientation::Horizontal, this);

    acceptCancelHorLay = new QHBoxLayout();
    acceptBtn = new QPushButton("Accept");
    cancelBtn = new QPushButton("Cancel");


    horConstantDataLay->addWidget(constantLabel);
    horConstantDataLay->addWidget(digitalGadget, Qt::AlignCenter);
    vertLayout->addLayout(horConstantDataLay);
    vertLayout->addWidget(constantSlider, Qt::AlignCenter);

    horGammaConstantLay = new QHBoxLayout;
    gammaLabel = new QLabel("Gamma constant");
    digitalGadget2 = new QLCDNumber;
    gammaSlider = new QSlider(Qt::Orientation::Horizontal, this);
    horGammaConstantLay->addWidget(gammaLabel);
    horGammaConstantLay->addWidget(digitalGadget2, Qt::AlignCenter);
    vertLayout->addLayout(horGammaConstantLay);
    vertLayout->addWidget(gammaSlider, Qt::AlignCenter);

    acceptCancelHorLay->addWidget(acceptBtn);
    acceptCancelHorLay->addWidget(cancelBtn);
    vertLayout->addLayout(acceptCancelHorLay);

    setFixedSize(400, 200);

    constantSlider->setRange(0, BRIGHTNESS_MAX - 1);
    constantSlider->setTickPosition(QSlider::TicksBelow);
    constantSlider->setValue(BRIGHTNESS_MAX / 2);

    gammaSlider->setRange(1, 30);
    gammaSlider->setTickPosition(QSlider::TicksBelow);

    digitalGadget->display(constantSlider->value());

    connect(acceptBtn, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelBtn, SIGNAL(clicked()), this, SLOT(reject()));
    connect(constantSlider, SIGNAL(valueChanged(int)), this, SLOT(onConstantValueChanged(int)));
    connect(gammaSlider, SIGNAL(valueChanged(int)), this, SLOT(onGammaValueChanged(int)));
}

TransformOptions &OptionsTool::getOptions()
{
    return *options;
}

void OptionsTool::setTransformImageData(QImage *&image, ImageWidget *&imageWidget, SinglePixelTransforms* const& transformator)
{
    this->transformator = transformator;
    this->image = image;
    this->imageWidget = imageWidget;
}

void OptionsTool::setContrastSet()
{
    constantSlider->setRange(0, BRIGHTNESS_MAX - 1);
    constantLabel->setText("Contrast edge");
    constantLabel->show();
    digitalGadget->show();
    constantSlider->show();

    gammaLabel->hide();
    digitalGadget2->hide();
    gammaSlider->hide();
}

void OptionsTool::setLogarythmSet()
{
    constantSlider->setRange(0, BRIGHTNESS_MAX - 1);
    constantLabel->setText("Logarythm constant; y = C*ln(x)");
    constantSlider->setValue((BRIGHTNESS_MAX - 1)/qLn(BRIGHTNESS_MAX));
    digitalGadget->display(constantSlider->value());

    gammaLabel->hide();
    digitalGadget2->hide();
    gammaSlider->hide();
}

void OptionsTool::setGammaSet()
{
    constantSlider->setRange(1, 5);
    constantLabel->setText("Contrast edge");
    constantLabel->show();
    digitalGadget->show();
    constantSlider->show();

    gammaLabel->setText("Gamma value; y = C*x^g");
    gammaLabel->show();
    digitalGadget2->show();
    gammaSlider->show();
}

void OptionsTool::setAreaCutSet()
{
    //TODO!
}

void OptionsTool::onConstantValueChanged(int val)
{
    options->setConstant(val);
    digitalGadget->display(val);
    transformator->transform(*image, imageWidget, options);
}

void OptionsTool::onGammaValueChanged(int val)
{
    options->setGammaConst(val);
    digitalGadget2->display(val);
    transformator->transform(*image, imageWidget, options);
}
