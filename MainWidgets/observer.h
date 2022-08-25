/***************************************************************************
 *                                                                         *
 *   Copyright (C) 21.08.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef OBSERVER_H
#define OBSERVER_H
#include <QImage>

class InterfaceObserver
{
public:
    virtual ~InterfaceObserver() = default;
    virtual void update(const QImage& img) = 0;
};

//class HistogramObserver : public InterfaceObserver
//{
//public:
//    HistogramObserver();
//    ~HistogramObserver() = default;
//    void update() override;
//};

#endif // OBSERVER_H
