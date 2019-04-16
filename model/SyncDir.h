//
// Created by jiang on 19-4-6.
//

#ifndef FILESERVER_SYNCDIR_H
#define FILESERVER_SYNCDIR_H

#include <string>
#include <memory>
using std::string;
class SyncDir
{
private:
    string username;
    string device_mac;
    string client_path;
public:
    SyncDir(string name,string dm,string cp):username(name),device_mac(dm),client_path(cp){}

    SyncDir():username(""),device_mac(""),client_path(""){}

    const string &getUsername() const;

    void setUsername(const string &username);

    const string &getDeviceMac() const;

    void setDeviceMac(const string &deviceMac);

    const string &getClientPath() const;

    void setClientPath(const string &clientPath);

};

using sync_dir_ptr=std::shared_ptr<SyncDir>;
#endif //FILESERVER_SYNCDIR_H
