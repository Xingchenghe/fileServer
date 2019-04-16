//
// Created by jiang on 19-4-7.
//

#ifndef FILESERVER_DEVICEDAO_H
#define FILESERVER_DEVICEDAO_H

#include "../model/device.h"
#include "mysqlConn.h"
#include <string>
using std::string;
class deviceDAO:public mysqlConn
{
private:
    const string TABLE_NAME=" device ";
    const string TABLE_FIELDS = " name, dev_mac ";
    const string SELECT_FIELDS = " dev_id, " + TABLE_FIELDS;
public:
    bool addDevice(device dev);
    bool removeDevice(device dev);
    dev_ptr selectByNameAndMac(const string& username, const string& mac);
};


#endif //FILESERVER_DEVICEDAO_H
