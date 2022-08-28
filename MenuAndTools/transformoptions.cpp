/***************************************************************************
 *                                                                         *
 *   Copyright (C) 23.08.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "transformoptions.h"

TransformOptions::TransformOptions()
{

}

unsigned int TransformOptions::getConstant() const
{
    return constantNumber;
}

int TransformOptions::getGammaConstant() const
{
    return gammaConstant;
}

bool TransformOptions::isAreaContrastChecked() const
{
    return areaContrastChecker;
}

int TransformOptions::getLeftAreaRange() const
{
    return rangeArea.first;
}

int TransformOptions::getRightAreaRange() const
{
    return rangeArea.second;
}

int TransformOptions::getMatrixDimension() const
{
    return windowMatrixDimension;
}

int TransformOptions::getWindowTransformMode() const
{
    return windowTransformMode;
}

void TransformOptions::setAreaCheckStatus(const bool status)
{
    areaContrastChecker = status;
}

void TransformOptions::setConstant(const unsigned int constant)
{
    constantNumber = constant;
}

void TransformOptions::setRangeArea(const QPair<int, int> &area)
{
    rangeArea.first = area.first;
    rangeArea.second = area.second;
}

void TransformOptions::setGammaConst(const int gamma)
{
    gammaConstant = gamma;
}

void TransformOptions::setLeftAreaRange(const int val)
{
    rangeArea.first = val;
}

void TransformOptions::setRightAreaRange(const int val)
{
    rangeArea.second = val;
}

void TransformOptions::setMatrixDimension(const int val)
{
    windowMatrixDimension = val;
}

void TransformOptions::setWindowTransformMode(const int val)
{
    windowTransformMode = val;
}
