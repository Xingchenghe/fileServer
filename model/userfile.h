//
// Created by jiang on 19-4-12.
//

#ifndef FILESERVER_USERFILE_H
#define FILESERVER_USERFILE_H

#include "file.h"
class userfile:public file
{
private:
    string owner;
    int type;
public:
    userfile()= default;

    const string &getOwner() const;

    void setOwner(const string &owner);

    int getType() const;

    void setType(int type);

};

using usr_file_ptr=std::shared_ptr<userfile>;
#endif //FILESERVER_USERFILE_H
