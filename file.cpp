//
// Created by jiang on 19-3-21.
//

#include "file.h"

file::file(std::string filename, std::string lastModifiedTime, std::string md5, std::string clientPath, long long size)
{
    this->filename = filename;
    this->lastModifiedTime = lastModifiedTime;
    this->md5 = md5;
    this->clientPath = clientPath;
    this->size = size;
}

std::string file::get_filename()
{
    return filename;
}

std::string file::get_lastModifiedTime()
{
    return lastModifiedTime;
}

std::string file::get_md5()
{
    return md5;
}

std::string file::get_clientPath()
{
    return clientPath;
}

long long file::get_size()
{
    return size;
}
