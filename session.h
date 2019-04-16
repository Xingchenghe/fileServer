//
// Created by jiang on 19-3-24.
//
#pragma once
#ifndef FILESERVER_SESSION_H
#define FILESERVER_SESSION_H

#include <memory>
#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/noncopyable.hpp>
#include "fileSender.h"
#include <string>
using std::string;
using boost::asio::ip::tcp;
class session:
        public std::enable_shared_from_this<session>,
        private boost::noncopyable
{
private:
    static unsigned int session_id;
    int s_id;
    tcp::socket socket_;
    enum {max_length=10240};
    char data_[max_length];
    string username;
    string dev_mac;
    bool transFin;
public:
    static unsigned int getSessionId();
    const tcp::socket &getSocket() const;
    tcp::socket &getSocket() ;
    const string &getUsername() const;
    const string &getDevMac() const;
private:
    bool isLogin;
    boost::property_tree::ptree cmdPt;
private:
    void do_read_ctrl();
    void do_write_ctrl(std::size_t length);
    void do_write_ctrl_norecur(std::size_t length);
    void parseCmdJson();
public:
    session(tcp::socket socket):socket_(std::move(socket)),isLogin(false),transFin(false){s_id=++session_id;memset(data_,0, sizeof(data_));}
    session()= delete;
    ~session();
    void start(){do_read_ctrl();};
};

using sess_ptr=std::shared_ptr<session>;
#endif //FILESERVER_SESSION_H
