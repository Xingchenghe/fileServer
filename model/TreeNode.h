//
// Created by jiang on 19-5-23.
//

#ifndef FILESERVER_TREENODE_H
#define FILESERVER_TREENODE_H


#include <string>
#include <set>
#include <map>
#include <memory>
#include <boost/filesystem.hpp>
using namespace std;
using namespace boost::filesystem;
class TreeNode
{
    using node_ptr=std::shared_ptr<TreeNode>;
private:
    string hash;
    node_ptr father;
    string filename;
    string path;
    long lastmodifiedtime;
    map<string,string> hashmap;
    list<node_ptr> childList;
    set<node_ptr> childSet;
public:
    map<string, string> &getHashmap();
    void setHashmap(const map<string, string> &hashmap);
    void addHashMap(const string& subfilename,const string& MD5);

    TreeNode(node_ptr father, const string &filename, const string &path, long lastmodifiedtime);

    explicit TreeNode(const string& p);

    TreeNode(const string &p, node_ptr f);

    TreeNode()= default;

    const string &getFilename() const;

    void setFilename(const string &filename);

    const node_ptr &getFather() const;

    const string &getPath() const;

    void setPath(const string &path);

    const string &getHash() const;

    list<node_ptr> & getChildList();

    set<node_ptr> & getChildSet();

    long getLastmodifiedtime() const;

    void setHash(const string &hash);

    void setLastmodifiedtime(long lastmodifiedtime);


};

using node_ptr=std::shared_ptr<TreeNode>;


#endif //FILESERVER_TREENODE_H
