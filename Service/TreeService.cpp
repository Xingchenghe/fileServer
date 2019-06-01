//
// Created by jiang on 19-5-23.
//

#include "TreeService.h"

#include <queue>
#include <iostream>
#include "../common/config.h"

using namespace std;

extern config cfg;

string TreeService::dirJson(const string& path)
{
    HashTree hashTree(path);
    boost::property_tree::ptree root;
    boost::property_tree::ptree subfiles;
    const auto& treeroot=hashTree.getRoot();
    root.put("type",1);
    root.put("filename",treeroot->getFilename());
    root.put("path","/");
    root.put("lastModifiedTime",treeroot->getLastmodifiedtime());
//    root.add_child("hashmap",boost::property_tree::ptree());
//    auto& hashmap=root.get_child("hashmap");
    root.put("hash",treeroot->getHash());
//    root.put("father","NULL");
    for(const auto& node:treeroot->getChildList())
    {
//        boost::property_tree::ptree ahash;
//        ahash.put("filename",node->getFilename());
//        ahash.put("hash",node->getHash());
//        hashmap.push_back(make_pair("",ahash));
        buildDirJson(node,subfiles);
    }
    root.add_child("subfiles",subfiles);
    std::stringstream ss;
    boost::property_tree::write_json(ss,root);
    return ss.str();
}

void TreeService::buildDirJson(const node_ptr& subnode, boost::property_tree::ptree &root)
{
    string abspath=subnode->getPath();
    string rpath=abspath.substr(cfg.getBasePath().length());
    rpath=rpath.substr(rpath.find("\/"));
    if(subnode->getChildList().empty())
    {
        boost::property_tree::ptree subtree;
        subtree.put("type",0);
//        subtree.put("father",subnode->getFather()->getFilename());
        subtree.put("filename",subnode->getFilename());
        subtree.put("path",rpath);
        subtree.put("lastModifiedTime",subnode->getLastmodifiedtime());
        subtree.put("hash",subnode->getHash());
        root.push_back(make_pair("",subtree));
    }
    else
    {
        boost::property_tree::ptree subdir;
        subdir.put("type",1);
//        subdir.put("father",subnode->getFather()->getFilename());
        subdir.put("filename",subnode->getFilename());
        subdir.put("path",rpath);
        subdir.put("lastModifiedTime",subnode->getLastmodifiedtime());
        subdir.put("hash",subnode->getHash());
        subdir.add_child("subfiles",boost::property_tree::ptree());
        auto& subdirfiles=subdir.get_child("subfiles");
//        subdir.add_child("hashmap",boost::property_tree::ptree());
//        auto& hmap=subdir.get_child("hashmap");
        for(auto subdirnode:subnode->getChildList())
        {
//            boost::property_tree::ptree ahash;
//            ahash.put("filename",subdirnode->getFilename());
//            ahash.put("hash",subdirnode->getHash());
//            hmap.push_back(make_pair("",ahash));
            buildDirJson(subdirnode,subdirfiles);
        }
        root.push_back(make_pair("",subdir));
    }
}
