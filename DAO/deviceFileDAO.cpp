//
// Created by jiang on 19-4-11.
//

#include "deviceFileDAO.h"
#include "../model/device.h"
bool deviceFileDAO::insertfile(devicefile devFile)
{
    dev_file_ptr devFilePtr=selectByDevidAndPath(devFile.getDevId(),devFile.get_clientPath());
    if(devFilePtr!= nullptr)
        return false;
    else
    {
        connect();
        string insert="insert into "+TABLE_NAME+"("+TABLE_FIELDS+") values("+std::to_string(devFile.getDevId())+","+std::to_string(devFile.getType())+",\""+devFile.get_clientPath()+"\","+std::to_string(devFile.get_lastModifiedTime())+",\""+devFile.get_md5()+"\")";
        execute(insert);
        disconnect();
        return true;
    }
}

dev_file_ptr deviceFileDAO::selectByDevidAndPath(int dev_id, string path)
{
    connect();
    string select="select "+SELECT_FIELDS+" from "+TABLE_NAME+" where dev_id= "+std::to_string(dev_id)+" and path=\""+path+"\"";
    res=stat->executeQuery(select);
    dev_file_ptr devFilePtr=std::make_shared<devicefile>(devicefile());
    if(res->next())
    {
        devFilePtr->setDevId(res->getInt("dev_id"));
        devFilePtr->setType(res->getInt("type"));
        devFilePtr->setClientPath(res->getString("path"));
        devFilePtr->setLastModifiedTime(res->getInt("last_modified_time"));
        devFilePtr->setMd5(res->getString("md5"));
        disconnect();
        return devFilePtr;
    }
    disconnect();
    return nullptr;
}

bool deviceFileDAO::insertfileNoConn(devicefile devFile)
{
    dev_file_ptr devFilePtr=selectByDevidAndPathNoConn(devFile.getDevId(),devFile.get_clientPath());
    if(devFilePtr!= nullptr)
        return false;
    else
    {
        string insert="insert into "+TABLE_NAME+"("+TABLE_FIELDS+") values("+std::to_string(devFile.getDevId())+","+std::to_string(devFile.getType())+",\""+devFile.get_clientPath()+"\","+std::to_string(devFile.get_lastModifiedTime())+",\""+devFile.get_md5()+"\")";
        execute(insert);
        return true;
    }
}

dev_file_ptr deviceFileDAO::selectByDevidAndPathNoConn(int dev_id, string path)
{
    string select="select "+SELECT_FIELDS+" from "+TABLE_NAME+" where dev_id= "+std::to_string(dev_id)+" and path=\""+path+"\"";
    res=stat->executeQuery(select);
    dev_file_ptr devFilePtr=std::make_shared<devicefile>(devicefile());
    if(res->next())
    {
        devFilePtr->setDevId(res->getInt("dev_id"));
        devFilePtr->setType(res->getInt("type"));
        devFilePtr->setClientPath(res->getString("path"));
        devFilePtr->setLastModifiedTime(res->getInt("last_modified_time"));
        devFilePtr->setMd5(res->getString("md5"));
        return devFilePtr;
    }
    return nullptr;
}
