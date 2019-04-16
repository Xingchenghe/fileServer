//
// Created by jiang on 19-4-7.
//
#pragma once
#ifndef FILESERVER_SESSIONMGR_H
#define FILESERVER_SESSIONMGR_H

#include <string>
#include <set>
#include <map>
#include <list>
#include "model/device.h"
#include <iostream>
#include <vector>
#include "model/userfile.h"
#include "session.h"

using namespace std;

class session;

class sessionMgr
{
private:
    set<string> connectedUserSet;
    set<string> connectedEndpointSet;
    map<string,set<string>> connectedUsernameDeviceMap;
    map<string,device> connectedEndpointDevMap;
    map<string,vector<userfile>> file_to_rsv_map;
    map<string,sess_ptr> addr_sess_map;
public:
    bool hasLoginInstance(const string& username);
    bool addUser(const string& username);
    bool removeUser(const string& username);
    bool isDevcieLogin(const device& dev);
    bool isDeviceLogin(const string& username,const string& mac);
    bool insertDevice(const device& dev);
    bool insertDevice(const string& username,const string& mac);
    bool removeDevice(const string& username,const string& mac);
    bool isUserDeviceEmpty(const string& username);
    bool isInConnectedEndpoint(const string& addr);
    bool insertIntoConnectedEndpoint(const string& addr);
    bool removeFromConnectedEndpoint(const string& addr);
    bool insertIntoConnectedEndpointDevMap(const string& addr,device dev);
    bool removeFromConnectedEndpointDevMap(const string& addr);
    bool insertIntoFileToRsvMap(const string &username, userfile ufile);
    bool removeUserFromFileToRsvMap(const string &username);
    bool removeFromFileToRsvMapByFilename(const string &username, const string &filename);
    bool getUserfileToRsvByUsernameAndFilename(const string& username,const string& filename,userfile& file);
    bool addAddrSessMap(string addr,sess_ptr sptr);
    sess_ptr getSessByAddr(string addr);
    bool removeAddrSessMap(string addr);
    string getUsernameByAddress(string addr);
    device getDeviceByAddr(const string& addr);
    void count(const string &username){cout<<connectedUserSet.size()<<' '<<connectedUsernameDeviceMap[username].size()<<' '<<connectedEndpointSet.size()<<' '<<file_to_rsv_map.size()<<endl;}
};


#endif //FILESERVER_SESSIONMGR_H
