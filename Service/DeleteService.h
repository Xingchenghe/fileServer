//
// Created by jiang on 19-4-14.
//

#ifndef FILESERVER_DELETESERVICE_H
#define FILESERVER_DELETESERVICE_H

#include "../common/common.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <string>
using std::string;
class DeleteService
{
public:
    string DelSuccess(const string& path);
    string DelFail(const string& path);
};


#endif //FILESERVER_DELETESERVICE_H
