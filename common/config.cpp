//
// Created by jiang on 19-5-25.
//

#include "config.h"

config::config(const string& path)
{
    boost::property_tree::ptree pt;
    boost::property_tree::ini_parser::read_ini("config.ini", pt);
    ctrl_port=pt.get<int>("APP_CFG.ctrl_port");
    data_port=pt.get<int>("APP_CFG.data_port");
    basePath=pt.get<string>("APP_CFG.basePath");
    syncdir=pt.get<string>("APP_CFG.syncdir");
    db_addr=pt.get<string>("APP_CFG.db_addr");
    db_username=pt.get<string>("APP_CFG.db_username");
    db_pwd=pt.get<string>("APP_CFG.db_pwd");
}

int config::getCtrlPort() const {
    return ctrl_port;
}

void config::setCtrlPort(int ctrlPort) {
    ctrl_port = ctrlPort;
}

int config::getDataPort() const {
    return data_port;
}

void config::setDataPort(int dataPort) {
    data_port = dataPort;
}

const string &config::getBasePath() const {
    return basePath;
}

void config::setBasePath(const string &basePath) {
    config::basePath = basePath;
}

const string &config::getSyncdir() const {
    return syncdir;
}

void config::setSyncdir(const string &syncdir) {
    config::syncdir = syncdir;
}

const string &config::getDbAddr() const {
    return db_addr;
}

void config::setDbAddr(const string &dbAddr) {
    db_addr = dbAddr;
}

const string &config::getDbUsername() const {
    return db_username;
}

void config::setDbUsername(const string &dbUsername) {
    db_username = dbUsername;
}

const string &config::getDbPwd() const {
    return db_pwd;
}

void config::setDbPwd(const string &dbPwd) {
    db_pwd = dbPwd;
}
