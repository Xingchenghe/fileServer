//
// Created by jiang on 19-4-12.
//

#include "userFileDAO.h"
#include <iostream>
using namespace std;
bool userFileDAO::insertfile(userfile ufile)
{
    usr_file_ptr usrFilePtr=selectByUsernameAndPath(ufile.getOwner(),ufile.get_clientPath());
    if(usrFilePtr!= nullptr)
    {
        return false;
    }
    else
    {
        connect();
        string insert="insert into "+TABLE_NAME+"("+TABLE_FIELDS+") values(\""+ufile.getOwner()+"\","+std::to_string(ufile.getType())+","+std::to_string(ufile.get_lastModifiedTime())+",\""+ufile.get_clientPath()+"\",\""+ufile.get_md5()+"\")";
        execute(insert);
        disconnect();
        return true;
    }
}


usr_file_ptr userFileDAO::selectByUsernameAndPath(const string& username, const string& path)
{
    connect();
    string select="select "+SELECT_FIELDS+" from "+TABLE_NAME+" where owner=\""+username+"\" and path=\""+path+"\"";
    res=stat->executeQuery(select);
    usr_file_ptr usrFilePtr=std::make_shared<userfile>(userfile());
    if(res->next())
    {
        usrFilePtr->setOwner(res->getString("owner"));
        usrFilePtr->setType(res->getInt("type"));
        usrFilePtr->setClientPath(res->getString("path"));
        usrFilePtr->setLastModifiedTime(res->getInt("last_modified_time"));
        usrFilePtr->setMd5(res->getString("md5"));
        disconnect();
        return usrFilePtr;
    }
    disconnect();
    return nullptr;
}

bool userFileDAO::insertTransFile(userfile ufile)
{
    usr_file_ptr usrFilePtr=selectTransFileByUsernameAndPath(ufile.getOwner(),ufile.get_clientPath());
    if(usrFilePtr!= nullptr)
    {
        return false;
    }
    else
    {
        connect();
        string insert="insert into "+TRANSFER_TABLE_NAME+"("+TABLE_FIELDS+") values(\""+ufile.getOwner()+"\","+std::to_string(ufile.getType())+","+std::to_string(ufile.get_lastModifiedTime())+",\""+ufile.get_clientPath()+"\",\""+ufile.get_md5()+"\")";
        execute(insert);
        disconnect();
        return true;
    }
}

bool userFileDAO::removeTransFileByUsernameAndPath(const string& username, const string& path)
{
    usr_file_ptr usrFilePtr=selectTransFileByUsernameAndPath(username,path);
    if(usrFilePtr== nullptr)
        return false;
    else
    {
        connect();
        string del="delete from "+TRANSFER_TABLE_NAME+" where owner=\""+username+"\" and path=\""+path+"\"";
        execute(del);
        disconnect();
        return true;
    }
}

usr_file_ptr userFileDAO::selectTransFileByUsernameAndPath(const string& username, const string& path) {
    connect();
    string select="select "+SELECT_FIELDS+" from "+TRANSFER_TABLE_NAME+" where owner=\""+username+"\" and path=\""+path+"\"";
    res=stat->executeQuery(select);
    usr_file_ptr usrFilePtr=std::make_shared<userfile>(userfile());
    if(res->next())
    {
        usrFilePtr->setOwner(res->getString("owner"));
        usrFilePtr->setType(res->getInt("type"));
        usrFilePtr->setClientPath(res->getString("path"));
        usrFilePtr->setLastModifiedTime(res->getInt("last_modified_time"));
        usrFilePtr->setMd5(res->getString("md5"));
        disconnect();
        return usrFilePtr;
    }
    disconnect();
    return nullptr;
}

vector<userfile> userFileDAO::getUserFilesByUserName(const string& username)
{
    vector<userfile> userfiles;
    connect();
    string select="select "+SELECT_FIELDS+" from "+TABLE_NAME+" where owner=\""+username+"\"";
    res=stat->executeQuery(select);
    while (res->next())
    {
        userfile ufile;
        ufile.setOwner(res->getString("owner"));
        ufile.setType(res->getInt("type"));
        ufile.setClientPath(res->getString("path"));
        ufile.setLastModifiedTime(res->getInt("last_modified_time"));
        ufile.setMd5(res->getString("md5"));
        userfiles.push_back(ufile);
    }
    disconnect();
    return userfiles;

}

bool userFileDAO::removeByUsernameAndPath(const string &username, const string &path)
{
    connect();
    string del="delete from "+TABLE_NAME+" where owner=\""+username+"\" and path=\""+path+"\"";
    execute(del);
    disconnect();
    return true;
}
