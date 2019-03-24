//
// Created by jiang on 19-3-24.
//

#include "fileSerevr.h"

void fileSerevr::do_accept() {
    m_acceptor.async_accept(
            [this](boost::system::error_code ec,tcp::socket socket)
            {
                if (!ec)
                {
                    std::make_shared<session>(std::move(socket))->start();
                }
                do_accept();
            }
            );
}
