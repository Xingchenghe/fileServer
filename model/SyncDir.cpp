//
// Created by jiang on 19-4-6.
//

#include "SyncDir.h"

const string &SyncDir::getUsername() const {
    return username;
}

void SyncDir::setUsername(const string &username) {
    SyncDir::username = username;
}

const string &SyncDir::getDeviceMac() const {
    return device_mac;
}

void SyncDir::setDeviceMac(const string &deviceMac) {
    device_mac = deviceMac;
}

const string &SyncDir::getClientPath() const {
    return client_path;
}

void SyncDir::setClientPath(const string &clientPath) {
    client_path = clientPath;
}
