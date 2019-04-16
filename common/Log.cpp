//
// Created by jiang on 19-4-15.
//
#include "Log.h"

bool g_nInitLog = false;

void InitLog() {
    auto pSink=logging::add_file_log
            (
                    keywords::open_mode=std::ios::app,
                    keywords::file_name="log/filesync%N.log",
                    keywords::rotation_size=10*1024*1024,
                    keywords::format=
                            (
                                    expr::stream
                                            <<expr::format_date_time<boost::posix_time::ptime>("TimeStamp","%Y-%m-%d, %H:%M:%S.%f")
                                            << ": <" << logging::trivial::severity
                                            <<">"<<expr::smessage
                            )
            );
    pSink->locked_backend()->auto_flush(true);
    logging::add_console_log();
    logging::add_common_attributes();
//  logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::info);
}
