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
#include <QScreen>
#include "histogram.h"
#include "exceptions.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    makeInnerWidgets();
}

MainWindow::~MainWindow()
{
    delete ui;
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
    startImageWgt->addObserver(histStartImg);

    vertMenuLayout =  new QVBoxLayout();

    vertResultLayout = new QVBoxLayout();
    resultImageWgt = new ImageWidget(this);
    histResultImg = new Histogram(this);
    resultImageWgt->addObserver(histResultImg);

    this->centralWidget()->setLayout(globalHorLayout);
    move(0, 0);

    vertStartLayout->addWidget(startImageWgt);
    addLoadImageBtn(vertStartLayout);
    vertStartLayout->addWidget(histStartImg);

    makeGraphicsMenu();

    vertResultLayout->addWidget(resultImageWgt);
    addSaveAndSwapBtns(vertResultLayout);

    vertResultLayout->addWidget(histResultImg);

    globalHorLayout->addLayout(vertStartLayout);
    globalHorLayout->addLayout(vertMenuLayout);
    globalHorLayout->addLayout(vertResultLayout);


}

void MainWindow::addLoadImageBtn(QVBoxLayout *&parentLayout)
{
    loadImageBtn = new QPushButton("Load image");
    parentLayout->addWidget(loadImageBtn);
    connect(loadImageBtn, SIGNAL(clicked()), this, SLOT(onLoadImageBtnClick()));
}

void MainWindow::makeGraphicsMenu()
{
    graphMenuWidget = new GraphMenuWidget(this);
    graphMenuWidget->createMenu(vertMenuLayout);

}

void MainWindow::setImageOnWidget(ImageWidget *&imageWidget, const QImage& image)
{
    imageWidget->setImage(image, image.size());
}

void MainWindow::onSaveImageBtnClick()
{
    QFileDialog::Options options;
    QString selectedFilter;
    QString fileName = "";
    try {
        if(!resultImageWgt->getImage()){
            QMessageBox::critical(this, "Image widget is empty", "Your image doesn`t exist.");
            return;
        }
    }
    catch (ImageExistanceError& err) {
        Q_UNUSED(err);
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
            resultImageWgt->getImage()->save(fileName);
        }
        catch (ImageExistanceError& err) {
            Q_UNUSED(err);
            return;
        }
    }
}

void MainWindow::onSwapImagesBtnClick()
{
    QImage* startImage;
    if(!resultImageWgt){
        QMessageBox::critical(this, "Image widget is empty", "Something goes wrong with your image widget");
        return;
    }
    try{
        startImage = resultImageWgt->getImage();
    }
    catch (ImageExistanceError& err) {
        Q_UNUSED(err);
        return;
    }

    setImageOnWidget(startImageWgt, *startImage);
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
        qDebug() << image.size();
        QScreen *screen = QGuiApplication::primaryScreen();
        QRect  screenGeometry = screen->geometry();
        int height = screenGeometry.height();
        int width = screenGeometry.width();
        qDebug() << height << Qt::endl;
        qDebug() << width << Qt::endl;
        image = image
                .scaled(width / 3, height / 2, Qt::KeepAspectRatio)
                .convertToFormat(QImage::Format_RGBA8888_Premultiplied);

        qDebug() << "After resize" << image.size()<< Qt::endl;
        setImageOnWidget(startImageWgt, image);

    }
}

void MainWindow::onNegativeBtnClick()
{
    if(transformStrategy){
        delete transformStrategy;
    }

    transformStrategy = new NegativeTransform();
    try {
        transformStrategy->transform(*startImageWgt->getImage(), resultImageWgt);
    }  catch (ImageExistanceError& err) {
        Q_UNUSED(err);
    }
}


