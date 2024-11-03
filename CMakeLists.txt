cmake_minimum_required(VERSION 3.18)

project(osinfo CXX)


set(CMAKE_CXX_STANDARD 23)


add_executable(${PROJECT_NAME}  
src/main.cpp
src/osinfo.cpp
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    "include/"
)

target_compile_options(
    ${PROJECT_NAME}
    PUBLIC
    "-Wall"
    "-Werror"
    "-Wno-unused"
)