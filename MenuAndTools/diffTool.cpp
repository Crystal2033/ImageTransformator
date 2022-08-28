/***************************************************************************
 *                                                                         *
 *   Copyright (C) 28.08.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "diffTool.h"
#include <QDebug>

DiffTool::DiffTool(QWidget *parent)
{
    Q_UNUSED(parent);
    //setFixedSize(400, 200);
    vertLay = new QVBoxLayout(this);
    horLay = new QHBoxLayout;
    acceptButton = new QPushButton("Accept");
    cancelButton = new QPushButton("Cancel");
    connect(acceptButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

void DiffTool::createTool(const int valueOfModes)
{
    for (int i = 0; i < valueOfModes; i++)
    {
        QRadioButton* radioBtn = new QRadioButton("Mode " + QString::number(i + 1));
        vertLay->addWidget(radioBtn);
        radioButtons.append(radioBtn);
    }
    radioButtons[0]->setChecked(true);
    horLay->addWidget(acceptButton);
    horLay->addWidget(cancelButton);
    vertLay->addLayout(horLay);
}

int DiffTool::getCheckedNumber() const
{
    int checkedNumber = 0;
    for(int i = 0; i < radioButtons.size(); i++)
    {
        if(radioButtons[i]->isChecked())
        {
            checkedNumber = i;
        }
    }
    return checkedNumber;
}
