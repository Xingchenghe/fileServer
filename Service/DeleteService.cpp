//
// Created by jiang on 19-4-14.
//

#include "DeleteService.h"

string DeleteService::DelSuccess(const string& path)
{
    boost::property_tree::ptree pt;
    pt.put("action",DELSUCCESS);
    pt.put("path",path);
    std::stringstream ss;
    boost::property_tree::write_json(ss,pt);
    return ss.str();
}

string DeleteService::DelFail(const string& path)
{
    boost::property_tree::ptree pt;
    pt.put("action",DELFAIL);
    pt.put("path",path);
    std::stringstream ss;
    boost::property_tree::write_json(ss,pt);
    return ss.str();
}
