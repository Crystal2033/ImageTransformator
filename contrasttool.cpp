/***************************************************************************
 *                                                                         *
 *   Copyright (C) 21.08.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "contrasttool.h"

ContrastTool::ContrastTool(QWidget *parent)
{
    Q_UNUSED(parent);

    vertLayout = new QVBoxLayout(this);
    horDataLayout = new QHBoxLayout();
    dataLabel = new QLabel("Contrast edge");
    digitalGadget = new QLCDNumber();
    slider = new QSlider(Qt::Orientation::Horizontal, this);

    horBtnsLayout = new QHBoxLayout();
    acceptBtn = new QPushButton("Accept");
    cancelBtn = new QPushButton("Cancel");

    horDataLayout->addWidget(dataLabel);
    horDataLayout->addWidget(digitalGadget, Qt::AlignCenter);
    vertLayout->addLayout(horDataLayout);
    vertLayout->addWidget(slider, Qt::AlignCenter);
    horBtnsLayout->addWidget(acceptBtn);
    horBtnsLayout->addWidget(cancelBtn);
    vertLayout->addLayout(horBtnsLayout);
    setFixedSize(300, 150);

}
