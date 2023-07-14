#pragma once

#include <iostream>
#include <format>

#include <essm/logger/detail/Filename.hpp>
#define __essm_logger_command(app, level, ...) \
::std::cout << ::std::format("{}/{}/{}#{} {}\n", #level, app, __essm_logger_filename, __LINE__, ::std::format(__VA_ARGS__));
#include <essm/logger/detail/ExposeBackend.hpp>
