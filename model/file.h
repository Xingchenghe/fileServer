//
// Created by jiang on 19-3-21.
//
#pragma once
#ifndef FILESERVER_FILE_H
#define FILESERVERy7_FILE_H

#include <string>
#include <memory>
using std::string;

class file
{
protected:
    time_t lastModifiedTime;
    std::string md5;
    std::string clientPath;
public:
    file(std::string clientPath, std::string md5, time_t lastModifiedTime);
    file()= default;
    time_t get_lastModifiedTime();
    std::string get_md5();
    std::string get_clientPath()const;
    void setLastModifiedTime(time_t lastModifiedTime);
    void setMd5(const string &md5);
    void setClientPath(const string &Path);
};

class devicefile:public file
{
private:
    int dev_id;
    int type;  //type:0 normal,1 modified,2 deleted
public:
    devicefile():dev_id(-1),type(-1),file(){}

    int getDevId() const;

    void setDevId(int devId);

    int getType() const;

    void setType(int type);
};



using dev_file_ptr=std::shared_ptr<devicefile>;

#endif //FILESERVER_FILE_H
