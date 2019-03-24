#include "util.h"
#include <boost/asio.hpp>
#include "fileSerevr.h"
using namespace boost::asio;

int main()
{
    //std::cout << Get_File_Md5("/media/jiang/新加卷/data/qq_msg_his.bak")  << std::endl;
    try {
        io_context ioContext;
        fileSerevr fSerevr(ioContext,6688);
        ioContext.run();
    }
    catch (std::exception e)
    {
        std::cerr<<"Exception:"<<e.what()<<std::endl;
    }
}