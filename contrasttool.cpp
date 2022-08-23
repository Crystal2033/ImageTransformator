/***************************************************************************
 *                                                                         *
 *   Copyright (C) 21.08.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "contrasttool.h"
#include "histogram.h"

ContrastTool::~ContrastTool()
{
    delete options;
}

ContrastTool::ContrastTool(QWidget *parent)
{
    Q_UNUSED(parent);
    options = new TransformOptions();

    vertLayout = new QVBoxLayout(this);
    horDataLayout = new QHBoxLayout();
    dataLabel = new QLabel("Contrast edge");
    digitalGadget = new QLCDNumber();
    slider = new QSlider(Qt::Orientation::Horizontal, this);

    //horBtnsLayout = new QHBoxLayout();
    //acceptBtn = new QPushButton("Accept");
    //cancelBtn = new QPushButton("Cancel");

    horDataLayout->addWidget(dataLabel);
    horDataLayout->addWidget(digitalGadget, Qt::AlignCenter);
    vertLayout->addLayout(horDataLayout);
    vertLayout->addWidget(slider, Qt::AlignCenter);
    //horBtnsLayout->addWidget(acceptBtn);
    //horBtnsLayout->addWidget(cancelBtn);
    vertLayout->addLayout(horBtnsLayout);
    setFixedSize(300, 150);

    slider->setRange(0, BRIGHTNESS_MAX - 1);
    slider->setTickPosition(QSlider::TicksBelow);
    slider->setValue(BRIGHTNESS_MAX / 2);

    digitalGadget->display(slider->value());

    //connect(acceptBtn, SIGNAL(clicked()), this, SLOT(accept()));
    //connect(cancelBtn, SIGNAL(clicked()), this, SLOT(reject()));
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(onValueChangedSlot(int)));
}

TransformOptions &ContrastTool::getOptions()
{
    return *options;
}

void ContrastTool::setTransformImageData(QImage *&image, ImageWidget *&imageWidget, SinglePixelTransforms* const& transformator)
{
    this->transformator = transformator;
    this->image = image;
    this->imageWidget = imageWidget;
}

void ContrastTool::onValueChangedSlot(int val)
{
    options->setConstant(val);
    digitalGadget->display(val);
    transformator->transform(*image, imageWidget, options);
}
