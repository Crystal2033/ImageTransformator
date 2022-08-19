/***************************************************************************
 *                                                                         *
 *   Copyright (C) 15.08.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QString>
#include <QMessageBox>
#include <QDir>
#include <QScrollArea>
#include <QLabel>
#include <QFileDialog>
#include "histogram.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadImage();
    makeInnerWidgets();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadImage()
{
    /* Загрузка изображения, с которым будет вся работа.
     *  Должно вызываться до всех остальных функций.
    */

    // нужно корректно склеить путь до файла, чтобы слеши были правильные
    QDir dir;
    // Сейчас путь dir == QApplication::applicationDirPath()
    QString path = dir.absoluteFilePath("Cat.jpg");

    if (!image.load(path))
    {
        QString err_msg = QString("Не смог загрузить картинку<br>Искал по пути: %1").arg(path);
        qDebug() << err_msg.split("<br>");
        QMessageBox::critical(this
                              , "Ошибка"
                              , err_msg);
        exit(-1);
    }
    image = image
            .convertToFormat(QImage::Format_RGBA8888_Premultiplied);
}

void MainWindow::addSaveAndSwapBtns(QVBoxLayout*& parentLayout)
{
    horBtnsResultLayout = new QHBoxLayout();
    horBtnsResultLayout->setSizeConstraint(QLayout::SetMinimumSize);
    saveImageBtn = new QPushButton("Save image");
    swapImagesBtn = new QPushButton("Set to start image");

    horBtnsResultLayout->addWidget(saveImageBtn);
    horBtnsResultLayout->addWidget(swapImagesBtn);

    parentLayout->addLayout(horBtnsResultLayout);

    connect(saveImageBtn, SIGNAL(clicked()), this, SLOT(onSaveImageBtnClick()));
    connect(swapImagesBtn, SIGNAL(clicked()), this, SLOT(onSwapImagesBtnClick()));
}

void MainWindow::makeInnerWidgets()
{
    globalHorLayout = new QHBoxLayout();
    globalHorLayout->setSpacing(50);
    vertStartLayout = new QVBoxLayout();
    vertResultLayout = new QVBoxLayout();

    vertMenuLayout =  new QVBoxLayout();

    this->centralWidget()->setLayout(globalHorLayout);
    move(0, 0);


    Histogram* hist_start_img = new Histogram;
    Histogram* hist_result_img = new Histogram;

    QImage* brightnessImage = &ImageFunctions::setToBrightnessMap(image);

    addImageOnLayout(*brightnessImage, vertStartLayout, startImageWgt);
    addLoadImageBtn(vertStartLayout);
    addHistOnLayout(*hist_start_img, vertStartLayout, *brightnessImage);

    makeGraphicsMenu();

    addImageOnLayout(image, vertResultLayout, resultImageWgt);
    addSaveAndSwapBtns(vertResultLayout);
    addHistOnLayout(*hist_result_img, vertResultLayout, image);



    globalHorLayout->addLayout(vertStartLayout);
    globalHorLayout->addLayout(vertMenuLayout);
    globalHorLayout->addLayout(vertResultLayout);


}

void MainWindow::addImageOnLayout(QImage &img, QVBoxLayout *&layout, ImageWidget *&imageWgt)
{
    if(imageWgt == nullptr){
        imageWgt = new ImageWidget(this);
    }

    imageWgt->setImage(img, QSize(width(), height()));
    layout->addWidget(imageWgt);
}

void MainWindow::addLoadImageBtn(QVBoxLayout *&parentLayout)
{
    loadImageBtn = new QPushButton("Load image");
    parentLayout->addWidget(loadImageBtn);

}

void MainWindow::addHistOnLayout(Histogram &hist, QVBoxLayout *&layout, const QImage &img)
{
    hist.createHistogram(img);
    layout->addWidget(&hist);
}

void MainWindow::makeGraphicsMenu()
{
    graphMenuWidget = new GraphMenuWidget();
    graphMenuWidget->createMenu(vertMenuLayout);

}

void MainWindow::onSaveImageBtnClick()
{
    QFileDialog::Options options;
    QString selectedFilter;
    QString fileName = "";
    if(!resultImageWgt){
        QMessageBox::critical(this, "Image widget is empty", "Your image doesn`t exist.");
        return;
    }


    fileName = QFileDialog::getSaveFileName(this, "Export Plot", ".", "PNG Files (*.png, *.jpg);;All Files (*)",
                                        &selectedFilter,
                                        options);
    if (!fileName.isEmpty())
    {
      // QSize startPictureSize =resultImageWgt->getPictureSize();
      // resultImageWgt->getImage().scaled(startPictureSize.width(), startPictureSize.height(), Qt::KeepAspectRatio).save(fileName);
        resultImageWgt->getImage().save(fileName);
    }
}

void MainWindow::onSwapImagesBtnClick()
{
    if(!resultImageWgt){
        QMessageBox::critical(this, "Image widget is empty", "Something goes wrong with your image widget");
        return;
    }
    image = resultImageWgt->getImage();
    startImageWgt->setImage(image, image.size());
}

