//
// Created by jiang on 19-4-6.
//

#ifndef FILESERVER_SYNCDIRDAO_H
#define FILESERVER_SYNCDIRDAO_H


#include "mysqlConn.h"
#include "../model/SyncDir.h"

class syncdirDAO: public mysqlConn
{
private:
    const string TABLE_NAME=" syncdir ";
    const string TABLE_FIELDS = " name, device_mac, client_path ";
    const string SELECT_FIELDS = TABLE_FIELDS;
public:
    bool addSyncDir(SyncDir syncDir);
    bool updateSyncDir(string username, string mac, string path);
    void removeSyncPath(SyncDir syncDir,string path);
    sync_dir_ptr selectByUsernameAndMac(string username,string mac);
};


#endif //FILESERVER_SYNCDIRDAO_H
