#pragma once

#define essm_logger_debug(app, ...) essm_logger_command(app, DBG, __VA_ARGS__)
#define essm_logger_info(app, ...) essm_logger_command(app, INF, __VA_ARGS__)
#define essm_logger_warn(app, ...) essm_logger_command(app, WRN, __VA_ARGS__)
#define essm_logger_error(app, ...) essm_logger_command(app, ERR, __VA_ARGS__)
