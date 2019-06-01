//
// Created by jiang on 19-4-12.
//

#include "userfile.h"

const string &userfile::getOwner() const
{
    return owner;
}

void userfile::setOwner(const string &owner)
{
    userfile::owner = owner;
}

int userfile::getType() const {
    return type;
}

void userfile::setType(int type) {
    userfile::type = type;
}