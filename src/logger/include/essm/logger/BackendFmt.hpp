#pragma once

#include <fmt/core.h>

#include "Filename.hpp"
#define essm_logger_command(app, level, ...) \
::fmt::print("{}/{}/{}#{} {}\n", #level, app, essm_logger_filename, __LINE__, ::fmt::format(__VA_ARGS__))
#include "ExposeBackend.hpp"
