/***************************************************************************
 *                                                                         *
 *   Copyright (C) 15.08.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "graphmenuwidget.h"
#include <QDebug>

GraphMenuWidget::GraphMenuWidget()
{

}

void GraphMenuWidget::createMenu(QBoxLayout* parentLayout)
{
    vertMenuItems = new QVBoxLayout();
    scrollArea = new QScrollArea();
    scrollArea->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    vertMenuItems->setSizeConstraint(QLayout::SetMinimumSize);

//    for(int i = 0; i < 60; i++){
//        QPushButton* btn = new QPushButton(QString::number(i) + " item");
//        vertMenuItems->addWidget(btn);
//    }

    createGradationTransBlock();
    createWindowTransBlock();
    createFourierTransBlock();

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

    contrastBtn = new QPushButton("Contrast Transform (add description)");
    negativeBtn = new QPushButton("Negative Transform");
    logarithmBtn = new QPushButton("Logarithm Transform (add description)");
    gammaCorrectionBtn = new QPushButton("Gamma Correction (add description)");
    cuttingBtn = new QPushButton("Area Cutting (add description)");

    vertGradTransfItems->addWidget(gradTransformLabel);
    vertGradTransfItems->addWidget(contrastBtn);
    vertGradTransfItems->addWidget(negativeBtn);
    vertGradTransfItems->addWidget(logarithmBtn);
    vertGradTransfItems->addWidget(gammaCorrectionBtn);
    vertGradTransfItems->addWidget(cuttingBtn);

    vertMenuItems->addLayout(vertGradTransfItems);
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

    averageBtn = new QPushButton("Average Transform (add description)");
    gaussBtn = new QPushButton("Gauss Transform (add description)");
    medianBtn = new QPushButton("Median Filter (add description)");
    laplassianBtn = new QPushButton("Laplassian (add description)");
    gradientBtn = new QPushButton("Gradient (add description)");

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

    simpleFourierTransform = new QPushButton("Simple Fourier Transform (add description)");
    fastFourierTransform = new QPushButton("Fast Fourier Transform (add description)");

    vertFourierTransfItems->addWidget(fourierTransformLabel);
    vertFourierTransfItems->addWidget(simpleFourierTransform);
    vertFourierTransfItems->addWidget(fastFourierTransform);

    vertMenuItems->addLayout(vertFourierTransfItems);
}
