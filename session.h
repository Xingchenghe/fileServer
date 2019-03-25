//
// Created by jiang on 19-3-24.
//

#ifndef FILESERVER_SESSION_H
#define FILESERVER_SESSION_H

#include <memory>
#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>

using boost::asio::ip::tcp;

class session:public std::enable_shared_from_this<session>
{
private:
    static unsigned int session_id;
    int s_id;
    tcp::socket socket_;
    enum {max_length=1024};
    char data_[max_length];
    boost::property_tree::ptree cmdPt;
private:
    void do_read_ctrl();  //TODO
    //void do_read_data(); //TODO
    void do_write_ctrl(std::size_t length);//TODO
    //void do_write_data(std::size_t length);//TODO
    void parseCmdJson();
public:
    session(tcp::socket socket):socket_(std::move(socket)){s_id=++session_id;}
    session()= delete;
    ~session(){--session_id;}
    void start(){do_read_ctrl();};
};


#endif //FILESERVER_SESSION_H
