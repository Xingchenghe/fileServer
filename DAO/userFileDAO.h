//
// Created by jiang on 19-4-12.
//

#ifndef FILESERVER_USERFILEDAO_H
#define FILESERVER_USERFILEDAO_H

#include "../model/userfile.h"
#include "mysqlConn.h"
#include <vector>
using std::vector;

class userFileDAO:public mysqlConn
{
private:
    const string TABLE_NAME=" userfile ";
    const string TRANSFER_TABLE_NAME=" transferingFile ";
    const string TABLE_FIELDS = " owner, type, last_modified_time, path, md5 ";
    const string SELECT_FIELDS = TABLE_FIELDS;
public:
    bool insertfile(userfile ufile);
    usr_file_ptr selectByUsernameAndPath(const string& username,const string& path);
    usr_file_ptr selectTransFileByUsernameAndPath(const string& username,const string& path);
    bool insertTransFile(userfile ufile);
    bool removeTransFileByUsernameAndPath(const string& username,const string& path);
    bool removeByUsernameAndPath(const string& username,const string& path);
    vector<userfile> getUserFilesByUserName(const string& username);
};


#endif //FILESERVER_USERFILEDAO_H
