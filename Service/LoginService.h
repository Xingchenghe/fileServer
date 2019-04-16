//
// Created by jiang on 19-4-4.
//

#ifndef FILESERVER_LOGINSERVICE_H
#define FILESERVER_LOGINSERVICE_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "../common/common.h"
using std::string;
class LoginService
{
private:
    boost::property_tree::ptree pt;
    string username;
    string password;
public:
    void setUsername(const string &username);

    void setPassword(const string &password);

private:
    int successFlag;
public:
    LoginService(string user,string passwd):username(user),password(passwd){}
    LoginService()= default;
    bool login();
    string resultStr();
    string getSalt();
    static string notLogin();
};


#endif //FILESERVER_LOGINSERVICE_H
