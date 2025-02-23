cmake_minimum_required(VERSION 3.22)

project(checkers CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_DEBUG_POSTFIX "d")

add_compile_options("-fPIC")

add_executable(checkers)

target_sources(checkers
    PRIVATE
        src/main.cpp
        src/game.cpp
        src/system.cpp
)

set_target_properties(checkers PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build
)

target_include_directories(checkers
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
)
