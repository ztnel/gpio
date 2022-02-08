cmake_minimum_required(VERSION 3.16.0)

project(pwm_driver)

message(STATUS "Building PWM Example Driver")
add_executable(example_pwm_driver main.c)
target_link_libraries(example_pwm_driver gpio-static)