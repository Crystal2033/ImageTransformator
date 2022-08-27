/***************************************************************************
 *                                                                         *
 *   Copyright (C) 15.08.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef GRAPHMENUWIDGET_H
#define GRAPHMENUWIDGET_H

#include <QObject>
#include <QWidget>
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>

class GraphMenuWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GraphMenuWidget(QWidget *parent = nullptr);
    void createMenu(QBoxLayout* parentLayout);

private:
    QVBoxLayout* vertMenuItems = nullptr;


    //Gradation transformation block
    QVBoxLayout* vertGradTransfItems = nullptr;
    QLabel* gradTransformLabel = nullptr;
    QPushButton* contrastBtn = nullptr;
    QPushButton* logarithmBtn = nullptr;
    QPushButton* gammaCorrectionBtn = nullptr;
    QPushButton* cuttingBtn = nullptr;

    //Window transformation block
    QVBoxLayout* vertWindowTransfItems = nullptr;
    QLabel* windowTransformLabel = nullptr;
    QPushButton* averageBtn = nullptr;
    QPushButton* negativeBtn = nullptr;
    QPushButton* gaussBtn = nullptr;
    QPushButton* medianBtn = nullptr;
    QPushButton* laplassianBtn = nullptr;
    QPushButton* gradientBtn = nullptr;


    //Fourier transform
    QVBoxLayout* vertFourierTransfItems = nullptr;
    QLabel* fourierTransformLabel = nullptr;
    QPushButton* simpleFourierTransform = nullptr;
    QPushButton* fastFourierTransform = nullptr;


    //Other
    QScrollArea* scrollArea = nullptr;


    //PRIVATE functions
    void createGradationTransBlock();
    void makeGradationalConnection();
    void makeWindowTransformConnection();
    void createWindowTransBlock();
    void createFourierTransBlock();


};

#endif // GRAPHMENUWIDGET_H
