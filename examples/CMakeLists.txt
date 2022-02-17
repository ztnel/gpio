cmake_minimum_required(VERSION 3.15)
project(gpio_examples)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add merase library
include(FetchContent)
message(STATUS "Fetching static dependancies")
FetchContent_Declare(
  merase
  GIT_REPOSITORY https://github.com/ztnel/merase
  GIT_TAG v0.1.5
)
FetchContent_MakeAvailable(merase)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/.. ${CMAKE_BINARY_DIR}/gpio)
include_directories(${GPIO_INCLUDES} ${MERASE_INCLUDE})
add_subdirectory(pwm)
add_subdirectory(sysfs)