//
// Created by jiang on 19-3-25.
//

#ifndef FILESERVER_COMMON_H
#define FILESERVER_COMMON_H

#include <string>

const int max_connection=3;

enum actType{SNDFILE=1,REQFILE,WRONGJSONFORMAT,TOOMUCHSESSION};

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
