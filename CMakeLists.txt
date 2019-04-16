cmake_minimum_required(VERSION 3.13)
project(fileServer)

set(CMAKE_CXX_STANDARD 14)
set(INC_DIR /home/jiang/boost_1_69_0)
set(DB_INC /home/jiang/mysql-connector-c++-8.0.15-linux-ubuntu18.04-x86-64bit/include)
set(LINK_DIR /home/jiang/boost_1_69_0/stage/lib)
set(DB_LINK /home/jiang/mysql-connector-c++-8.0.15-linux-ubuntu18.04-x86-64bit/lib64)


include_directories(${INC_DIR} ${DB_INC})
link_directories(${LINK_DIR} ${DB_LINK})
add_executable(fileServer main.cpp model/file.h model/file.cpp common/md5.h common/md5.cpp common/util.h common/util.cpp fileSerevr.cpp fileSerevr.h session.cpp session.h common/common.h
        common/common.cpp fileSender.cpp fileRsver.cpp fileRsver.h fileSender.h fileTransferMgr.cpp fileTransferMgr.h model/User.cpp model/User.h DAO/mysqlConn.h
        DAO/userDAO.h DAO/userDAO.cpp DAO/mysqlConn.cpp Service/LoginService.cpp Service/LoginService.h Service/RegisterService.cpp Service/RegisterService.h DAO/syncdirDAO.cpp
        DAO/syncdirDAO.h model/SyncDir.cpp model/SyncDir.h model/device.cpp model/device.h sessionMgr.cpp sessionMgr.h DAO/deviceDAO.cpp DAO/deviceDAO.h Service/DeviceService.cpp
        Service/DeviceService.h Service/SendService.cpp Service/SendService.h DAO/deviceFileDAO.cpp DAO/deviceFileDAO.h Service/DeviceFileService.cpp Service/DeviceFileService.h model/userfile.cpp model/userfile.h DAO/userFileDAO.cpp DAO/userFileDAO.h Service/DeleteService.cpp Service/DeleteService.h common/Log.h common/Log.cpp)
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)
target_link_libraries(fileServer -lpthread -lboost_system -lboost_filesystem -lboost_log -lboost_log_setup -lboost_thread -lboost_regex -lmysqlcppconn)