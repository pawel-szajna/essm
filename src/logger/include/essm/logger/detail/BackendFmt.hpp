#pragma once

#include <fmt/core.h>

#include <essm/logger/detail/Filename.hpp>
#define __essm_logger_command(app, level, ...) \
::fmt::print("{}/{}/{}#{} {}\n", #level, app, __essm_logger_filename, __LINE__, ::fmt::format(__VA_ARGS__))
#include <essm/logger/detail/ExposeBackend.hpp>
