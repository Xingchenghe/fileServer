//
// Created by jiang on 19-3-24.
//

#include "session.h"
#include <boost/property_tree/json_parser.hpp>
#include <iostream>
#include "common.h"
using namespace std;

unsigned int session::session_id=0;

void session::do_read_ctrl()
{
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_,max_length),
            [this,self](boost::system::error_code ec,std::size_t length)
            {
                if(!ec)
                {
                    cout<<s_id<<endl;
                    if(length==0)
                        return;
                    try
                    {
                        parseCmdJson();
                    }
                    catch (exception e)
                    {
                        errJson ej(WRONGJSONFORMAT,"wrong json format");
                        strcpy(data_,ej.toJson().c_str());
                        do_write_ctrl(strlen(data_));
                    }

                    if(s_id>max_connection)
                    {
                        errJson ej(TOOMUCHSESSION,"too much connection, please wait...");
                    }
                    else
                    {
                        auto act= static_cast<actType>(cmdPt.get<int>("action"));
                    }
                    do_read_ctrl();
                }
            }
            );
}

//void session::do_write_data(std::size_t length)
//{
//    auto self(shared_from_this());
//    boost::asio::async_write(socket_,boost::asio::buffer(data_,length),
//    [this,self](boost::system::error_code ec,std::size_t)
//    {
//        if(!ec)
//        {
//            do_read();
//        }
//    }
//    );
//}
//
//void session::do_read_data()
//{
//    auto self(shared_from_this());
//    socket_.async_read_some(boost::asio::buffer(cmdJson,max_length),
//                            [this,self](boost::system::error_code ec,std::size_t length)
//                            {
//                                if(!ec)
//                                {
//                                    do_write(length);
//                                }
//                            }
//    );
//}
//
void session::do_write_ctrl(std::size_t length)
{
    auto self(shared_from_this());
    boost::asio::async_write(socket_,boost::asio::buffer(data_,length),
                             [this,self](boost::system::error_code ec,std::size_t)
                             {
                                 if(!ec)
                                 {
                                     do_read_ctrl();
                                 }
                             }
    );
}

void session::parseCmdJson()
{
    std::stringstream ss(data_);
    boost::property_tree::json_parser::read_json(ss,cmdPt);
}

