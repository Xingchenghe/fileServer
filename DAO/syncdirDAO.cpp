//
// Created by jiang on 19-4-6.
//

#include "syncdirDAO.h"

sync_dir_ptr syncdirDAO::selectByUsernameAndMac(string username, string mac)
{
    connect();
    string select="select "+SELECT_FIELDS+" from "+TABLE_NAME+" where name= \""+username+"\" and device_mac=\""+mac+"\"";
    res=stat->executeQuery(select);
    sync_dir_ptr syncDirPtr=std::make_shared<SyncDir>(SyncDir());
    if(res->next())
    {
        syncDirPtr->setUsername(res->getString("name"));
        syncDirPtr->setDeviceMac(res->getString("device_mac"));
        syncDirPtr->setClientPath(res->getString("client_path"));
        disconnect();
        return syncDirPtr;
    }
    disconnect();
    return nullptr;
}

bool syncdirDAO::addSyncDir(SyncDir syncDir)
{
    connect();
    string insert="insert into "+TABLE_NAME+" values (\""+syncDir.getUsername()+"\",\""+syncDir.getDeviceMac()+"\",\""+syncDir.getClientPath()+"\"";
    execute(insert);
    disconnect();
    return true;
}

bool syncdirDAO::updateSyncDir(string username, string mac, string path)
{
    sync_dir_ptr syncDirPtr=selectByUsernameAndMac(username,mac);
    if(syncDirPtr==nullptr)
    {
        syncDirPtr->setClientPath(path);
        addSyncDir(*syncDirPtr);
        return true;
    }
    else
    {
        string oldpath=syncDirPtr->getClientPath();
        string updatedPath;
        if(oldpath.length()==0)
        {
            updatedPath=path;
        }
        else
        {
            updatedPath=oldpath+","+path;
        }
        string update="update "+TABLE_NAME+" set client_path=\""+updatedPath+"\" where name=\""+username+"\" and device_mac=\""+mac+"\"";
        execute(update);
        return true;
    }
}
