#include <utility>

//
// Created by jiang on 19-4-18.
//

#ifndef FILESERVER_REQFILESERVICE_H
#define FILESERVER_REQFILESERVICE_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "../common/common.h"
class ReqFileService
{
private:
    string path;
public:
    ReqFileService(string p):path(std::move(p)){}
    string reqReady();
    string reqFail();
};


#endif //FILESERVER_REQFILESERVICE_H
