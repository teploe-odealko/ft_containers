cmake_minimum_required(VERSION 3.21)
project(containers)

set(CMAKE_CXX_STANDARD 98)

SET(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")
add_compile_definitions(FT)
add_executable(containers
        main.cpp
        vector.cpp vector.hpp
        )
