/***************************************************************************
 *                                                                         *
 *   Copyright (C) 15.08.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "graphmenuwidget.h"
#include "mainwindow.h"
#include <QDebug>

GraphMenuWidget::GraphMenuWidget(QWidget *parent) : QWidget(parent)
{

}

void GraphMenuWidget::createMenu(QBoxLayout* parentLayout)
{
    vertMenuItems = new QVBoxLayout();
    scrollArea = new QScrollArea();
    scrollArea->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    vertMenuItems->setSizeConstraint(QLayout::SetMinimumSize);

    createGradationTransBlock();
    createWindowTransBlock();
    createBlockWithOtherTransforms();
    //createFourierTransBlock();

    setLayout(vertMenuItems);
    scrollArea->setWidgetResizable(true);
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(this);

    parentLayout->addWidget(scrollArea);


}

void GraphMenuWidget::createGradationTransBlock()
{
    vertGradTransfItems = new QVBoxLayout();
    vertGradTransfItems->setSizeConstraint(QLayout::SetMinimumSize);

    gradTransformLabel = new QLabel();
    gradTransformLabel->setText(QString("Gradation transformations"));
    gradTransformLabel->setAlignment(Qt::AlignCenter);
    gradTransformLabel->setWordWrap(true);

    contrastBtn = new QPushButton("&Contrast Transform");
    negativeBtn = new QPushButton("Negative Transform");
    logarithmBtn = new QPushButton("Logarithm Transform");
    gammaCorrectionBtn = new QPushButton("Gamma Correction");
    cuttingBtn = new QPushButton("Area Cutting");
    makeGradationalConnection();

    vertGradTransfItems->addWidget(gradTransformLabel);
    vertGradTransfItems->addWidget(contrastBtn);
    vertGradTransfItems->addWidget(negativeBtn);
    vertGradTransfItems->addWidget(logarithmBtn);
    vertGradTransfItems->addWidget(gammaCorrectionBtn);
    vertGradTransfItems->addWidget(cuttingBtn);

    vertMenuItems->addLayout(vertGradTransfItems);
}

void GraphMenuWidget::makeGradationalConnection()
{
    connect(negativeBtn, SIGNAL(clicked()), parent(), SLOT(onNegativeBtnClick()));
    connect(contrastBtn, SIGNAL(clicked()), parent(), SLOT(onContrastBtnClick()));
    connect(logarithmBtn, SIGNAL(clicked()), parent(), SLOT(onLogarythmBtnClick()));
    connect(gammaCorrectionBtn, SIGNAL(clicked()), parent(), SLOT(onGammaCorrectionBtnClick()));
    connect(cuttingBtn, SIGNAL(clicked()), parent(), SLOT(onAreaCutBtnClick()));
}

void GraphMenuWidget::makeWindowTransformConnection()
{
    connect(averageBtn, SIGNAL(clicked()), parent(), SLOT(onAverageBtnClick()));
    connect(gaussBtn, SIGNAL(clicked()), parent(), SLOT(onGaussBtnClick()));
    connect(medianBtn, SIGNAL(clicked()), parent(), SLOT(onMedianFilterBtnClick()));
    connect(laplassianBtn, SIGNAL(clicked()), parent(), SLOT(onLaplassBtnClick()));
    connect(gradientBtn, SIGNAL(clicked()), parent(), SLOT(onGradientBtnClick()));
}

void GraphMenuWidget::makeFourierTransformConnection()
{
    connect(simpleFourierTransform, SIGNAL(clicked()), parent(), SLOT(onFourierTransformBtnClick()));
}

void GraphMenuWidget::createWindowTransBlock()
{
    vertWindowTransfItems = new QVBoxLayout();
    vertWindowTransfItems->setSizeConstraint(QLayout::SetMinimumSize);

    windowTransformLabel = new QLabel();
    windowTransformLabel->setAlignment(Qt::AlignCenter);
    windowTransformLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    windowTransformLabel->setWordWrap(true);
    windowTransformLabel->setText(QString("Window transformation"));

    averageBtn = new QPushButton("Average Transform");
    gaussBtn = new QPushButton("Gauss Transform");
    medianBtn = new QPushButton("Median Filter");
    laplassianBtn = new QPushButton("Laplassian");
    gradientBtn = new QPushButton("Gradient");
    makeWindowTransformConnection();

    vertWindowTransfItems->addWidget(windowTransformLabel);
    vertWindowTransfItems->addWidget(averageBtn);
    vertWindowTransfItems->addWidget(gaussBtn);
    vertWindowTransfItems->addWidget(medianBtn);
    vertWindowTransfItems->addWidget(laplassianBtn);
    vertWindowTransfItems->addWidget(gradientBtn);

    vertMenuItems->addLayout(vertWindowTransfItems);
}

void GraphMenuWidget::createFourierTransBlock()
{
    vertFourierTransfItems = new QVBoxLayout();
    vertFourierTransfItems->setSizeConstraint(QLayout::SetMinimumSize);

    fourierTransformLabel = new QLabel();
    fourierTransformLabel->setAlignment(Qt::AlignCenter);
    fourierTransformLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    fourierTransformLabel->setWordWrap(true);
    fourierTransformLabel->setText(QString("Fourier transformations"));

    simpleFourierTransform = new QPushButton("Simple Fourier Transform");
    //fastFourierTransform = new QPushButton("Fast Fourier Transform (add impl)");
    makeFourierTransformConnection();

    vertFourierTransfItems->addWidget(fourierTransformLabel);
    vertFourierTransfItems->addWidget(simpleFourierTransform);
    //vertFourierTransfItems->addWidget(fastFourierTransform);

    vertMenuItems->addLayout(vertFourierTransfItems);
}

void GraphMenuWidget::createBlockWithOtherTransforms()
{
    vertOtherLay = new QVBoxLayout();
    summImageslabel = new QLabel("Other transforms");
    summImageslabel->setAlignment(Qt::AlignCenter);
    summImageslabel->setWordWrap(true);
    summImagesBtn = new QPushButton("Summ images");

    vertOtherLay->addWidget(summImageslabel);
    vertOtherLay->addWidget(summImagesBtn);

    vertMenuItems->addLayout(vertOtherLay);
    connect(summImagesBtn, SIGNAL(clicked()), parent(), SLOT(onSummImagesBtnClick()));

}
