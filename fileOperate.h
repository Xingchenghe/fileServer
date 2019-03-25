//
// Created by jiang on 19-3-25.
//

#ifndef FILESERVER_FILEOPERATE_H
#define FILESERVER_FILEOPERATE_H

#include "file.h"
#include "common.h"
#include <string>
class fileOperate:public file{
private:
    actType act;
public:
    fileOperate(std::string filename, std::string lastModifiedTime, std::string md5, std::string clientPath, int size,std::string serverPath,actType act);
    std::string toJson();
};


#endif //FILESERVER_FILEOPERATE_H
