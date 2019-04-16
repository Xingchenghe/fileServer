//
// Created by jiang on 19-4-3.
//

#ifndef FILESERVER_USERDAO_H
#define FILESERVER_USERDAO_H

#include "mysqlConn.h"
#include "../model/User.h"

class userDAO: public mysqlConn
{
private:
    const string TABLE_NAME=" user ";
    const string TABLE_FIELDS = " name, password, salt ";
    const string SELECT_FIELDS = " id, " + TABLE_FIELDS;
public:
    void addUser(User user);
    string getSaltByUsername(const string &username);
    User selectById(int id);
    user_ptr selectByName(string name);
    void updataPassword(User user);
    void deleteUserById(int id);
};


#endif //FILESERVER_USERDAO_H
