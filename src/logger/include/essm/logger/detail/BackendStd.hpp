#pragma once

#include <format>
#include <iostream>

#include <essm/logger/detail/Filename.hpp>
#define __essm_logger_command(app, level, ...)                                                                         \
    ::std::cout << ::std::format("{}/{} [{}:{}] {}\n",                                                                 \
                                 #level,                                                                               \
                                 app,                                                                                  \
                                 __essm_logger_filename,                                                               \
                                 __LINE__,                                                                             \
                                 ::std::format(__VA_ARGS__))

#define __essm_logger_debug(app, ...) __essm_logger_command(app, DBG, __VA_ARGS__)
#define __essm_logger_info(app, ...) __essm_logger_command(app, INF, __VA_ARGS__)
#define __essm_logger_warn(app, ...) __essm_logger_command(app, WRN, __VA_ARGS__)
#define __essm_logger_error(app, ...) __essm_logger_command(app, ERR, __VA_ARGS__)
