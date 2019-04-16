//
// Created by jiang on 19-4-11.
//

#ifndef FILESERVER_DEVICEFILEDAO_H
#define FILESERVER_DEVICEFILEDAO_H

#include "../model/file.h"
#include "mysqlConn.h"

class deviceFileDAO:public mysqlConn
{
private:
    const string TABLE_NAME=" devicefile ";
    const string TABLE_FIELDS = " dev_id, type,path,last_modified_time,md5 ";
    const string SELECT_FIELDS = TABLE_FIELDS;
public:
    bool insertfile(devicefile devFile);
    bool insertfileNoConn(devicefile devFile);
    dev_file_ptr selectByDevidAndPath(int dev_id,string path);
    dev_file_ptr selectByDevidAndPathNoConn(int dev_id,string path);
};


#endif //FILESERVER_DEVICEFILEDAO_H
