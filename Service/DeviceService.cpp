//
// Created by jiang on 19-4-7.
//

#include "DeviceService.h"

bool DeviceService::isDeviceExist()
{
    deviceDAO devicedao;
    dev_ptr devPtr=devicedao.selectByNameAndMac(username,dev_mac);
    return (devPtr!=nullptr);
}

bool DeviceService::addDevice()
{
    deviceDAO devDao;
    device dev;
    dev.setDevMac(dev_mac);
    dev.setUsername(username);
    return devDao.addDevice(dev);
}

int DeviceService::getIdbyUsernameAndMac(string username, string mac)
{
    deviceDAO devDao;
    return devDao.selectByNameAndMac(username,mac)->getDevId();
}
