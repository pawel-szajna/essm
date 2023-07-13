#pragma once

#if defined(ESSM_LOGGER_BACKEND_STD)
#    include <essm/logger/detail/BackendStd.hpp>
#elif defined(ESSM_LOGGER_BACKEND_FMT)
#    include <essm/logger/detail/BackendFmt.hpp>
#elif defined(ESSM_LOGGER_BACKEND_SPDLOG)
#    include <essm/logger/detail/BackendSpdlog.hpp>
#else
#    define essm_logger_debug(app, ...) (void)0
#    define essm_logger_info(app, ...) (void)0
#    define essm_logger_warn(app, ...) (void)0
#    define essm_logger_error(app, ...) (void)0
#endif

#if not defined(essm_app_client)
#    define essm_app_client "Application"
#endif

#define essm_debug(...) essm_logger_debug(essm_app_client, __VA_ARGS__)
#define essm_info(...) essm_logger_info(essm_app_client, __VA_ARGS__)
#define essm_warn(...) essm_logger_warn(essm_app_client, __VA_ARGS__)
#define essm_error(...) essm_logger_error(essm_app_client, __VA_ARGS__)
