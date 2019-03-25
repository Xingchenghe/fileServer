//
// Created by jiang on 19-3-25.
//

#ifndef FILESERVER_FILESENDER_H
#define FILESERVER_FILESENDER_H

#include <glob.h>
#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>
#include "common.h"
using boost::asio::ip::tcp;
class fileSender:private boost::noncopyable
{
private:
    static const size_t max_length=1024;
    static const size_t threadNum=max_connection;
    char data_[threadNum][max_length];

};


#endif //FILESERVER_FILESENDER_H
