//
// Created by jiang on 19-3-31.
//

#ifndef FILESERVER_FILESENDER_H
#define FILESERVER_FILESENDER_H

void sendfile(boost::asio::io_service& io, const char* ip_address, unsigned port, const char* filename);
#endif //FILESERVER_FILESENDER_H
