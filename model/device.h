//
// Created by jiang on 19-4-7.
//

#ifndef FILESERVER_DEVICE_H
#define FILESERVER_DEVICE_H

#include <string>
#include <memory>
using std::string;
class device
{
private:
    int dev_id;
    string username;
    string dev_mac;
public:
    int getDevId() const;

    void setDevId(int devId);

    device():username(""),dev_mac(""){}

    device(string user,string mac):username(user),dev_mac(mac){}

    const string &getUsername() const;

    void setUsername(const string &username);

    const string &getDevMac() const;

    void setDevMac(const string &devMac);
};

using dev_ptr=std::shared_ptr<device>;
#endif //FILESERVER_DEVICE_H
