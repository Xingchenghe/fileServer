//
// Created by jiang on 19-4-3.
//

#ifndef FILESERVER_USER_H
#define FILESERVER_USER_H

#include <memory>
#include <string>
using std::string;

class User
{
private:
    int id;
    string username;
    string password;
    string salt;
public:
    User():id(-1),username(""),password(""),salt(""){}

    const string &getUsername() const;

    void setUsername(const string &username);

    const string &getPassword() const;

    void setPassword(const string &password);

    const string &getSalt() const;

    void setSalt(const string &salt);

    int getId() const;

    void setId(int id);
};

using user_ptr=std::shared_ptr<User>;
#endif //FILESERVER_USER_H
