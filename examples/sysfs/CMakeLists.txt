cmake_minimum_required(VERSION 3.16.0)

project(sysfs_driver)

message(STATUS "Building Sysfs Example Driver")
add_executable(ex-sysfs main.c)
target_link_libraries(ex-sysfs PRIVATE gpio-static merase-static)