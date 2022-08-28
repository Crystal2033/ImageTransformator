/***************************************************************************
 *                                                                         *
 *   Copyright (C) 28.08.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef DIFFTOOL_H
#define DIFFTOOL_H

#include <QDialog>
#include <QVector>
#include <QRadioButton>
#include <QLayout>
#include <QGroupBox>
#include <QPushButton>

class DiffTool : public QDialog
{
protected:
    QHBoxLayout* horLay = nullptr;
    QPushButton *acceptButton = nullptr;
    QPushButton *cancelButton = nullptr;
    QGroupBox* groupBox = nullptr;
    QVBoxLayout* vertLay = nullptr;
    QVector<QRadioButton*> radioButtons;
public:
    DiffTool(QWidget* parent = nullptr);
    void createTool(const int valueOfModes);
    int getCheckedNumber() const;
};



#endif // DIFFTOOL_H
