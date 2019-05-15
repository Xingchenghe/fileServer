//
// Created by jiang on 19-3-25.
//

#ifndef FILESERVER_FILESENDER_H
#define FILESERVER_FILESENDER_H
#include <glob.h>
#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>
#include <queue>
#include <iostream>
#include "fileSender.h"

struct File_info
{
    typedef unsigned long long Size_type;
    Size_type filesize;
    size_t filename_size;
    File_info() : filesize(0), filename_size(0) {}
};

void sendfile(boost::asio::io_service& io, const char* ip_address, unsigned port, const char* filename)
{
    typedef boost::asio::ip::tcp TCP;

    FILE *fp = fopen(filename, "rb");
    if (fp == nullptr)
    {
        std::cerr << "cannot open file\n";
        return;
    }

    boost::shared_ptr<FILE> file_ptr(fp, fclose);

    clock_t cost_time = clock();

    const size_t k_buffer_size = 32 * 1024;
    char buffer[k_buffer_size];
    File_info file_info;

    int filename_size  = strlen(filename) + 1;
    size_t file_info_size = sizeof(file_info);
    size_t total_size = file_info_size + filename_size;
    if (total_size > k_buffer_size)
    {
        std::cerr << "File name is too long";
        return;
    }
    file_info.filename_size = filename_size;

    fseek(fp, 0, SEEK_END);
    file_info.filesize = ftell(fp);
    rewind(fp);

    memcpy(buffer, &file_info, file_info_size);
    memcpy(buffer + file_info_size, filename, filename_size);

    TCP::socket socket(io);
    socket.connect(TCP::endpoint(boost::asio::ip::address_v4::from_string(ip_address), port));

    std::cout << "Sending file : " << filename << "\n";
    size_t len = total_size;
    unsigned long long total_bytes_read = 0;
    while (true) {
        socket.send(boost::asio::buffer(buffer, len), 0);
        if (feof(fp)) break;
        len = fread(buffer, 1, k_buffer_size, fp);
        total_bytes_read += len;
    }

    cost_time = clock() - cost_time;
    if (cost_time == 0) cost_time = 1;
    double speed = total_bytes_read * (CLOCKS_PER_SEC / 1024.0 / 1024.0) / cost_time;
    std::cout << "cost time: " << cost_time / (double) CLOCKS_PER_SEC  << " s "
              << "  transferred_bytes: " << total_bytes_read << " bytes\n"
              << "speed: " <<  speed << " MB/s\n\n";
}
#endif //FILESERVER_FILESENDER_H


