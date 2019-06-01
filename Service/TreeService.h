//
// Created by jiang on 19-5-23.
//

#ifndef FILESERVER_TREESERVICE_H
#define FILESERVER_TREESERVICE_H

#include "../model/HashTree.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
class TreeService
{
public:
    static string dirJson(const string& path);
    static void buildDirJson(const node_ptr& subnode, boost::property_tree::ptree &root);
};


#endif //FILESERVER_TREESERVICE_H
