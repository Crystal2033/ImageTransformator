/***************************************************************************
 *                                                                         *
 *   Copyright (C) 23.08.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef TRANSFORMOPTIONS_H
#define TRANSFORMOPTIONS_H
#include <QPair>

class TransformOptions
{
private:
    unsigned int constantNumber = 0;
    int gammaConstant = 0;
    QPair<int, int> rangeArea;
    bool areaContrastChecker = false;
    int windowMatrixDimension = 3;
    int windowTransformMode = 1;

public:
    TransformOptions();
    //GETTERS
    unsigned int getConstant() const;
    int getGammaConstant() const;
    bool isAreaContrastChecked() const;
    int getLeftAreaRange() const;
    int getRightAreaRange() const;
    int getMatrixDimension() const;
    int getWindowTransformMode() const;

    //SETTERS
    void setAreaCheckStatus(const bool status);
    void setConstant(const unsigned int constant);
    void setRangeArea(const QPair<int, int>& area);
    void setGammaConst(const int gamma);
    void setLeftAreaRange(const int val);
    void setRightAreaRange(const int val);
    void setMatrixDimension(const int val);
    void setWindowTransformMode(const int val);

};

#endif // TRANSFORMOPTIONS_H
