#pragma once

#include <iostream>
#include <format>

#include "Filename.hpp"
#define essm_logger_command(app, level, ...) \
::std::cout << ::std::format("{}/{}/{}#{} {}\n", #level, app, essm_logger_filename, __LINE__, ::std::format(__VA_ARGS__));
#include "ExposeBackend.hpp"
