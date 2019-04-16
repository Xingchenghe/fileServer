//
// Created by jiang on 19-4-7.
//

#include "device.h"

const string &device::getUsername() const {
    return username;
}

void device::setUsername(const string &username) {
    device::username = username;
}

const string &device::getDevMac() const {
    return dev_mac;
}

void device::setDevMac(const string &devMac) {
    dev_mac = devMac;
}

int device::getDevId() const {
    return dev_id;
}

void device::setDevId(int devId) {
    dev_id = devId;
}
