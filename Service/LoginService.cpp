//
// Created by jiang on 19-4-4.
//

#include "LoginService.h"
#include "../DAO/userDAO.h"

bool LoginService::login()
{
    userDAO userDao;
    user_ptr user=userDao.selectByName(username);
    if(user== nullptr)
    {
        successFlag=1;
    }
    else
    {
        if(password==user->getPassword())
        {
            successFlag=0;
            return true;
        }
        else
            successFlag=2;
    }
    return false;
}

string LoginService::resultStr()
{
    boost::property_tree::ptree pt;
    if(successFlag==0)
    {
        pt.put("action",LOGINSUCCESS);
    }
    else if(successFlag==1)
    {
        pt.put("action",LOGINFAIL);
        pt.put("info","no such user");
    }
    else if(successFlag==2)
    {
        pt.put("action",LOGINFAIL);
        pt.put("info","wrong password");
    }
    std::stringstream ss;
    boost::property_tree::write_json(ss,pt);
    return ss.str();
}

string LoginService::notLogin()
{
    boost::property_tree::ptree pt;
    pt.put("action",LOGINFAIL);
    pt.put("info","not login");
    std::stringstream ss;
    boost::property_tree::write_json(ss,pt);
    return ss.str();
}

string LoginService::getSalt()
{
    userDAO userDao;
    return userDao.getSaltByUsername(username);
}

void LoginService::setUsername(const string &username) {
    LoginService::username = username;
}

void LoginService::setPassword(const string &password) {
    LoginService::password = password;
}

