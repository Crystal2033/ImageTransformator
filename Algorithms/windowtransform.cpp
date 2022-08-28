/***************************************************************************
 *                                                                         *
 *   Copyright (C) 27.08.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "windowtransform.h"
#include "ImageMiscellaneous/imagefunctions.h"

void WindowTransform::setMatrixOptions(const int constantNum, const int mode)
{
    if(matrixType == AVERAGE)
    {
        setMatrixSize(constantNum);
            int summOfMatrix = 0;

            for(int i = 0; i < matrix.size(); i++)
            {
                for(int j = 0; j < matrix.size(); j++)
                {
                    matrix[i].append(1);
                    summOfMatrix += matrix[i][j];
                }
            }

            averageMatrixCoeff = 1/double(summOfMatrix);
    }
    else if(matrixType == GAUSS)
    {
        int shiftRelatedImage = matrix.size() / 2;
        setMatrixSize(constantNum * 6 + 1);
        double summOfMatrix = 0.0;
        int gammaNumber = constantNum;
        double gaussResult = 0.0;
        for(int i = 0; i < matrix.size(); i++)
        {
            for(int j = 0; j < matrix.size(); j++)
            {
                gaussResult = gauss(gammaNumber, i - shiftRelatedImage, j - shiftRelatedImage);
                summOfMatrix += gaussResult;
                matrix[i].append(gaussResult);
            }
        }
        averageMatrixCoeff = 1/double(summOfMatrix);
    }
    else if(matrixType == LAPLASS)
    {
        setMatrixSize(constantNum);
        switch (mode) {
            case 0:
            {
                matrix = {{-1, -1, -1}, {1, 1, 1}, {0, 0, 0}};
                break;
            }
            case 1:
            {
                matrix = {{-1, -1, -1}, {0, 0, 0}, {1, 1, 1}};
                break;
            }
            case 2:
            {
               matrix = {{-1, 1, 0}, {-1, 1, 0}, {-1, 1, 0}};
               break;
            }
            case 3:
            {
                matrix = {{-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1}};
                break;
            }
            case 4:
            {
               matrix = {{1, 1, 1}, {1, -8, 1}, {1, 1, 1}};
               break;
            }
            case 5:
            {
                matrix = {{-1, 0, 1}, {-1, 0, 1}, {-1, 0, 1}};
                break;
            }
            default:
            {
                qDebug() << "laplassError" << Qt::endl;
            }

        }


    }
    else if(matrixType == GRADIENT)
    {
        setMatrixSize(constantNum);
        switch (mode) {
            case 0:
            {
                matrix = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
                break;
            }
            case 1:
            {
                matrix = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
                break;
            }

            default:
            {
                qDebug() << "gradientError" << Qt::endl;
            }

        }
    }
    else if(matrixType == MEDIAN)
    {
        setMatrixSize(constantNum);
    }
}

void WindowTransform::createWindowTransfOnPix(const QImage& originalImage, QImage &image, const int i, const int j)
{
    int shiftRelatedImage = matrix.size() / 2;
    double transformedPixelValue = 0.0;

    if(matrixType == MEDIAN)
    {
        QVector<int> matrixInVector;
        for(int k = 0; k < matrix.size(); ++k)
        {
            for (int p = 0; p < matrix.size(); ++p)
            {
                matrixInVector.append(*getPixByWindow(const_cast<uchar*>(originalImage.bits()), i, j, k - shiftRelatedImage, p - shiftRelatedImage, originalImage.size()));
            }
        }
        std::sort(matrixInVector.begin(), matrixInVector.end());

        transformedPixelValue = matrixInVector[matrixInVector.size() / 2];

    }
    else if(matrixType != MEDIAN)
    {
        for(int k = 0; k < matrix.size(); ++k)
        {
            for (int p = 0; p < matrix.size(); ++p)
            {
                transformedPixelValue = transformedPixelValue + matrix[k][p] * *getPixByWindow(const_cast<uchar*>(originalImage.bits()), i, j, k - shiftRelatedImage, p - shiftRelatedImage, originalImage.size());
            }
        }
        transformedPixelValue *= averageMatrixCoeff;
    }


    uchar* px = ImageFunctions::getPixByIndexes(image.bits(), i, j, image.width());
    if(transformedPixelValue > BRIGHTNESS_MAX - 1)
    {
        *px++ = *px++ = *px++ = BRIGHTNESS_MAX - 1;
    }
    else if(transformedPixelValue <= 0)
    {
        *px++ = *px++ = *px++ = 0;
    }
    else
    {
        *px++ = *px++ = *px++ = int(transformedPixelValue);
    }
}

uchar *WindowTransform::getPixByWindow(uchar* startImagePx, const int i, const int j, const int k, const int p, const QSize& size) const
{
    int row = 0, column = 0;
    row = i + k;
    if(row < 0 || row >= size.height())
    {
        row = i - k;
    }

    column = j + p;
    if (column < 0 || column >= size.width())
    {
        column = j - p;
    }
    return ImageFunctions::getPixByIndexes(startImagePx, row, column, size.width());

}


void WindowTransform::clearMatrix()
{
    for(int i = 0; i < matrix.size(); i++)
    {
        matrix[i].clear();
    }
    matrix.clear();
}

WindowTransform::WindowTransform(const TransformMatrixes type)
{
    matrixType = type;
}

void WindowTransform::setMatrixSize(const int matrixSize)
{
    clearMatrix();
    for(int i = 0; i < matrixSize; i++)
    {
        matrix.append(QVector<double>{});
    }
}

double WindowTransform::gauss(const int gamma, const int x, const int y)
{
    return double (1/(2*M_PI * qPow(gamma, 2)) * qExp((-qPow(x, 2) - qPow(y, 2))/(2*qPow(gamma, 2))));
}



void WindowTransform::transform(const QImage &image, ImageWidget *&imageWidget, const TransformOptions* options)
{
    if(options != nullptr){
        setMatrixOptions(options->getConstant(), options->getWindowTransformMode());
    }

    QImage* transformedImage = new QImage(image);
    for(int i = 0; i < image.height(); i++)
    {
        for(int j = 0; j < image.width(); j++)
        {
            createWindowTransfOnPix(image, *transformedImage, i, j);
        }
    }

    imageWidget->setImage(*transformedImage, transformedImage->size());
    delete transformedImage;
}
