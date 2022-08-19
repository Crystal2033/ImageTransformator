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
#include "exceptions.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //loadImage();
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
    startImageWgt = new ImageWidget(this);
    histStartImg = new Histogram(this);

    vertMenuLayout =  new QVBoxLayout();

    vertResultLayout = new QVBoxLayout();
    resultImageWgt = new ImageWidget(this);
    histResultImg = new Histogram(this);

    this->centralWidget()->setLayout(globalHorLayout);
    move(0, 0);

    //QImage* brightnessImage = &ImageFunctions::setToBrightnessMap(image);
    vertStartLayout->addWidget(startImageWgt);
    //addImageOnLayout(image, vertStartLayout, startImageWgt);
    addLoadImageBtn(vertStartLayout);
    vertStartLayout->addWidget(histStartImg);
    //addHistOnLayout(*hist_start_img, vertStartLayout, *brightnessImage);

    makeGraphicsMenu();

    //addImageOnLayout(image, vertResultLayout, resultImageWgt);
    vertResultLayout->addWidget(resultImageWgt);
    addSaveAndSwapBtns(vertResultLayout);
    //addHistOnLayout(*histResultImg, vertResultLayout, image);
    vertResultLayout->addWidget(histResultImg);


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
    connect(loadImageBtn, SIGNAL(clicked()), this, SLOT(onLoadImageBtnClick()));
}

void MainWindow::makeGraphicsMenu()
{
    graphMenuWidget = new GraphMenuWidget();
    graphMenuWidget->createMenu(vertMenuLayout);

}

void MainWindow::setImageAndCreateHist(ImageWidget *&imageWidget, Histogram *&hist, const QImage& image)
{

    QImage* brightnessImage = &ImageFunctions::setToBrightnessMap(image);
    imageWidget->setImage(*brightnessImage, brightnessImage->size());
    hist->createHistogram(imageWidget->getImage(), imageWidget->size());
}

//void MainWindow::setImageOnWidget(const QImage &img, ImageWidget *&imageWidget)
//{
//    imageWidget->setImage(img, img.size());
//    addHistOnLayout(*hist_start_img, vertStartLayout, *brightnessImage);
//}

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
        try{
            resultImageWgt->getImage().save(fileName);
        }
        catch (ImageExistanceError& err) {
            Q_UNUSED(err);
            return;
        }
    }
}

void MainWindow::onSwapImagesBtnClick()
{
    if(!resultImageWgt){
        QMessageBox::critical(this, "Image widget is empty", "Something goes wrong with your image widget");
        return;
    }
    try{
        image = resultImageWgt->getImage();
    }
    catch (ImageExistanceError& err) {
        Q_UNUSED(err);
        return;
    }

    setImageAndCreateHist(startImageWgt, histStartImg, image);
}

void MainWindow::onLoadImageBtnClick()
{
    QFileDialog::Options options;
    QString selectedFilter;
    QString fileName = "";
    if(!resultImageWgt){
        QMessageBox::critical(this, "Image widget is empty", "Your image doesn`t exist.");
        return;
    }


    fileName = QFileDialog::getOpenFileName(this, "Export Plot", ".", "PNG Files (*.png, *.jpg);;All Files (*)",
                                        &selectedFilter,
                                        options);
    if (!fileName.isEmpty())
    {
      // QSize startPictureSize =resultImageWgt->getPictureSize();
      // resultImageWgt->getImage().scaled(startPictureSize.width(), startPictureSize.height(), Qt::KeepAspectRatio).save(fileName);
        if (!image.load(fileName))
        {
            QString err_msg = QString("Can not download an image<br>Searching by path: %1").arg(fileName);
            qDebug() << err_msg.split("<br>");
            QMessageBox::critical(this
                                  , "Error"
                                  , err_msg);
            exit(-1);
        }
        image = image
                .scaled(width(), height(), Qt::KeepAspectRatio)
                .convertToFormat(QImage::Format_RGBA8888_Premultiplied);

        setImageAndCreateHist(startImageWgt, histStartImg, image);

    }
}

