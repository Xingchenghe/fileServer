#include "common/util.h"
#include <boost/asio.hpp>
#include "fileSerevr.h"
#include "common/Log.h"
#include "common/config.h"
#include <iostream>
#include "Service/TreeService.h"
using namespace std;
using namespace boost::asio;
using transfer_mgr_ptr=std::shared_ptr<fileTransferMgr>;

int main()
{
//    string s=TreeService::dirJson("/home/jiang/workspace/filebackup/user2");
//    cout<<s<<endl;
//    cout<<s.length()<<endl;
//    cin.get();
    try
    {
        extern config cfg;
        extern bool g_nInitLog;
        InitLog();
        io_context ioContext;
        fileTransferMgr transferMgr(ioContext,cfg.getDataPort());
        fileSerevr fSerevr(ioContext,cfg.getCtrlPort());
        ioContext.run();
    }
    catch (std::exception& e)
    {
        std::cerr<<"Exception:"<<e.what()<<std::endl;
    }
}