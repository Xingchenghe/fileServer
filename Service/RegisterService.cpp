//
// Created by jiang on 19-4-5.
//

#include "RegisterService.h"
#include "../DAO/userDAO.h"

bool RegisterService::Register()
{
    userDAO userDao;
    user_ptr user=userDao.selectByName(username);
    if(user== nullptr)
    {
        if(password=="")
        {
            successFlag=1;
            return false;
        }
        else
        {
            User user;
            user.setUsername(username);
            user.setPassword(password);
            user.setSalt(salt);
            userDao.addUser(user);
            successFlag=0;
            return true;
        }
    }
    else
    {
        successFlag=2;
        return false;
    }
}

string RegisterService::resultStr() {
    boost::property_tree::ptree pt;
    if(successFlag==0)
    {
        pt.put("action",REGISTERSUCCESS);
    }
    else if(successFlag==1)
    {
        pt.put("action",REGISTERFAIL);
        pt.put("info","password can not be empty");
    }
    else if(successFlag==2)
    {
        pt.put("action",REGISTERFAIL);
        pt.put("info","username existed");
    }
    std::stringstream ss;
    boost::property_tree::write_json(ss,pt);
    return ss.str();
}
