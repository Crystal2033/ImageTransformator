/***************************************************************************
 *                                                                         *
 *   Copyright (C) 21.08.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "optionstool.h"
#include "MainWidgets/histogram.h"


OptionsTool::~OptionsTool()
{
    delete options;
}

OptionsTool::OptionsTool(QWidget *parent)
{
    Q_UNUSED(parent);
    options = new TransformOptions();
    vertLayout = new QVBoxLayout(this);
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

void OptionsTool::createFirstSlider(const QPair<int, int> &range, const QString& labelName, const int startValue)
{
    horConstantDataLay = new QHBoxLayout;
    constantLabel = new QLabel(labelName);
    digitalGadget = new QLCDNumber;
    digitalGadget->setFixedSize(200, 100);
    constantSlider = new QSlider(Qt::Orientation::Horizontal, this);

    constantSlider->setRange(range.first, range.second);
    constantSlider->setTickPosition(QSlider::TicksBelow);
    constantSlider->setValue(startValue);

    horConstantDataLay->addWidget(constantLabel);
    horConstantDataLay->addWidget(digitalGadget, Qt::AlignCenter);
    digitalGadget->display(constantSlider->value());

    vertLayout->addLayout(horConstantDataLay);
    vertLayout->addWidget(constantSlider, Qt::AlignCenter);

    connect(constantSlider, SIGNAL(valueChanged(int)), this, SLOT(onConstantValueChanged(int)));
}

void OptionsTool::createSecondSlider(const QPair<int, int> &range, const QString& labelName, const int startValue)
{
    horGammaConstantLay = new QHBoxLayout;
    gammaLabel = new QLabel(labelName);
    digitalGadget2 = new QLCDNumber;
    digitalGadget2->setFixedSize(200, 100);
    gammaSlider = new QSlider(Qt::Orientation::Horizontal, this);

    gammaSlider->setRange(range.first, range.second);
    gammaSlider->setTickPosition(QSlider::TicksBelow);
    gammaSlider->setValue(startValue);

    horGammaConstantLay->addWidget(gammaLabel);
    horGammaConstantLay->addWidget(digitalGadget2, Qt::AlignCenter);
    digitalGadget2->display(gammaSlider->value());

    vertLayout->addLayout(horGammaConstantLay);
    vertLayout->addWidget(gammaSlider, Qt::AlignCenter);

    connect(gammaSlider, SIGNAL(valueChanged(int)), this, SLOT(onGammaValueChanged(int)));
}

void OptionsTool::createRangeSlider(const QPair<int, int> &range)
{
    rangeSlider = new RangeSlider(this);
    leftNumSliderGadget = new QLCDNumber;
    rightNumSliderGadget = new QLCDNumber;
    horRangleSliderLay = new QHBoxLayout;
    areaCheckBox = new QCheckBox("Black/White Mode");

    horRangleSliderLay->addWidget(leftNumSliderGadget);
    horRangleSliderLay->addWidget(rangeSlider);
    horRangleSliderLay->addWidget(rightNumSliderGadget);

    rangeSlider->SetRange(range.first, range.second);
    rangeSlider->setFixedSize(200, 100);
    options->setRangeArea(range);

    leftNumSliderGadget->display(range.first);
    rightNumSliderGadget->display(range.second);

    vertLayout->addLayout(horRangleSliderLay);
    vertLayout->addWidget(areaCheckBox);


    connect(rangeSlider, SIGNAL(lowerValueChanged(int)), this, SLOT(onLeftAreaValueChanged(int)));
    connect(rangeSlider, SIGNAL(upperValueChanged(int)), this, SLOT(onRightAreaValueChanged(int)));
    connect(areaCheckBox, SIGNAL(stateChanged(int)), this, SLOT(onAreaCheckStatusClicked(int)));
}

void OptionsTool::createAcceptCancelBtns()
{
    acceptCancelHorLay = new QHBoxLayout();
    acceptBtn = new QPushButton("Accept");
    cancelBtn = new QPushButton("Cancel");

    acceptCancelHorLay->addWidget(acceptBtn);
    acceptCancelHorLay->addWidget(cancelBtn);

    vertLayout->addLayout(acceptCancelHorLay);
    connect(acceptBtn, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelBtn, SIGNAL(clicked()), this, SLOT(reject()));
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

void OptionsTool::onLeftAreaValueChanged(int val)
{
    options->setLeftAreaRange(val);
    leftNumSliderGadget->display(val);
    transformator->transform(*image, imageWidget, options);
}

void OptionsTool::onRightAreaValueChanged(int val)
{
    options->setRightAreaRange(val);
    rightNumSliderGadget->display(val);
    transformator->transform(*image, imageWidget, options);
}

void OptionsTool::onAreaCheckStatusClicked(int val)
{
    options->setAreaCheckStatus(val);
    transformator->transform(*image, imageWidget, options);
}


void ToolBuilder::reset(QWidget *parent)
{
    this->tool = new OptionsTool(parent);
}

void ToolBuilder::createAcceptCancelBtns()
{
    tool->createAcceptCancelBtns();
}


ConstrastToolBuilder::ConstrastToolBuilder(QWidget *parent)
{
    reset(parent);
}

void ConstrastToolBuilder::createFirstSlider()
{
    tool->createFirstSlider(QPair<int, int>(0, BRIGHTNESS_MAX - 1), "Contrast edge", BRIGHTNESS_MAX / 2);
}

OptionsTool*& ConstrastToolBuilder::createTool()
{
    createFirstSlider();
    createAcceptCancelBtns();
    return tool;
}

GammaToolBuilder::GammaToolBuilder(QWidget *parent)
{
    reset(parent);
}

void GammaToolBuilder::createFirstSlider()
{
    tool->createFirstSlider(QPair<int, int>(1, BRIGHTNESS_MAX - 1), "Constant/25", BRIGHTNESS_MAX / 2);
}

void GammaToolBuilder::createSecondSlider()
{
    tool->createSecondSlider(QPair<int, int>(1, BRIGHTNESS_MAX - 1), "Gamma value/25");
}

OptionsTool*& GammaToolBuilder::createTool()
{
    createFirstSlider();
    createSecondSlider();
    createAcceptCancelBtns();
    return tool;
}

LogarythmToolBuilder::LogarythmToolBuilder(QWidget *parent)
{
    reset(parent);
}

void LogarythmToolBuilder::createFirstSlider()
{
    tool->createFirstSlider(QPair<int ,int>(0, BRIGHTNESS_MAX - 1), "Logarythm constant; y = C*ln(x)", (BRIGHTNESS_MAX - 1)/qLn(BRIGHTNESS_MAX));
}

OptionsTool*& LogarythmToolBuilder::createTool()
{
    createFirstSlider();
    createAcceptCancelBtns();
    return tool;
}

AreaCuttingBuilder::AreaCuttingBuilder(QWidget *parent)
{
    reset(parent);
}

void AreaCuttingBuilder::createRangeSlider()
{
    tool->createRangeSlider(QPair<int, int>(0, BRIGHTNESS_MAX - 1));
}

OptionsTool *&AreaCuttingBuilder::createTool()
{
    createRangeSlider();
    createAcceptCancelBtns();
    return tool;
}
