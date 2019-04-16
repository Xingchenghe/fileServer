//
// Created by jiang on 19-3-24.
//

#include "fileSerevr.h"
#include "common/Log.h"

void fileSerevr::do_accept()
{
    m_acceptor.async_accept(
            [this](boost::system::error_code ec,tcp::socket socket)
            {
                if (!ec)
                {
                    BOOST_LOG_TRIVIAL(info)<<"fileserver accept a endpoint:"<<socket.remote_endpoint().address();
                    std::make_shared<session>(std::move(socket))->start();
                }
                do_accept();
            }
            );
}

fileSerevr::fileSerevr(io_context &ioContext, unsigned short port) :m_acceptor(ioContext,TcpEndpoint(ip::tcp::v4(),port))
{
    BOOST_LOG_TRIVIAL(info)<<"fileserver start accept";
    do_accept();
}
