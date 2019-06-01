//
// Created by jiang on 19-3-25.
//

#include "common.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
errJson::errJson(actType act, std::string what):act(act),errinfo(std::move(what))
{

}

std::string errJson::toJson()
{
    boost::property_tree::ptree pt;
    pt.put("action",act);
    pt.put("errinfo",errinfo);
    std::stringstream ss;
    boost::property_tree::write_json(ss,pt);
    return ss.str();
}

sessionMgr sessionmgr;

config cfg("config.ini");