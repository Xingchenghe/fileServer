#include "common/util.h"
#include <boost/asio.hpp>
#include "fileSerevr.h"
#include "DAO/userDAO.h"
#include "common/Log.h"
#include <iostream>
using namespace std;
using namespace boost::asio;
using transfer_mgr_ptr=std::shared_ptr<fileTransferMgr>;


int main()
{
    try
    {
        extern bool g_nInitLog;
        InitLog();
        io_context ioContext;
        fileTransferMgr transferMgr(ioContext,6689);
        fileSerevr fSerevr(ioContext,6688);
        ioContext.run();
    }
    catch (std::exception& e)
    {
        std::cerr<<"Exception:"<<e.what()<<std::endl;
    }
}