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
#include <QScrollBar>
#include "transformoptions.h"
#include "imagewidget.h"
#include <QImage>
#include "transformations.h"


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

    TransformOptions* options = nullptr;
    SinglePixelTransforms* transformator;
    ImageWidget* imageWidget;
    QImage* image;

    ~ContrastTool();

public:
    explicit ContrastTool(QWidget *parent = nullptr);
    TransformOptions& getOptions();
    void setTransformImageData(QImage*& image, ImageWidget*&  imageWidget, SinglePixelTransforms* const& transformator);


signals:

private slots:
    void onValueChangedSlot(int val);

};

#endif // CONTRASTTOOL_H
