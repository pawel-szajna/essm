#pragma once

#if defined(ESSM_LOGGER_BACKEND_STD)
    #include <essm/logger/detail/BackendStd.hpp>
#elif defined(ESSM_LOGGER_BACKEND_FMT)
    #include <essm/logger/detail/BackendFmt.hpp>
#elif defined(ESSM_LOGGER_BACKEND_SPDLOG)
    #include <essm/logger/detail/BackendSpdlog.hpp>
#else
    #define __essm_logger_debug(app, ...) (void)0
    #define __essm_logger_info(app, ...) (void)0
    #define __essm_logger_warn(app, ...) (void)0
    #define __essm_logger_error(app, ...) (void)0
#endif

#if not defined(essm_app_client)
    #define essm_app_client "Application"
#endif

/// @brief Write a debug log using the default logger
#if defined(ESSM_LOGGER_ENABLE_DEBUG)
    #define essm_debug(...) __essm_logger_debug(essm_app_client, __VA_ARGS__)
#else
    #define essm_debug(...) (void)0
#endif

/// @brief Write an info log using the default logger
#define essm_info(...) __essm_logger_info(essm_app_client, __VA_ARGS__)

/// @brief Write a warning log using the default logger
#define essm_warn(...) __essm_logger_warn(essm_app_client, __VA_ARGS__)

/// @brief Write an error log using the default logger
#define essm_error(...) __essm_logger_error(essm_app_client, __VA_ARGS__)
