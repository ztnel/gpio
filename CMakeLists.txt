cmake_minimum_required(VERSION 3.16)

project(
  gpio
  LANGUAGES CXX C
  VERSION "1.0.0"
  DESCRIPTION "Lightweight Drivers for RPi GPIO"
)

# cmake build guard
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
  )
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 11)

# Detect if the project is being build within a project or standalone.
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(STANDALONE true)
  # Configure the build path
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
else()
  set(STANDALONE false)
endif()

# set log level through cli
if(NOT GPIO_LOG_LEVEL)
  set(GPIO_LOG_LEVEL "ERROR")
endif()

# Add merase library
include(FetchContent)
message(STATUS "Fetching static dependancies")
FetchContent_Declare(
  merase
  GIT_REPOSITORY https://github.com/ztnel/merase
  GIT_TAG v0.1.5
)
FetchContent_MakeAvailable(merase)

add_library(
  gpio-static
  STATIC
  src/pwm.c
  src/sysfs.c
)
include_directories(${MERASE_INCLUDE})
target_link_libraries(gpio-static PRIVATE merase-static)
target_compile_definitions(gpio-static PRIVATE GPIO_LOG_LEVEL=${GPIO_LOG_LEVEL})
set_target_properties(gpio-static PROPERTIES VERSION ${PROJECT_VERSION})
target_include_directories(gpio-static PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(gpio-static PRIVATE -Wall -Wextra -Wshadow -Wconversion -Wformat -Wundef -fno-common)

if (NOT ${STANDALONE})
  set(GPIO_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/include PARENT_SCOPE)
endif()

if(CMAKE_BUILD_TYPE MATCHES "Debug" AND ${STANDALONE})
  message(STATUS "Building ${PROJECT_NAME} with debug flag")
  message(STATUS "Configuring code coverage")
  # Setup coverage with gcov
  FetchContent_Declare(
    cmake 
    GIT_REPOSITORY https://github.com/bilke/cmake-modules.git
    GIT_TAG        770145a3338408bff34e2e7bdec15ee4e4ae2b79
  )
  FetchContent_MakeAvailable(cmake)
  include(${CMAKE_BINARY_DIR}/_deps/cmake-src/CodeCoverage.cmake)
  append_coverage_compiler_flags()
  set(COVERAGE_EXCLUDES "${PROJECT_SOURCE_DIR}/tests/*" "${PROJECT_SOURCE_DIR}/main.c" "${PROJECT_SOURCE_DIR}/build/*")
  setup_target_for_coverage_gcovr_xml(
    NAME cov
    EXECUTABLE GTEST_COLOR=1 ctest -V
  )
  message(STATUS "Fetching unittest dependancies")
  # setup gtest and fff
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        703bd9caab50b139428cea1aaff9974ebee5742e # release-1.10.0
  )
  FetchContent_Declare(
    fff
    GIT_REPOSITORY https://github.com/meekrosoft/fff
    GIT_TAG v1.1 
  )
  FetchContent_MakeAvailable(googletest) 
  FetchContent_GetProperties(fff)
  # remove gtest confliction
  if(NOT fff_POPULATED)
    FetchContent_Populate(fff)
    file(REMOVE_RECURSE ${fff_SOURCE_DIR}/gtest)
  endif()

  enable_testing()
  add_subdirectory(tests)
endif()