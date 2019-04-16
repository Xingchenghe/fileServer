//
// Created by jiang on 19-4-8.
//

#ifndef FILESERVER_SENDSERVICE_H
#define FILESERVER_SENDSERVICE_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "../common/common.h"

class SendService
{
private:
    boost::property_tree::ptree pt;
    string path;
    string md5;
public:
    string sendFail();
    string sendReady();
};


#endif //FILESERVER_SENDSERVICE_H
