//
// Created by jiang on 19-4-8.
//

#include "SendService.h"

string SendService::sendFail()
{
    pt.put("action",SNDFILEFAIL);
    pt.put("info","please login first");
    std::stringstream ss;
    boost::property_tree::write_json(ss,pt);
    return ss.str();
}

string SendService::sendReady()
{
    pt.put("action",SNDFILEREADY);
    pt.put("path",path);
    pt.put("md5",md5);
    std::stringstream ss;
    boost::property_tree::write_json(ss,pt);
    return ss.str();
}
