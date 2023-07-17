# `essm::logger`: logging interface

The `essm::logger` module provides interface for calling loggers. The `essm::logger` is used internally by all the
`essm` libraries for providing logs. Those loggers can be configured to use different backends or disabled altogether
(which entirely disables library logs).

## Configuration

The logger interface in big part uses preprocessor macros, and can be configured using compiler definitions:

* `ESSM_LOGGER_BACKEND` – backend selection, available options:
    * `std` – use standard library 
    * `fmt` – use {fmt} library
    * `spdlog` – use spdlog
    * other values – disable logging
* `ESSM_LOGGER_ENABLE_DEBUG` – enables debug logs
* `ESSM_LOGGER_DEFAULT_NAME` – the library name to be printed in this compilation unit, defaults to "Application"

## Usage

The log macros accept the [{fmt} format](https://hackingcpp.com/cpp/libs/fmt.html):

```c++
essm_info("Just giving some information");
auto value = 10;
essm_debug("Value is {}!", value); // no-op if debug logs are disabled
essm_warn("Something suspicious happened...");
essm_error("Wrong! Hex value: {:#x}", value);
```

Possible output:

```
INF/Application [example.cpp:12] Just giving some information!
DBG/Application [example.cpp:14] Value is 10!
WRN/Application [example.cpp:15] Something suspicious happened...
ERR/Application [example.cpp:16] Wrong! Hex value: 0xa
```

## Backends

### Standard library

Uses the standard library for logging output, printing the logs to stdout. This requires the `<format>` header to be
available.

### {fmt} logger

Uses {fmt} library for logging output.

### spdlog

Simply forwards the logging commands to `spdlog` library.
