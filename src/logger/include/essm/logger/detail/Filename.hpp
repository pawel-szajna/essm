#pragma once

#include <string_view>

#define essm_logger_filename_position \
 (::std::string_view(__FILE__).rfind('/') != ::std::string_view::npos ? ::std::string_view(__FILE__).rfind('/') + 1 : 0)

#define essm_logger_filename \
 (::std::string_view(__FILE__).substr(essm_logger_filename_position))
