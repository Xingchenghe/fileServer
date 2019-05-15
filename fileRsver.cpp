//
// Created by jiang on 19-3-31.
//

#include "fileRsver.h"
#include "common/common.h"
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <vector>
#include "DAO/userFileDAO.h"
#include "common/Log.h"
#include "common/util.h"
using std::vector;
using namespace boost;
fileRsver::~fileRsver()
{
    if (fp_) fclose(fp_);
    clock_ = clock() - clock_;
    Size_type bytes_writen = total_bytes_writen_;
    if (clock_ == 0) clock_ = 1;
    double speed = bytes_writen * (CLOCKS_PER_SEC / 1024.0 / 1024.0) / clock_ ;
    BOOST_LOG_TRIVIAL(trace)<<"receive user:"<<username<<",file:"<<filepath << " finished,cost time: " << clock_ / (double) CLOCKS_PER_SEC << " s  "
    << "bytes_writen: " << bytes_writen << " bytes,"
    << "speed: " <<  speed << " MB/s\n\n";
}

void fileRsver::start()
{
    clock_ = clock();
    BOOST_LOG_TRIVIAL(trace)<<"start receive file, user:"<<username<< ",client: " << socket_.remote_endpoint().address() <<endl;
    socket_.async_receive(
            boost::asio::buffer(reinterpret_cast<char*>(&file_info_), sizeof(file_info_)),
            boost::bind(&fileRsver::handle_header, shared_from_this(), boost::asio::placeholders::error));
}

void fileRsver::handle_header(const fileRsver::Error &error)
{
    if (error) return print_asio_error(error);
    size_t filename_size = file_info_.filename_size;
    if (filename_size > k_buffer_size)
    {
        BOOST_LOG_TRIVIAL(error) << "Path name is too long!\n";
        return;
    }
    //得用async_read,不能用async_read_some，防止路径名超长时，一次接收不完
    boost::asio::async_read(socket_, boost::asio::buffer(buffer_, file_info_.filename_size),
                            boost::bind(&fileRsver::handle_file, shared_from_this(), boost::asio::placeholders::error));
}

void fileRsver::handle_file(const fileRsver::Error &error)
{
    if (error) return print_asio_error(error);
    string clientPath=buffer_;
    replace_all(clientPath,"\\","/");
    vector<string> result;
    string serverPath=basePath+username;
    split(result,clientPath,is_any_of("/"));
    filename=result[result.size()-1];
    bool find=false;
    for(int i=0;i<result.size()-1;i++)
    {
        if(result[i]==syncdir)
        {
            find=true;
            continue;
        }
        if(find)
        {
            serverPath+='/'+result[i];
            filepath+='/'+result[i];
        }
    }
    if(!boost::filesystem::exists(serverPath))
        boost::filesystem::create_directories(serverPath);
    BOOST_LOG_TRIVIAL(trace) << "Open file: " << filename << " (" << buffer_ << ")\n";
    string filedir=serverPath+'/'+filename;
    filepath+='/'+filename;
    fp_ = fopen(filedir.c_str(), "wb");
    if (fp_ == nullptr)
    {
        BOOST_LOG_TRIVIAL(error) << "Failed to open file to write\n";
        return;
    }
    receive_file_content();
}

void fileRsver::receive_file_content()
{
    socket_.async_receive(boost::asio::buffer(buffer_, k_buffer_size),
                          boost::bind(&fileRsver::handle_write, shared_from_this(), boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred));
}

void fileRsver::handle_write(const fileRsver::Error &error, size_t bytes_transferred)
{
    if (error)
    {
        if (error != boost::asio::error::eof) return print_asio_error(error);
        Size_type filesize = file_info_.filesize;
        if (total_bytes_writen_ != filesize)
            BOOST_LOG_TRIVIAL(error) <<  "Filesize not matched! " << total_bytes_writen_<< "/" << filesize <<endl;
        return;
    }
    total_bytes_writen_ += fwrite(buffer_, 1, bytes_transferred, fp_);
    if(total_bytes_writen_==file_info_.filesize)
    {
        userFileDAO userFileDao;
        usr_file_ptr usrFilePtr=userFileDao.selectTransFileByUsernameAndPath(username,filepath);
        userFileDao.removeTransFileByUsernameAndPath(username,filepath);
        userFileDao.insertfile(*usrFilePtr);
    }
    receive_file_content();
}

void fileRsver::setUsername(const string &username)
{
    fileRsver::username = username;
}
