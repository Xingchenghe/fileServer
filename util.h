//
// Created by jiang on 19-3-21.
//

#ifndef FILESERVER_UTIL_H
#define FILESERVER_UTIL_H
#include <string>
#include <fstream>
#include "md5.h"

std::string  Get_Current_Date();

std::string Get_File_Md5(std::string filePath);
#endif //FILESERVER_UTIL_H
