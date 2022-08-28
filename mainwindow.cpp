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
#include "MainWidgets/histogram.h"
#include "Exceptions/exceptions.h"
#include <QtMath>
#include <QThread>


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
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();

    globalHorLayout = new QHBoxLayout();
    globalHorLayout->setSpacing(50);
    vertStartLayout = new QVBoxLayout();
    startImageWgt = new ImageWidget(this);
    histStartImg = new Histogram(screenGeometry ,this);
    startImageWgt->addObserver(histStartImg);

    vertMenuLayout =  new QVBoxLayout();

    vertResultLayout = new QVBoxLayout();
    resultImageWgt = new ImageWidget(this);
    histResultImg = new Histogram(screenGeometry, this);
    resultImageWgt->addObserver(histResultImg);

    this->centralWidget()->setLayout(globalHorLayout);
    move(0, 0);

    vertStartLayout->addWidget(startImageWgt, Qt::AlignHCenter);
    addLoadImageBtn(vertStartLayout);
    vertStartLayout->addWidget(histStartImg, Qt::AlignHCenter);

    makeGraphicsMenu();

    vertResultLayout->addWidget(resultImageWgt, Qt::AlignHCenter);
    addSaveAndSwapBtns(vertResultLayout);

    vertResultLayout->addWidget(histResultImg, Qt::AlignHCenter);

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
        try{
            resultImageWgt->getImage()->scaled(startedImageSize.width(), startedImageSize.height(), Qt::KeepAspectRatio).save(fileName);
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
        QScreen *screen = QGuiApplication::primaryScreen();
        QRect  screenGeometry = screen->geometry();

        //Need to delete this variable
        startedImageSize = image.size();
        image = image
                .scaled(screenGeometry.width() / 3, screenGeometry.height() / 2, Qt::KeepAspectRatio)
                .convertToFormat(QImage::Format_RGBA8888_Premultiplied);
        image = ImageFunctions::setToBrightnessMap(image);

        setImageOnWidget(startImageWgt, image);

    }
}

void MainWindow::onNegativeBtnClick()
{
    if(transformStrategy){
        delete transformStrategy;
    }
    if(!resultImageWgt){
        QMessageBox::critical(this, "Image widget is empty", "Your image doesn`t exist.");
        return;
    }

    transformStrategy = new NegativeTransform();
    try {
        transformStrategy->transform(*startImageWgt->getImage(), resultImageWgt); // add options class DATATransforms
    }  catch (ImageExistanceError& err) {
        Q_UNUSED(err);
    }
}

void MainWindow::onContrastBtnClick()
{
    ToolBuilder* builder = new ConstrastToolBuilder(this);

    if(tool){
        delete tool;
    }
    tool = builder->createTool();

    if(transformStrategy){
        delete transformStrategy;
    }
    transformStrategy = new ContrastTransform;

    try {
        tool->setTransformImageData(startImageWgt->getImage(), resultImageWgt, transformStrategy);
        tool->exec();
    }  catch (ImageExistanceError& err) {
        Q_UNUSED(err);
    }
    delete builder;
}

void MainWindow::onLogarythmBtnClick()
{
    ToolBuilder* builder = new LogarythmToolBuilder(this);
    if(tool){
        delete tool;
    }
    tool = builder->createTool();

    if(transformStrategy){
        delete transformStrategy;
    }
    transformStrategy = new LogarythmTransform;


    try {
        tool->setTransformImageData(startImageWgt->getImage(), resultImageWgt, transformStrategy);
        tool->exec();
    }  catch (ImageExistanceError& err) {
        Q_UNUSED(err);
    }
    delete builder;
}

void MainWindow::onGammaCorrectionBtnClick()
{
    ToolBuilder* builder = new GammaToolBuilder(this);
    if(tool){
        delete tool;
    }
    tool = builder->createTool();

    if(transformStrategy){
        delete transformStrategy;
    }

    transformStrategy = new GammaCorrection;

    try {
        tool->setTransformImageData(startImageWgt->getImage(), resultImageWgt, transformStrategy);
        tool->exec();
    }  catch (ImageExistanceError& err) {
        Q_UNUSED(err);
    }
    delete builder;
}

void MainWindow::onAreaCutBtnClick()
{
    ToolBuilder* builder = new AreaCuttingBuilder(this);
    if(tool){
        delete tool;
    }
    tool = builder->createTool();

    if(transformStrategy){
        delete transformStrategy;
    }

    transformStrategy = new AreaCutting;
    try {
        tool->setTransformImageData(startImageWgt->getImage(), resultImageWgt, transformStrategy);
        tool->exec();
    }  catch (ImageExistanceError& err) {
        Q_UNUSED(err);
    }
    delete builder;
}


void MainWindow::onAverageBtnClick()
{
    ToolBuilder* builder = new AverageWindowFilterBuilder(this);
    if(tool){
        delete tool;
    }
    tool = builder->createTool();

    if(windowTransformator)
    {
        delete windowTransformator;
    }
    windowTransformator = new WindowTransform(AVERAGE);

    try {
        if(tool->exec() == QDialog::Accepted)
        {
            windowTransformator->transform(*startImageWgt->getImage(), resultImageWgt, &tool->getOptions());
        }
    }  catch (ImageExistanceError& err) {
        Q_UNUSED(err);
    }
    delete builder;


}

void MainWindow::onGaussBtnClick()
{
    ToolBuilder* builder = new GaussWindowFilterBuilder(this);
    if(tool){
        delete tool;
    }
    tool = builder->createTool();

    if(windowTransformator)
    {
        delete windowTransformator;
    }
    windowTransformator = new WindowTransform(GAUSS);

    try {
        if(tool->exec() == QDialog::Accepted)
        {
            windowTransformator->transform(*startImageWgt->getImage(), resultImageWgt, &tool->getOptions());
        }
    }  catch (ImageExistanceError& err) {
        Q_UNUSED(err);
    }
    delete builder;
}

void MainWindow::onMedianFilterBtnClick()
{
    ToolBuilder* builder = new MedianWindowFilterBuilder(this);
    if(tool){
        delete tool;
    }
    tool = builder->createTool();

    if(windowTransformator)
    {
        delete windowTransformator;
    }
    windowTransformator = new WindowTransform(MEDIAN);

    try {
        if(tool->exec() == QDialog::Accepted)
        {
            windowTransformator->transform(*startImageWgt->getImage(), resultImageWgt, &tool->getOptions());
        }
    }  catch (ImageExistanceError& err) {
        Q_UNUSED(err);
    }
    delete builder;
}

void MainWindow::onLaplassBtnClick()
{
    //ToolBuilder* builder = new LaplassWindowFilterBuilder(this);
    if(diffTool){
        delete diffTool;
    }
    diffTool = new DiffTool;
    diffTool->createTool(8);

    if(windowTransformator)
    {
        delete windowTransformator;
    }
    windowTransformator = new WindowTransform(LAPLASS);
    TransformOptions* options = new TransformOptions();
    try {
        if(diffTool->exec() == QDialog::Accepted)
        {
            options->setConstant(3);
            options->setWindowTransformMode(diffTool->getCheckedNumber());
            windowTransformator->transform(*startImageWgt->getImage(), resultImageWgt, options);
        }

    }  catch (ImageExistanceError& err) {
        Q_UNUSED(err);
    }
    delete options;
}

void MainWindow::onGradientBtnClick()
{
    if(diffTool){
        delete diffTool;
    }
    diffTool = new DiffTool(this);
    diffTool->createTool(2);

    if(windowTransformator)
    {
        delete windowTransformator;
    }
    windowTransformator = new WindowTransform(GRADIENT);
    TransformOptions* options = new TransformOptions();
    try {
        if(diffTool->exec() == QDialog::Accepted)
        {
            options->setConstant(3);
            options->setWindowTransformMode(diffTool->getCheckedNumber());
            windowTransformator->transform(*startImageWgt->getImage(), resultImageWgt, options);
        }

    }  catch (ImageExistanceError& err) {
        Q_UNUSED(err);
    }
    delete options;
}

void MainWindow::onSummImagesBtnClick()
{
    QFileDialog::Options options;
    QString selectedFilter;
    QString fileName = "";
    if(!resultImageWgt){
        QMessageBox::critical(this, "Image widget is empty", "Your image doesn`t exist.");
        return;
    }

    QImage addingImage;
    fileName = QFileDialog::getOpenFileName(this, "Export Plot", ".", "PNG Files (*.png, *.jpg);;All Files (*)",
                                        &selectedFilter,
                                        options);
    if (!fileName.isEmpty())
    {
        if (!addingImage.load(fileName))
        {
            QString err_msg = QString("Can not download an image<br>Searching by path: %1").arg(fileName);
            qDebug() << err_msg.split("<br>");
            QMessageBox::critical(this
                                  , "Error"
                                  , err_msg);
            exit(-1);
        }

        addingImage = addingImage
                .scaled(image.width(), image.height()) // Qt::KeepAspectRatio
                .convertToFormat(QImage::Format_RGBA8888_Premultiplied);
        addingImage = ImageFunctions::setToBrightnessMap(addingImage);
        QImage* resultImage = nullptr;

        try {
            resultImage = new QImage(*startImageWgt->getImage());

        }  catch (ImageExistanceError& err) {
            Q_UNUSED(err);
        }

        uchar* px = resultImage->bits();
        uchar* addingPx = addingImage.bits();

        const int pixelsQuo = resultImage->width() * resultImage->height();
        int newBrightness = 0;
        for(int i = 0; i < pixelsQuo; i++)
        {
            newBrightness = *px + *addingPx;
            if(newBrightness > BRIGHTNESS_MAX - 1)
            {
                *px++ = *px++ = *px++ = BRIGHTNESS_MAX - 1;
            }
            else{
                *px++ = *px++ = *px++ = newBrightness;
            }

            px++;
            addingPx+=4;
        }

        resultImageWgt->setImage(*resultImage, resultImage->size());
        delete resultImage;

    }
}


