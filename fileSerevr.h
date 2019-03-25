//
// Created by jiang on 19-3-24.
//

#ifndef FILESERVER_FILESEREVR_H
#define FILESERVER_FILESEREVR_H

#include "session.h"
#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include <memory>
#include <unordered_set>
using namespace boost::asio;
class fileSerevr:private boost::noncopyable{
    using TcpAcceptor=boost::asio::ip::tcp::acceptor;
    using TcpEndpoint=boost::asio::ip::tcp::endpoint;
    using TcpSocket=boost::asio::ip::tcp::socket;
    using sock_ptr=std::shared_ptr<TcpSocket>;
private:
    TcpAcceptor  m_acceptor;
    void do_accept();
public:
    fileSerevr()= delete;
    fileSerevr(io_context& ioContext,unsigned short port):m_acceptor(ioContext,TcpEndpoint(ip::tcp::v4(),port)){do_accept();}
};


#endif //FILESERVER_FILESEREVR_H
