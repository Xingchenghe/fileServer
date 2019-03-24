cmake_minimum_required(VERSION 3.13)
project(fileServer)

set(CMAKE_CXX_STANDARD 14)
set(INC_DIR /home/jiang/boost_1_69_0)
set(LINK_DIR /home/jiang/boost_1_69_0/stage/lib)

include_directories(${INC_DIR})
link_directories(${LINK_DIR})
add_executable(fileServer main.cpp file.h file.cpp md5.h md5.cpp util.h util.cpp fileSerevr.cpp fileSerevr.h session.cpp session.h)
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)
target_link_libraries(fileServer -lpthread -lboost_system -lboost_filesystem -lboost_log -lboost_log_setup -lboost_thread -lboost_regex)