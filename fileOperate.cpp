//
// Created by jiang on 19-3-25.
//

#include "fileOperate.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
using std::move;
fileOperate::fileOperate(std::string filename, std::string lastModifiedTime, std::string md5, std::string clientPath,int size, std::string serverPath, actType act):
file(move(filename),move(lastModifiedTime),move(md5),move(clientPath),size,move(serverPath)),act(act)
{

}

std::string fileOperate::toJson()
{
    boost::property_tree::ptree pt;
    pt.put("action",act);
    pt.put("filename",filename);
    pt.put("size",size);
    pt.put("lastModifiedTime",lastModifiedTime);
    pt.put("md5",md5);
    pt.put("clientPath",clientPath);
    pt.put("serverPath",serverPath);
    std::stringstream ss;
    boost::property_tree::write_json(ss,pt);
    return ss.str();
}
