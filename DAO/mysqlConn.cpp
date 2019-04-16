//
// Created by jiang on 19-4-3.
//

#include "mysqlConn.h"

void mysqlConn::connect() {
    driver=sql::mysql::get_driver_instance();
    conn=driver->connect("tcp://localhost:3306/filesync","jiang","123456");
    stat=conn->createStatement();
    stat->execute("set names 'gbk'");
}

void mysqlConn::execute(string s)
{
    stat->execute(s);
}

void mysqlConn::disconnect() {
    if(conn!= nullptr)
        delete conn;
}
