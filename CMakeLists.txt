cmake_minimum_required(VERSION 3.16)

project(gpio LANGUAGES CXX C VERSION "1.0.0" DESCRIPTION "Lightweight Drivers for RPi GPIO")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

# set log level through cli
if(NOT GPIO_LOG_LEVEL)
  set(GPIO_LOG_LEVEL "ERROR")
endif()

add_library(
  gpio-static
  STATIC
  src/pwm.c
  src/sysfs.c
)
target_compile_definitions(gpio-static PRIVATE GPIO_LOG_LEVEL=${GPIO_LOG_LEVEL})
set_target_properties(gpio-static PROPERTIES VERSION ${PROJECT_VERSION})
target_include_directories(gpio-static PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(gpio-static PRIVATE -Wall -Wextra -Wshadow -Wconversion -Wformat -Wundef -fno-common)
set(GPIO_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/include PARENT_SCOPE)

if(CMAKE_BUILD_TYPE MATCHES "Debug")
  # Setup coverage with gcov
  include(tests/modules/CodeCoverage.cmake)
  append_coverage_compiler_flags()
  set(COVERAGE_EXCLUDES "${PROJECT_SOURCE_DIR}/tests/*" "${PROJECT_SOURCE_DIR}/main.c" "${PROJECT_SOURCE_DIR}/build/*")
  setup_target_for_coverage_gcovr_xml(
      NAME cov
      EXECUTABLE GTEST_COLOR=1 ctest -V
  )

  # setup gtest and fff
  include(FetchContent)
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