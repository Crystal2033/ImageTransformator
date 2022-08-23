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
    unsigned int leftConstantEdge = 0;
    unsigned int rightConstantEdge = 0;
    int gammaConstant = 0;

public:
    TransformOptions();
    //GETTERS
    unsigned int getConstant() const;
    QPair<unsigned int, unsigned int> getConstEdges() const;
    int getGammaConstant() const;

    //SETTERS
    void setConstant(const unsigned int constant);
    void setConstEdges(const QPair<unsigned int, unsigned int>& numPair);
    void setGammaConst(const int gamma);

};

#endif // TRANSFORMOPTIONS_H
