//
// Created by jiang on 19-5-23.
//

#ifndef FILESERVER_HASHTREE_H
#define FILESERVER_HASHTREE_H


#include "TreeNode.h"
#include <stack>
class HashTree
{
private:
    node_ptr root;
    string path;
    stack<node_ptr> filestack;
public:
    string currDir;
    explicit HashTree(const string& path);
    void CreateTree(const string& p);
    void countHash();
    void initHashTreeRoot(const string& p);
    void initHashTree(const string &p, node_ptr treenode);
    void addChildToStack(node_ptr fnode,node_ptr subnode);

    const node_ptr &getRoot() const;

    void addChildToHashmap(node_ptr tempnode);
};

#endif //FILESERVER_HASHTREE_H
