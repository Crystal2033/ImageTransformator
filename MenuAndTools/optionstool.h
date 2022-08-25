/***************************************************************************
 *                                                                         *
 *   Copyright (C) 21.08.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef OPTIONSTOOL_H
#define OPTIONSTOOL_H

#include <QObject>
#include <QDialog>
#include <QBoxLayout>
#include <QLCDNumber>
#include <QSlider>
#include <QPushButton>
#include <QLabel>
#include <QScrollBar>
#include "transformoptions.h"
#include "MainWidgets/imagewidget.h"
#include <QImage>
#include "Algorithms/transformations.h"
#include <QPair>
#include "rangeslider.h"
#include <QCheckBox>

class OptionsTool : public QDialog
{
    Q_OBJECT
private:
    QHBoxLayout* horConstantDataLay = nullptr;
    QLabel* constantLabel = nullptr;
    QLCDNumber* digitalGadget = nullptr;
    QVBoxLayout* vertLayout = nullptr;
    QHBoxLayout* acceptCancelHorLay = nullptr;
    QPushButton* acceptBtn = nullptr;
    QPushButton* cancelBtn = nullptr;
    QSlider* constantSlider = nullptr;


    QHBoxLayout* horGammaConstantLay;
    QLabel* gammaLabel = nullptr;
    QLCDNumber* digitalGadget2 = nullptr;
    QSlider* gammaSlider = nullptr;


    TransformOptions* options = nullptr;
    SinglePixelTransforms* transformator = nullptr;
    ImageWidget* imageWidget = nullptr;
    QImage* image = nullptr;

    QHBoxLayout* horRangleSliderLay = nullptr;
    QLCDNumber* leftNumSliderGadget = nullptr;
    QLCDNumber* rightNumSliderGadget = nullptr;
    RangeSlider* rangeSlider = nullptr;
    QCheckBox* areaCheckBox = nullptr;

public:
    explicit OptionsTool(QWidget *parent = nullptr);
    TransformOptions& getOptions();
    void setTransformImageData(QImage*& image, ImageWidget*&  imageWidget, SinglePixelTransforms* const& transformator);

    void createFirstSlider(const QPair<int , int>& range, const QString& labelName, const int startValue = 0);
    void createSecondSlider(const QPair<int , int>& range, const QString& labelName, const int startValue = 0);
    void createRangeSlider(const QPair<int, int>& range);
    void createAcceptCancelBtns();
    virtual ~OptionsTool();


signals:

private slots:
    void onConstantValueChanged(int val);
    void onGammaValueChanged(int val);
    void onLeftAreaValueChanged(int val);
    void onRightAreaValueChanged(int val);
    void onAreaCheckStatusClicked(int val);

};


class ToolBuilder
{
protected:
    OptionsTool* tool = nullptr;
    void reset(QWidget* parent = nullptr);
public:
    virtual ~ToolBuilder() = default;
    virtual void createFirstSlider() = 0;
    virtual void createSecondSlider() = 0;
    virtual OptionsTool*& createTool() = 0;
    virtual void createAcceptCancelBtns();
    virtual void createRangeSlider() = 0;
};

class ConstrastToolBuilder : public ToolBuilder
{
public:
    ConstrastToolBuilder(QWidget* parent = nullptr);

    void createFirstSlider() override;
    void createSecondSlider() override {};
    void createRangeSlider() override {};
    OptionsTool*& createTool() override;

};

class LogarythmToolBuilder : public ToolBuilder
{
public:
    LogarythmToolBuilder(QWidget* parent = nullptr);
    void createFirstSlider() override;
    void createSecondSlider() override {};
    void createRangeSlider() override {};
    OptionsTool*& createTool() override;

};

class GammaToolBuilder : public ToolBuilder
{
public:
    GammaToolBuilder(QWidget* parent = nullptr);
    void createFirstSlider() override;
    void createSecondSlider() override;
    void createRangeSlider() override {};
    OptionsTool*& createTool() override;

};


class AreaCuttingBuilder : public ToolBuilder
{
public:
    AreaCuttingBuilder(QWidget* parent = nullptr);
    void createFirstSlider() override {};
    void createSecondSlider() override {};
    void createRangeSlider() override;
    OptionsTool*& createTool() override;
};

#endif // OPTIONSTOOL_H
