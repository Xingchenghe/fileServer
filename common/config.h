//
// Created by jiang on 19-5-25.
//

#ifndef FILESERVER_CONFIG_H
#define FILESERVER_CONFIG_H

#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>
using std::string;
class config
{
private:
    int ctrl_port;
    int data_port;
    string basePath;
    string syncdir;
    string db_addr;
    string db_username;
    string db_pwd;
public:
    int getCtrlPort() const;

    void setCtrlPort(int ctrlPort);

    int getDataPort() const;

    void setDataPort(int dataPort);

    const string &getBasePath() const;

    void setBasePath(const string &basePath);

    const string &getSyncdir() const;

    void setSyncdir(const string &syncdir);

    const string &getDbAddr() const;

    void setDbAddr(const string &dbAddr);

    const string &getDbUsername() const;

    void setDbUsername(const string &dbUsername);

    const string &getDbPwd() const;

    void setDbPwd(const string &dbPwd);

    explicit config(const string& path);
};


#endif //FILESERVER_CONFIG_H
