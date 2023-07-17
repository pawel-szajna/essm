#pragma once

#include <spdlog/spdlog.h>

#if defined(ESSM_LOGGER_ENABLE_DEBUG)
    #define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG
#endif

#define __essm_logger_debug(app, ...) SPDLOG_DEBUG(__VA_ARGS__)
#define __essm_logger_info(app, ...) SPDLOG_INFO(__VA_ARGS__)
#define __essm_logger_warn(app, ...) SPDLOG_WARN(__VA_ARGS__)
#define __essm_logger_error(app, ...) SPDLOG_ERROR(__VA_ARGS__)
