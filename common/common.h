//
// Created by jiang on 19-3-25.
//

#ifndef FILESERVER_COMMON_H
#define FILESERVER_COMMON_H

#include <string>
#include "../sessionMgr.h"
using std::string;

const string basePath="/home/jiang/workspace/filebackup/";

const string syncdir="syncdir";

const int max_connection=30;

enum actType{LOGIN=1,LOGINSUCCESS,LOGINFAIL,REGISTER,REGISTERSUCCESS,REGISTERFAIL,REQSERVFILES,DELFILE,DELSUCCESS,DELFAIL,SERVERFILES,SNDFILE,SNDFILEFAIL,
        SNDFILEREADY,REQFILE,DEVICEFILEINFO,WRONGJSONFORMAT,TOOMUCHSESSION,EXIT};

enum fileStatus{NORMAL,DELETE,MODIFIED,REPLACED};

class errJson
{
private:
    actType act;
    std::string errinfo;
public:
    std::string toJson();
    errJson(actType act,std::string what);
};


#endif //FILESERVER_COMMON_H
