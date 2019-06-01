//
// Created by jiang on 19-4-18.
//

#include "ReqFileService.h"

string ReqFileService::reqReady(long lastModifiedTime)
{
    boost::property_tree::ptree pt;
    pt.put("action",REQFILEREADY);
    pt.put("path",path);
    pt.put("lastModifiedTime",lastModifiedTime);
    std::stringstream ss;
    boost::property_tree::write_json(ss,pt);
    return ss.str();
}

string ReqFileService::reqFail()
{
    boost::property_tree::ptree pt;
    pt.put("action",REQFILEFAIL);
    pt.put("path",path);
    std::stringstream ss;
    boost::property_tree::write_json(ss,pt);
    return ss.str();
}
