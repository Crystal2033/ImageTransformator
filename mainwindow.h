/***************************************************************************
 *                                                                         *
 *   Copyright (C) 15.08.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QImage>
#include <QColor>
#include <QLayout>
#include <QScrollArea>
#include <QLabel>
#include <QPushButton>
#include "singlepixeltransforms.h"
#include "graphmenuwidget.h"
#include "imagewidget.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    //Images
    QImage image;
    ImageWidget *startImageWgt = nullptr;
    Histogram* histStartImg = nullptr;
    Histogram* histResultImg = nullptr;
    ImageWidget *resultImageWgt = nullptr;

    //Layouts
    QHBoxLayout *globalHorLayout = nullptr;
    QVBoxLayout *vertStartLayout = nullptr;
    QPushButton *loadImageBtn = nullptr;
    QVBoxLayout *vertResultLayout = nullptr;
    QVBoxLayout *vertMenuLayout = nullptr;
    QVBoxLayout *vertMenuItems = nullptr;

    QHBoxLayout *horBtnsResultLayout = nullptr;
    QPushButton *saveImageBtn = nullptr;
    QPushButton *swapImagesBtn = nullptr;


    //Menu
    GraphMenuWidget* graphMenuWidget = nullptr;

    //Transformators
    SinglePixelTransforms* singlePixelTransformator;


    //Functions
    void addSaveAndSwapBtns(QVBoxLayout*& parentLayout);
    void makeInnerWidgets();
    bool makeAndSaveImage();
    void addImageOnLayout(QImage& img, QVBoxLayout *&layout, ImageWidget*& imageWgt);
    void addLoadImageBtn(QVBoxLayout *& parentLayout);
    void makeGraphicsMenu();
public:
    void setImageAndCreateHist(ImageWidget*& imageWidget, Histogram *& hist, const QImage& image);

private slots:
    void onSaveImageBtnClick();
    void onSwapImagesBtnClick();
    void onLoadImageBtnClick();
public slots:
    void onNegativeBtnClick();

};
#endif // MAINWINDOW_H
