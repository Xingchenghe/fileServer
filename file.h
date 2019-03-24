//
// Created by jiang on 19-3-21.
//

#ifndef FILESERVER_FILE_H
#define FILESERVERy7_FILE_H
#include <string>
class file
{
public:
    file(std::string filename, std::string lastModifiedTime, std::string md5, std::string clientPath, long long size);
    std::string get_filename();
    std::string get_lastModifiedTime();
    std::string get_md5();
    std::string get_clientPath();
    long long get_size();
private:
    std::string filename;
    std::string lastModifiedTime;
    std::string md5;
    std::string clientPath;
    long long size;
};

#endif //FILESERVER_FILE_H
