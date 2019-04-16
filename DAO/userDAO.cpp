//
// Created by jiang on 19-4-3.
//

#include "userDAO.h"
#include <iostream>
using namespace std;
void userDAO::addUser(User user)
{
    connect();
    string insert="insert into "+TABLE_NAME+"("+TABLE_FIELDS+") values(\""+user.getUsername()+"\",\""+user.getPassword()+"\",\""+user.getSalt()+"\")";
    execute(insert);
    disconnect();
}

user_ptr userDAO::selectByName(string name)
{
    connect();
    string select="select "+SELECT_FIELDS+" from "+TABLE_NAME+" where name= \""+name+"\"";
    res=stat->executeQuery(select);
    user_ptr user=make_shared<User>(User());
    if(res->next())
    {
        user->setId(res->getInt("id"));
        user->setUsername(res->getString("name"));
        user->setPassword(res->getString("password"));
        user->setSalt(res->getString("salt"));
        disconnect();
        return user;
    }
    disconnect();
    return nullptr;
}

string userDAO::getSaltByUsername(const string &username)
{
    connect();
    string salt;
    string select="select "+SELECT_FIELDS+" from "+TABLE_NAME+" where name= \""+username+"\"";
    res=stat->executeQuery(select);
    if(res->next())
    {
        salt=res->getString("salt");
    }
    else
        salt="";
    disconnect();
    return salt;
}
