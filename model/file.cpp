//
// Created by jiang on 19-3-21.
//

#include "file.h"

file::file(std::string clientPath, std::string md5, long lastModifiedTime)
{
    this->lastModifiedTime = lastModifiedTime;
    this->md5 = std::move(md5);
    this->clientPath = std::move(clientPath);
}

long file::get_lastModifiedTime()
{
    return lastModifiedTime;
}

std::string file::get_md5()
{
    return md5;
}

std::string file::get_clientPath()const
{
    return clientPath;
}

void file::setLastModifiedTime(long lastModifiedTime)
{
    file::lastModifiedTime = lastModifiedTime;
}

void file::setMd5(const string &md5)
{
    file::md5 = md5;
}

void file::setClientPath(const string &Path)
{
    file::clientPath = Path;
}

int devicefile::getDevId() const {
    return dev_id;
}

void devicefile::setDevId(int devId) {
    dev_id = devId;
}

int devicefile::getType() const {
    return type;
}

void devicefile::setType(int type) {
    devicefile::type = type;
}


