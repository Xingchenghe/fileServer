//
// Created by jiang on 19-4-1.
//

#ifndef FILESERVER_FILETRANSFERMGR_H
#define FILESERVER_FILETRANSFERMGR_H

#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include "fileRsver.h"
using boost::system::error_code;
class fileTransferMgr
{
public:
    typedef boost::asio::ip::tcp TCP;
    typedef error_code Error;

    fileTransferMgr(boost::asio::io_context& io, unsigned port) :acceptor_(io, TCP::endpoint(TCP::v4(), port))
    {
        start_accept();
    }

    static void print_asio_error(const Error& error) { std::cerr << error.message() << "\n";}

private:
    void start_accept();

    void handle_accept(fileRsver::Pointer rsver, const Error& error);

    TCP::acceptor acceptor_;
};


#endif //FILESERVER_FILETRANSFERMGR_H
