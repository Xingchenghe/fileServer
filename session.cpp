//
// Created by jiang on 19-3-24.
//

#include "session.h"
#include <boost/property_tree/json_parser.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <iostream>
#include <boost/filesystem.hpp>
#include <vector>
#include "common/common.h"
#include "common/util.h"
#include "common/Log.h"
#include "Service/LoginService.h"
#include "Service/RegisterService.h"
#include "Service/DeviceService.h"
#include "Service/SendService.h"
#include "Service/DeviceFileService.h"
#include "Service/DeleteService.h"
#include "DAO/userFileDAO.h"

using namespace std;
using namespace boost::filesystem;
unsigned int session::session_id=0;
extern sessionMgr sessionmgr;
void session::do_read_ctrl()
{
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_,max_length),
            [this,self](boost::system::error_code ec,std::size_t length)
            {
                BOOST_LOG_TRIVIAL(trace)<<"read sth,length="<<length<<",data:"<<data_;
                if(!ec)
                {
                    try
                    {
                        parseCmdJson();
                    }
                    catch (exception& e)
                    {
                        BOOST_LOG_TRIVIAL(error)<<"receive wrong json format,json:"<<data_;
                        errJson ej(WRONGJSONFORMAT,"wrong json format");
                        strcpy(data_,ej.toJson().c_str());
                        do_write_ctrl(strlen(data_));
                    }

                    if(s_id>max_connection)
                    {
                        BOOST_LOG_TRIVIAL(error)<<"Too much connection,connection count:"<<s_id;
                        errJson ej(TOOMUCHSESSION,"too much connection, please wait...");
                        return;
                    }
                    else
                    {
                        auto act= static_cast<actType>(cmdPt.get<int>("action"));
                        if(act==LOGIN)
                        {
                            username=cmdPt.get<string>("username");
                            string password=cmdPt.get<string>("password");
                            dev_mac=cmdPt.get<string>("dev_mac");
                            BOOST_LOG_TRIVIAL(trace)<<"user username:"<<username<<",dev_mac:"<<dev_mac<<" enter Login,session_id="<<s_id;
                            string reply;
                            LoginService loginService;
                            loginService.setUsername(username);
                            string salt=loginService.getSalt();
                            loginService.setPassword(md5(password+salt));
                            DeviceService deviceService(username,dev_mac);
                            if(loginService.login())
                            {
                                BOOST_LOG_TRIVIAL(info)<<"device username:"<<username<<",mac_addr:"<<dev_mac<<" logged in";
                                isLogin=true;
                                device dev(username,dev_mac);
                                if(!deviceService.isDeviceExist())
                                {
                                    deviceService.addDevice();
                                }
                                dev.setDevId(deviceService.getIdbyUsernameAndMac(username,dev_mac));
                                string addr=socket_.remote_endpoint().address().to_string();
                                reply=loginService.resultStr();
                                strcpy(data_,reply.c_str());
                                do_write_ctrl(reply.length());
                                memset(data_,0, sizeof(data_));
                                sessionmgr.addUser(username);
                                sessionmgr.insertDevice(username,dev_mac);
                                sessionmgr.insertIntoConnectedEndpoint(addr);
                                sessionmgr.insertIntoConnectedEndpointDevMap(addr,dev);
                            }
                            else
                            {
                                reply=loginService.resultStr();
                                BOOST_LOG_TRIVIAL(error)<<"device username:"<<username<<",mac_addr:"<<dev_mac<<" logg in fail,fail json:"<<reply;
                                strcpy(data_,reply.c_str());
                                do_write_ctrl(reply.length());
                                memset(data_,0, sizeof(data_));
                                return;
                            }
                        }
                        else if(act==REGISTER)
                        {
                            string username=cmdPt.get<string>("username");
                            string passwd=cmdPt.get<string>("password");
                            BOOST_LOG_TRIVIAL(info)<<"user use username:"<<username<<" registered";
                            boost::uuids::uuid a_uuid = boost::uuids::random_generator()();
                            string salt = boost::uuids::to_string(a_uuid).substr(0,5);
                            string passwd_md5=md5(passwd+salt);
                            cout<<passwd_md5<<endl;
                            string reply;
                            RegisterService registerService(username,passwd_md5,salt);
                            registerService.Register();
                            reply=registerService.resultStr();
                            BOOST_LOG_TRIVIAL(info)<<"user use username:"<<username<<" register result json:"<<reply;
                            strcpy(data_,reply.c_str());
                            do_write_ctrl(reply.length());
                            memset(data_,0, sizeof(data_));
                        }
                        else if(act==SNDFILE)
                        {
                            BOOST_LOG_TRIVIAL(trace)<<"device username:"<<username<<",mac_addr:"<<dev_mac<<" enter sndfile,json:"<<data_;
                            SendService sendService;
                            string reply;
                            if(!isLogin)
                            {
                                reply=sendService.sendFail();
                                strcpy(data_,reply.c_str());
                                do_write_ctrl(reply.length());
                                memset(data_,0, sizeof(data_));
                                return;
                            }
                            else
                            {
                                userfile ufile;
                                ufile.setOwner(cmdPt.get<string>("owner"));
                                ufile.setType(cmdPt.get<int>("type"));
                                ufile.setLastModifiedTime(cmdPt.get<int>("last_modified_time"));
                                ufile.setClientPath(cmdPt.get<string>("path"));
                                ufile.setMd5(cmdPt.get<string>("md5"));
                                BOOST_LOG_TRIVIAL(trace)<<"device username:"<<username<<",mac_addr:"<<dev_mac<<" require to send file to server,file json:"<<data_;
                                reply=sendService.sendReady();
                                userFileDAO userFileDao;
                                userFileDao.insertTransFile(ufile);
                                strcpy(data_,reply.c_str());
                                do_write_ctrl(reply.length());
                                memset(data_,0, sizeof(data_));
                                //TODO
                            }
                        }
                        else if(act==REQSERVFILES)
                        {
                            string reply;
                            if(!isLogin)
                            {
                                reply=LoginService::notLogin();
                                strcpy(data_,reply.c_str());
                                do_write_ctrl(reply.length());
                                memset(data_,0, sizeof(data_));
                                return;
                            }
                            else
                            {
                                BOOST_LOG_TRIVIAL(trace)<<"device username:"<<username<<",mac_addr:"<<dev_mac<<" require server file list";
                                userFileDAO userFileDao;
                                const int max_files=50;
                                auto files=userFileDao.getUserFilesByUserName(username);
                                boost::property_tree::ptree pt;
                                pt.put("action",SERVERFILES);
                                boost::property_tree::ptree serverfiles;
                                int i;
                                if(files.empty())
                                {
                                    pt.add_child("info",serverfiles);
                                    pt.put("has_more","no");
                                    std::stringstream ss;
                                    boost::property_tree::write_json(ss,pt);
                                    strcpy(data_,ss.str().c_str());
                                    do_write_ctrl(ss.str().length());
                                    memset(data_,0, sizeof(data_));
                                }
                                else
                                {
                                    for(i=0;i<files.size();i++)
                                    {
                                        boost::property_tree::ptree onefile;
                                        onefile.put("path",files[i].get_clientPath());
                                        onefile.put("type",files[i].getType());
                                        onefile.put("last_modified_time",files[i].get_lastModifiedTime());
                                        onefile.put("md5",files[i].get_md5());
                                        serverfiles.push_back(make_pair("",onefile));
                                        if((i>0)&&(i%max_files==0))
                                        {
                                            pt.add_child("info",serverfiles);
                                            if(i<files.size()-1)
                                            {
                                                pt.put("has_more","yes");
                                            }
                                            else if(i==files.size()-1)
                                            {
                                                pt.put("has_more","no");
                                            }
                                            std::stringstream ss;
                                            boost::property_tree::write_json(ss,pt);
                                            strcpy(data_,ss.str().c_str());
                                            do_write_ctrl_norecur(ss.str().length());
                                            memset(data_,0, sizeof(data_));
                                            serverfiles.clear();
                                            pt.clear();
                                        }
                                        else if(i==files.size()-1)
                                        {
                                            pt.put("has_more","no");
                                            pt.add_child("info",serverfiles);
                                            std::stringstream ss;
                                            boost::property_tree::write_json(ss,pt);
                                            strcpy(data_,ss.str().c_str());
                                            do_write_ctrl(ss.str().length());
                                            memset(data_,0, sizeof(data_));
                                        }
                                    }
                                }

                            }

                        }
                        else if(act==DELFILE)
                        {
                            string reply;
                            if(!isLogin)
                            {
                                reply=LoginService::notLogin();
                                strcpy(data_,reply.c_str());
                                do_write_ctrl(reply.length());
                                memset(data_,0, sizeof(data_));
                                return;
                            }
                            else
                            {
                                userFileDAO userFileDao;
                                DeleteService deleteService;
                                string delpath=cmdPt.get<string>("path");
                                BOOST_LOG_TRIVIAL(trace)<<"device username:"<<username<<",mac_addr:"<<dev_mac<<" require delete server file,filepath:"<<delpath;
                                usr_file_ptr usrFilePtr=userFileDao.selectByUsernameAndPath(username,delpath);
                                string localPath=basePath+'/'+username+delpath;
                                if(usrFilePtr== nullptr)
                                {
                                    BOOST_LOG_TRIVIAL(error)<<"device username:"<<username<<",mac_addr:"<<dev_mac<<" require delete server file failed,filepath:"<<delpath;
                                    reply=deleteService.DelFail(delpath);
                                }
                                else
                                {
                                    if(is_regular_file(localPath))
                                    {
                                        remove(localPath);
                                        userFileDao.removeByUsernameAndPath(username, delpath);
                                        reply=deleteService.DelSuccess(delpath);
                                        BOOST_LOG_TRIVIAL(trace)<<"device username:"<<username<<",mac_addr:"<<dev_mac<<" require delete server file success,filepath:"<<delpath;
                                    }
                                }
                                strcpy(data_,reply.c_str());
                                do_write_ctrl(reply.length());
                                memset(data_,0, sizeof(data_));
                            }
                        }
                        else if(act==DEVICEFILEINFO)
                        {
                            cout<<"dev info"<<endl;
                            string reply;
                            if(!isLogin)
                            {
                                reply=LoginService::notLogin();
                                strcpy(data_,reply.c_str());
                                do_write_ctrl(reply.length());
                                memset(data_,0, sizeof(data_));
                                return;
                            }
                            else
                            {
                                deviceDAO deviceDao;
                                int id=deviceDao.selectByNameAndMac(username,dev_mac)->getDevId();
                                boost::property_tree::ptree files=cmdPt.get_child("info");
                                vector<devicefile> devFiles;
                                auto it=files.begin();
                                while (it!=files.end())
                                {
                                    devicefile devfile;
                                    devfile.setDevId(id);
                                    devfile.setMd5(it->second.get<string>("md5"));
                                    devfile.setClientPath(it->second.get<string>("path"));
                                    devfile.setLastModifiedTime(it->second.get<int>("last_modified_time"));
                                    devfile.setType(it->second.get<int>("type"));
                                    devFiles.push_back(devfile);
                                    it++;
                                }
                                if(!devFiles.empty())
                                {
                                    DeviceFileService deviceFileService;
                                    deviceFileService.insertMulti(devFiles);
                                }
                                do_read_ctrl();
                                memset(data_,0, sizeof(data_));
                            }
                        }
                        else if(act==EXIT)
                        {
                            BOOST_LOG_TRIVIAL(trace)<<"device username:"<<username<<",mac_addr:"<<dev_mac<<" require EXIT";
                            memset(data_,0, sizeof(data_));
                            return;
                        }
                    }
                }
                else
                {
                    BOOST_LOG_TRIVIAL(error)<<"an error occured,username:"<<username<<",mac_addr:"<<dev_mac<<" session_id:"<<s_id<<" error message:"<<ec.message();
                }
            }
            );

}


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

void session::do_write_ctrl_norecur(std::size_t length)
{
    auto self(shared_from_this());
    boost::asio::async_write(socket_,boost::asio::buffer(data_,length),[this,self](boost::system::error_code ec,std::size_t){});
}

void session::parseCmdJson()
{
    std::stringstream ss(data_);
    boost::property_tree::json_parser::read_json(ss,cmdPt);
}

session::~session()
{
    BOOST_LOG_TRIVIAL(trace)<<"session:"<<s_id<<" destroyed";
    sessionmgr.count(username);
    sessionmgr.removeDevice(username,dev_mac);
    sessionmgr.removeFromConnectedEndpoint(socket_.remote_endpoint().address().to_string());
    sessionmgr.removeFromConnectedEndpointDevMap(socket_.remote_endpoint().address().to_string());
    if(sessionmgr.isUserDeviceEmpty(username))
    {
        sessionmgr.removeUser(username);
    }
    --session_id;
    std::cout<<"~session"<<endl;
    sessionmgr.count(username);
}

unsigned int session::getSessionId()
{
    return session_id;
}

const tcp::socket &session::getSocket() const
{
    return socket_;
}

const string &session::getUsername() const
{
    return username;
}

const string &session::getDevMac() const
{
    return dev_mac;
}

tcp::socket &session::getSocket() {
    return socket_;
}

