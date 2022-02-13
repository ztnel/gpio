cmake_minimum_required(VERSION 3.16.0)

project(pwm_driver)

message(STATUS "Building PWM Example Driver")
add_executable(ex-pwm main.c)
target_link_libraries(ex-pwm gpio-static)