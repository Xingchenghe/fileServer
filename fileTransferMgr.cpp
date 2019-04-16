//
// Created by jiang on 19-4-1.
//

#include "fileTransferMgr.h"
#include "sessionMgr.h"

extern sessionMgr sessionmgr;

void fileTransferMgr::start_accept()
{
    cout<<"start_accept"<<endl;
    fileRsver::Pointer rsver = fileRsver::create(acceptor_.get_io_service());
    acceptor_.async_accept(rsver->socket(),
                           boost::bind(&fileTransferMgr::handle_accept, this, rsver, boost::asio::placeholders::error));
}

void fileTransferMgr::handle_accept(fileRsver::Pointer rsver, const fileTransferMgr::Error &error)
{
    cout<<"handle_accept"<<endl;
    cout<<rsver->socket().remote_endpoint().address()<<endl;
    if (error) return print_asio_error(error);
    if(sessionmgr.isInConnectedEndpoint(rsver->socket().remote_endpoint().address().to_string()))
    {
        cout<<"handle_if"<<endl;
        string username=sessionmgr.getUsernameByAddress(rsver->socket().remote_endpoint().address().to_string());
        rsver->setUsername(username);
        rsver->start();
    }
    start_accept();
}
