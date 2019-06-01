//
// Created by jiang on 19-5-23.
//

#include "TreeNode.h"

map<string, string> &TreeNode::getHashmap() {
    return hashmap;
}

void TreeNode::setHashmap(const map<string, string> &hashmap) {
    TreeNode::hashmap = hashmap;
}

void TreeNode::addHashMap(const string &subfilename, const string &MD5) {
    hashmap[subfilename]=MD5;
}

TreeNode::TreeNode(node_ptr father, const string &filename, const string &path, long lastmodifiedtime) : father(father),
                                                                                                         filename(filename), path(path), lastmodifiedtime(lastmodifiedtime) {}

const string &TreeNode::getFilename() const {
    return filename;
}

void TreeNode::setFilename(const string &filename) {
    TreeNode::filename = filename;
}

const string &TreeNode::getPath() const {
    return path;
}

void TreeNode::setPath(const string &path) {
    TreeNode::path = path;
}

long TreeNode::getLastmodifiedtime() const {
    return lastmodifiedtime;
}

void TreeNode::setLastmodifiedtime(long lastmodifiedtime) {
    TreeNode::lastmodifiedtime = lastmodifiedtime;
}

TreeNode::TreeNode(const string& p)
{
    int pos=p.find_last_of("/");
    filename=p.substr(pos+1);
    path=p;
    lastmodifiedtime=last_write_time(p);
}

void TreeNode::setHash(const string &hash) {
    TreeNode::hash = hash;
}

TreeNode::TreeNode(const string &p, node_ptr f)
{
    int pos=p.find_last_of("/");
    filename=p.substr(pos+1);
    path=p;
    lastmodifiedtime=last_write_time(p);
    father=f;
}

list<node_ptr> & TreeNode::getChildList()
{
    return childList;
}

set<node_ptr> & TreeNode::getChildSet()
{
    return childSet;
}

const node_ptr &TreeNode::getFather() const {
    return father;
}

const string &TreeNode::getHash() const {
    return hash;
}
