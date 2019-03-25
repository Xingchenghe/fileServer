//
// Created by jiang on 19-3-21.
//

#include "file.h"

file::file(std::string filename, std::string lastModifiedTime, std::string md5, std::string clientPath, int size,std::string serverPath) :
serverPath(std::move(serverPath))
{
    this->filename = std::move(filename);
    this->lastModifiedTime = std::move(lastModifiedTime);
    this->md5 = std::move(md5);
    this->clientPath = std::move(clientPath);
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

int file::get_size()
{
    return size;
}

std::string file::get_serverPath() {
    return serverPath;
}
