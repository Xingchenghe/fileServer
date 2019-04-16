//
// Created by jiang on 19-4-11.
//

#include "DeviceFileService.h"

bool DeviceFileService::insertOne(devicefile &devFile)
{
    deviceFileDAO devfileDao;
    return devfileDao.insertfile(devFile);
}

bool DeviceFileService::insertMulti(vector<devicefile> &devFileVec)
{
    deviceFileDAO devFileDao;
    devFileDao.connect();
    for(auto &f:devFileVec)
        devFileDao.insertfileNoConn(f);
    devFileDao.disconnect();
    return true;
}
