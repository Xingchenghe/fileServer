//
// Created by jiang on 19-5-23.
//

#include "HashTree.h"
#include "../common/md5.h"

HashTree::HashTree(const string& path)
{
    currDir=path;
    CreateTree(path);
    countHash();
}

void HashTree::CreateTree(const string& p)
{
    node_ptr node=make_shared<TreeNode>(p);
    if(!is_directory(p)||boost::filesystem::is_empty(p))
    {
        node->setHash(md5(node->getPath().substr(currDir.length())+to_string(node->getLastmodifiedtime())));
        root=node;
    }
    else if(is_directory(p)&&!(boost::filesystem::is_empty(p)))
    {
        initHashTreeRoot(p);
    }
}

void HashTree::initHashTreeRoot(const string &p)
{
    if(!is_directory(p)||boost::filesystem::is_empty(p))
    {
        node_ptr subtreeNode=make_shared<TreeNode>(p);
        filestack.push(subtreeNode);
    }
    else
    {
        node_ptr subtreeFileNode=make_shared<TreeNode>(p);
        filestack.push(subtreeFileNode);
        if(!boost::filesystem::is_empty(p))
        {
            boost::filesystem::path dirpath = p;
            boost::filesystem::directory_iterator end;// 只支持本层目录遍历
            for (boost::filesystem::directory_iterator iter(dirpath); iter != end; iter++)
            {
                boost::filesystem::path p = *iter;
                initHashTree(p.string(),subtreeFileNode);
            }
        }
    }
}

void HashTree::initHashTree(const string &p, node_ptr treenode)
{
    if(!is_directory(p)||(is_directory(p)&&boost::filesystem::is_empty(p)))
    {
        node_ptr subtreeNode=make_shared<TreeNode>(p,treenode);
        filestack.push(subtreeNode);
        addChildToStack(treenode,subtreeNode);
    }
    else if(is_directory(p)&&!(boost::filesystem::is_empty(p)))
    {
        node_ptr subFileNode=make_shared<TreeNode>(p,treenode);
        filestack.push(subFileNode);
        addChildToStack(treenode,subFileNode);
        if(!boost::filesystem::is_empty(p))
        {
            boost::filesystem::path dirpath = p;
            boost::filesystem::directory_iterator end;// 只支持本层目录遍历
            for (boost::filesystem::directory_iterator iter(dirpath); iter != end; iter++)
            {
                boost::filesystem::path p = *iter;
                initHashTree(p.string(),subFileNode);
            }
        }
    }
}


void HashTree::countHash()
{
    node_ptr tempNode=make_shared<TreeNode>();
    while(!filestack.empty())
    {
        tempNode=filestack.top();
        filestack.pop();
        if(tempNode->getChildList().empty())
        {
            tempNode->setHash(md5(tempNode->getPath().substr(currDir.length())+to_string(tempNode->getLastmodifiedtime())));
//            cout<<tempNode->getPath().substr(currDir.length())+to_string(tempNode->getLastmodifiedtime())<<endl;
            addChildToHashmap(tempNode);
        }
        else
        {
            string md5V;
            set<string> valset;
            for(auto m:tempNode->getHashmap())
            {
                valset.insert(m.second);
            }
            for(auto m:valset)
            {
                md5V+=m;
            }
            tempNode->setHash(md5(md5V));
            if(!filestack.empty())
            {
                addChildToHashmap(tempNode);
            }
        }
    }
    root=tempNode;
}

void HashTree::addChildToStack(node_ptr fnode,node_ptr subnode)
{
    stack<node_ptr> tmpstk;
    while (!filestack.empty()&&filestack.top()!=fnode)
    {
        tmpstk.push(filestack.top());
        filestack.pop();
    }
    filestack.top()->getChildList().push_back(subnode);
//    filestack.top()->getChildSet().insert(subnode);
    while (!tmpstk.empty())
    {
        filestack.push(tmpstk.top());
        tmpstk.pop();
    }
}

void HashTree::addChildToHashmap(node_ptr tempnode)
{
    stack<node_ptr> tmpstk;
    while (!filestack.empty()&&filestack.top()!=tempnode->getFather())
    {
        tmpstk.push(filestack.top());
        filestack.pop();
    }
    filestack.top()->getHashmap()[tempnode->getFilename()]=tempnode->getHash();
    while (!tmpstk.empty())
    {
        filestack.push(tmpstk.top());
        tmpstk.pop();
    }
}

const node_ptr &HashTree::getRoot() const {
    return root;
}
