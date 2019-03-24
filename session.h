//
// Created by jiang on 19-3-24.
//

#ifndef FILESERVER_SESSION_H
#define FILESERVER_SESSION_H

#include <memory>
#include <boost/asio.hpp>
using boost::asio::ip::tcp;
class session:public std::enable_shared_from_this<session>{
private:
    tcp::socket socket_;
    enum {max_length=1024};
    char data_[max_length];
    void do_read();
    void do_write(std::size_t length);
public:
    session(tcp::socket socket):socket_(std::move(socket)){}
    session()= delete;
    void start(){do_read();};
};


#endif //FILESERVER_SESSION_H
