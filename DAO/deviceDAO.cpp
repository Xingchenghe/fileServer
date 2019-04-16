//
// Created by jiang on 19-4-7.
//

#include "deviceDAO.h"

dev_ptr deviceDAO::selectByNameAndMac(const string &username, const string &mac)
{
    connect();
    string select="select "+SELECT_FIELDS+" from "+TABLE_NAME+" where name= \""+username+"\" and dev_mac=\""+mac+"\"";
    res=stat->executeQuery(select);
    dev_ptr dev=std::make_shared<device>(device());
    if(res->next())
    {
        dev->setDevId(res->getInt("dev_id"));
        dev->setUsername(res->getString("name"));
        dev->setDevMac(res->getString("dev_mac"));
        disconnect();
        return dev;
    }
    disconnect();
    return nullptr;
}

bool deviceDAO::addDevice(device dev)
{
    dev_ptr devPtr=selectByNameAndMac(dev.getUsername(),dev.getDevMac());
    if(devPtr!= nullptr)
        return false;
    else
    {
        connect();
        string insert="insert into "+TABLE_NAME+"("+TABLE_FIELDS+") values(\""+dev.getUsername()+"\",\""+dev.getDevMac()+"\")";
        execute(insert);
        disconnect();
        return true;
    }
}
