//
// Created by jiang on 19-4-5.
//

#ifndef FILESERVER_REGISTERSERVICE_H
#define FILESERVER_REGISTERSERVICE_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "../common/common.h"
using std::string;

class RegisterService
{
private:
    boost::property_tree::ptree pt;
    string username;
    string password;
    string salt;
    int successFlag;
public:
    RegisterService(string user,string passwd,string slt):username(user),password(passwd),salt(slt){}
    bool Register();
    string resultStr();
};


#endif //FILESERVER_REGISTERSERVICE_H
