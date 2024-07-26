cmake_minimum_required(VERSION 3.10)

project(
    design_patterns
    VERSION 1.0
)

# Generate compiler json commands, this is use by LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

message(STATUS "----------INFO----------")
message(STATUS "CMake version: ${CMAKE_VERSION}")
message(STATUS "CMake system name: ${CMAKE_SYSTEM_NAME}")
message(STATUS "CMake system version: ${CMAKE_SYSTEM_VERSION}")
# Print C++ compiler information
message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "C++ compiler version: ${CMAKE_CXX_COMPILER_VERSION}")
# Print the build type
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
# Print C++ flags
message(STATUS "C++ flags: ${CMAKE_CXX_FLAGS}")
message(STATUS "C++ flags (Debug): ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "C++ flags (Release): ${CMAKE_CXX_FLAGS_RELEASE}")
# Print C++ standard
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "-----------------------")

add_subdirectory(src)
