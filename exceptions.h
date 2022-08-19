/***************************************************************************
 *                                                                         *
 *   Copyright (C) 19.08.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <iostream>

class Exception : public std::exception
{
protected:
    std::string error_msg;
public:
    virtual const char* what() const override = 0;
    virtual ~Exception() = default;
};


class ImageExistanceError : public Exception
{
public:
    ImageExistanceError(const std::string& error);
    const char* what() const override;
};

#endif // EXCEPTIONS_H
