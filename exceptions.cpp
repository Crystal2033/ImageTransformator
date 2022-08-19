/***************************************************************************
 *                                                                         *
 *   Copyright (C) 19.08.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "exceptions.h"


ImageExistanceError::ImageExistanceError(const std::string &error)
{
    this->error_msg = error;
}

const char *ImageExistanceError::what() const
{
    return error_msg.c_str();
}
