/***************************************************************************
 *                                                                         *
 *   Copyright (C) 27.08.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "windowtransform.h"

WindowTransform::WindowTransform(const TransformMatrixes type)
{
    if(type == AVERAGE)
    {
        int summOfMatrix = 0;
        int valueOfCeils;
        matrix = {{1,1,1}, {1,1,1}, {1,1,1}};
        valueOfCeils = matrix.size() * matrix[0].size();
        for(int i = 0; i < matrix.size(); ++i)
        {
            for(int j = 0; i < matrix[i].size(); ++j)
            {
                summOfMatrix += matrix[i][j];
                //valueOfCeils++;
            }
        }

        matrixCoeff = double(summOfMatrix/valueOfCeils);
    }
}

void WindowTransform::transform(const QImage &image, ImageWidget *&imageWidget)
{
    //TODO!
}
