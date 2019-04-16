//
// Created by jiang on 19-4-11.
//

#ifndef FILESERVER_DEVICEFILESERVICE_H
#define FILESERVER_DEVICEFILESERVICE_H

#include "../DAO/deviceFileDAO.h"
#include <vector>
using std::vector;
class DeviceFileService
{
public:
    bool insertOne(devicefile &devFile);
    bool insertMulti(vector<devicefile>& devFileVec);
};


#endif //FILESERVER_DEVICEFILESERVICE_H
