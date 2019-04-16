//
// Created by jiang on 19-4-7.
//

#include <algorithm>
#include "sessionMgr.h"
//#include "model/file.h"

bool sessionMgr::hasLoginInstance(const string& username)
{
    auto it=connectedUserSet.find(username);
    return !(it == connectedUserSet.end());
}

bool sessionMgr::addUser(const string& username)
{
    connectedUserSet.insert(username);
}

bool sessionMgr::removeUser(const string& username)
{
    connectedUserSet.erase(username);
}

bool sessionMgr::isDevcieLogin(const device& dev)
{
    auto dev_lst=connectedUsernameDeviceMap[dev.getUsername()];
    auto it=std::find(dev_lst.begin(),dev_lst.end(),dev.getDevMac());
    return !(it == dev_lst.end());
}

bool sessionMgr::insertDevice(const device& dev)
{
    connectedUsernameDeviceMap[dev.getUsername()].insert(dev.getDevMac());
    return true;
}

bool sessionMgr::isDeviceLogin(const string& username, const string& mac)
{
    auto dev_lst=connectedUsernameDeviceMap[username];
    auto it=std::find(dev_lst.begin(),dev_lst.end(),mac);
    return !(it == dev_lst.end());
}

bool sessionMgr::insertDevice(const string& username, const string& mac)
{
    connectedUsernameDeviceMap[username].insert(mac);
    return true;
}

bool sessionMgr::removeDevice(const string &username, const string &mac)
{
    return connectedUsernameDeviceMap[username].erase(mac);
}

bool sessionMgr::isUserDeviceEmpty(const string &username)
{
    return connectedUsernameDeviceMap[username].empty();
}

bool sessionMgr::isInConnectedEndpoint(const string &addr)
{
    return (connectedEndpointSet.find(addr)!=connectedEndpointSet.end());
}

bool sessionMgr::insertIntoConnectedEndpoint(const string& addr)
{
    connectedEndpointSet.insert(addr);
    return true;
}

bool sessionMgr::removeFromConnectedEndpoint(const string &addr)
{
    return connectedEndpointSet.erase(addr);
}

bool sessionMgr::insertIntoConnectedEndpointDevMap(const string &addr, device dev)
{
    connectedEndpointDevMap[addr]=dev;
    return true;
}

bool sessionMgr::removeFromConnectedEndpointDevMap(const string &addr)
{
    connectedEndpointDevMap.erase(addr);
    return true;
}

string sessionMgr::getUsernameByAddress(string addr)
{
    return connectedEndpointDevMap[addr].getUsername();
}

device sessionMgr::getDeviceByAddr(const string &addr)
{
    return connectedEndpointDevMap[addr];
}

bool sessionMgr::insertIntoFileToRsvMap(const string &username, userfile ufile)
{
    file_to_rsv_map[username].push_back(ufile);
    return true;
}

bool sessionMgr::removeFromFileToRsvMapByFilename(const string &username, const string &filename)
{
    auto rsvVec=file_to_rsv_map[username];
    auto it=rsvVec.begin();
    while (it!=rsvVec.end())
    {
        string filepath=it->get_clientPath();
        if(filepath.find(filename)!=filepath.npos)
        {
            file_to_rsv_map[username].erase(it);
            return true;
        }
        it++;
    }
    return false;
}

bool sessionMgr::getUserfileToRsvByUsernameAndFilename(const string &username, const string &filename,userfile& file)
{
    auto rsvSet=file_to_rsv_map[username];
    auto it=rsvSet.begin();
    while (it!=rsvSet.end())
    {
        string filepath=it->get_clientPath();
        if(filepath.find(filename)!=filepath.npos)
        {
            file=*it;
            return true;
        }
        it++;
    }
    return false;
}

bool sessionMgr::removeUserFromFileToRsvMap(const string &username)
{
    return file_to_rsv_map.erase(username);
}

bool sessionMgr::addAddrSessMap(string addr, sess_ptr sptr) {
    addr_sess_map[addr]=sptr;
    return true;
}

sess_ptr sessionMgr::getSessByAddr(string addr)
{
    return reinterpret_cast<const shared_ptr<session> &>(file_to_rsv_map[addr]);
}

bool sessionMgr::removeAddrSessMap(string addr) {
    return file_to_rsv_map.erase(addr);
}



