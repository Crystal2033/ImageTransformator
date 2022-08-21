/***************************************************************************
 *                                                                         *
 *   Copyright (C) 21.08.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef CONTRASTTOOL_H
#define CONTRASTTOOL_H

#include <QObject>
#include <QDialog>
#include <QBoxLayout>
#include <QLCDNumber>
#include <QSlider>
#include <QPushButton>
#include <QLabel>


class ContrastTool : public QDialog
{
    Q_OBJECT
private:
    QHBoxLayout* horDataLayout = nullptr;
    QLabel* dataLabel = nullptr;
    QLCDNumber* digitalGadget = nullptr;
    QVBoxLayout* vertLayout = nullptr;
    QHBoxLayout* horBtnsLayout = nullptr;
    QPushButton* acceptBtn = nullptr;
    QPushButton* cancelBtn = nullptr;
    QSlider* slider = nullptr;

public:
    explicit ContrastTool(QWidget *parent = nullptr);

signals:

};

#endif // CONTRASTTOOL_H
