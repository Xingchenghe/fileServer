//
// Created by jiang on 19-4-7.
//

#ifndef FILESERVER_DEVICESERVICE_H
#define FILESERVER_DEVICESERVICE_H

#include "../DAO/deviceDAO.h"

class DeviceService
{
private:
    string username;
    string dev_mac;
public:
    DeviceService(string user,string mac):username(user),dev_mac(mac){}
    bool isDeviceExist();
    bool addDevice();
    int getIdbyUsernameAndMac(string username,string mac);
};


#endif //FILESERVER_DEVICESERVICE_H
