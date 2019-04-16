//
// Created by jiang on 19-4-3.
//

#ifndef FILESERVER_MYSQLCONN_H
#define FILESERVER_MYSQLCONN_H

#include <jdbc/mysql_driver.h>
#include <jdbc/mysql_connection.h>
#include <jdbc/cppconn/driver.h>
#include <jdbc/cppconn/prepared_statement.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/metadata.h>
#include <jdbc/cppconn/exception.h>
#include <string>
using namespace sql;
using std::string;

class mysqlConn
{
private:
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *conn;
protected:
    sql::Statement* stat;
    ResultSet *res;
public:
    void connect();
    void execute(string s);
    void disconnect();
};


#endif //FILESERVER_MYSQLCONN_H
