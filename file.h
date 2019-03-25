//
// Created by jiang on 19-3-21.
//

#ifndef FILESERVER_FILE_H
#define FILESERVERy7_FILE_H
#include <string>

class file
{
public:
    file(std::string filename, std::string lastModifiedTime, std::string md5, std::string clientPath, int size,std::string serverPath);
    std::string get_filename();
    std::string get_lastModifiedTime();
    std::string get_md5();
    std::string get_clientPath();
    std::string get_serverPath();
    int get_size();
protected:
    std::string filename;
    std::string lastModifiedTime;
    std::string md5;
    std::string clientPath;
    std::string serverPath;
    int size;
};

#endif //FILESERVER_FILE_H
