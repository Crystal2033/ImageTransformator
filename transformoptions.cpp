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

QPair<unsigned int, unsigned int> TransformOptions::getConstEdges() const
{
    return QPair<unsigned int, unsigned int>(leftConstantEdge, rightConstantEdge);
}

int TransformOptions::getGammaConstant() const
{
    return gammaConstant;
}

void TransformOptions::setConstant(const unsigned int constant)
{
    constantNumber = constant;
}

void TransformOptions::setConstEdges(const QPair<unsigned int, unsigned int> &numPair)
{
    leftConstantEdge = numPair.first;
    rightConstantEdge = numPair.second;
}

void TransformOptions::setGammaConst(const int gamma)
{
    gammaConstant = gamma;
}
