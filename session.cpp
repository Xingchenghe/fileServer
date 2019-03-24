//
// Created by jiang on 19-3-24.
//

#include "session.h"
#include <iostream>
void session::do_read()
{
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_,max_length),
            [this,self](boost::system::error_code ec,std::size_t length)
            {
                if(!ec)
                {
                    do_write(length);
                }
            }
            );
}

void session::do_write(std::size_t length)
{
    auto self(shared_from_this());
    boost::asio::async_write(socket_,boost::asio::buffer(data_,length),
    [this,self](boost::system::error_code ec,std::size_t)
    {
        if(!ec)
        {
            do_read();
        }
    }
    );
}
