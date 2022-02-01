cmake_minimum_required(VERSION 3.16)
project(lib_gpio LANGUAGES CXX C VERSION "1.0.0" DESCRIPTION "Lightweight Drivers for RPi GPIO")
set(CMAKE_C_STANDARD 99)
add_library(lib_gpio STATIC src/pwm.c)
set_target_properties(lib_gpio PROPERTIES VERSION ${PROJECT_VERSION} PREFIX "" SUFFIX ".a.${PROJECT_VERSION}")
target_include_directories(lib_gpio PUBLIC ${PROJECT_SOURCE_DIR}/include)
include(GNUInstallDirs)
install(TARGETS lib_gpio
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)