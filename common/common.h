//
// Created by jiang on 19-3-25.
//

#ifndef FILESERVER_COMMON_H
#define FILESERVER_COMMON_H

#include <string>
#include "../sessionMgr.h"
#include "config.h"
using std::string;
extern config cfg;
//const string basePath="/home/jiang/workspace/filebackup/";

//const string syncdir=cfg.getSyncdir();
//const string syncdir="syncdir";

const int max_connection=30;

enum actType{LOGIN=1,LOGINSUCCESS,LOGINFAIL,REGISTER,REGISTERSUCCESS,REGISTERFAIL,REQSERVFILES,DELFILE,DELSUCCESS,DELFAIL,SERVERFILES,SNDFILE,SNDFILEFAIL,
        SNDFILEREADY,REQFILE,REQFILEREADY,REQFILEFAIL,DEVICEFILEINFO,WRONGJSONFORMAT,TOOMUCHSESSION,EXIT,ISCHANGE,CHANGED,NOTCHANGED};

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
