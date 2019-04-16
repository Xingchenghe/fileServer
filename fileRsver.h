//
// Created by jiang on 19-3-31.
//

#ifndef FILESERVER_FILERSVER_H
#define FILESERVER_FILERSVER_H
#include <iostream>
#include <cstdio>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <memory>
#include <string>
#include <boost/enable_shared_from_this.hpp>

using std::string;

using boost::system::error_code;
using std::string;
struct File_info {
    typedef unsigned long long Size_type;
    Size_type filesize;
    size_t filename_size;
    File_info() : filesize(0), filename_size(0) {}
};


class fileRsver : public boost::enable_shared_from_this<fileRsver> {
public:
    typedef boost::asio::ip::tcp TCP;
    typedef error_code Error;
    typedef boost::shared_ptr<fileRsver> Pointer;
    typedef File_info::Size_type Size_type;

    static void print_asio_error(const Error& error) { std::cerr << error.message() << "\n";}

    static Pointer create(boost::asio::io_context& io) { return Pointer(new fileRsver(io));}

    TCP::socket& socket() { return socket_; }

    ~fileRsver();

    void start();

private:
    fileRsver(boost::asio::io_context& io) : socket_(io), fp_(nullptr), total_bytes_writen_(0) { }

    void handle_header(const Error& error);

    void handle_file(const Error& error);

    void receive_file_content();

    void handle_write(const Error& error, size_t bytes_transferred);

    clock_t clock_;
    TCP::socket socket_;
    FILE *fp_;
    File_info file_info_;
    Size_type total_bytes_writen_;
    static const unsigned k_buffer_size = 1024 * 32;
    char buffer_[k_buffer_size];
    string username;
    string filename;
    string filepath;
public:
    void setUsername(const string &username);
};
#endif //FILESERVER_FILERSVER_H
