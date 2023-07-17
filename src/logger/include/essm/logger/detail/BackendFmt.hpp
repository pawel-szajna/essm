#pragma once

#include <fmt/color.h>

#include <essm/helpers/Hash.hpp>
#include <essm/logger/detail/Filename.hpp>

#define __essm_logger_command(app, level, fheader, ...)                                                                \
    (::fmt::print(fheader, "{}", #level),                                                                              \
     ::fmt::print("/"),                                                                                                \
     ::fmt::print(fmt::fg(::fmt::rgb(::essm::helpers::hash(#app) | 0x88'88'88)), app),                                 \
     ::fmt::print(fmt::emphasis::bold, " [{}:{}] ", __essm_logger_filename, __LINE__),                                 \
     ::fmt::print(__VA_ARGS__),                                                                                        \
     ::fmt::print("\n"))

#define __essm_logger_debug(app, ...) __essm_logger_command(app, DBG, fmt::fg(fmt::color::sea_green), __VA_ARGS__)
#define __essm_logger_info(app, ...) __essm_logger_command(app, INF, fmt::fg(fmt::color::lime_green), __VA_ARGS__)
#define __essm_logger_warn(app, ...) __essm_logger_command(app, WRN, fmt::fg(fmt::color::red), __VA_ARGS__)
#define __essm_logger_error(app, ...) __essm_logger_command(app, ERR, fmt::bg(fmt::color::red), __VA_ARGS__)
