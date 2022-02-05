cmake_minimum_required(VERSION 3.16)

project(lib_gpio LANGUAGES CXX C VERSION "1.0.0" DESCRIPTION "Lightweight Drivers for RPi GPIO")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

add_library(lib_gpio STATIC src/pwm.c src/sysfs.c)
set_target_properties(lib_gpio PROPERTIES VERSION ${PROJECT_VERSION} PREFIX "" SUFFIX ".a.${PROJECT_VERSION}")
target_include_directories(lib_gpio PUBLIC ${PROJECT_SOURCE_DIR}/include)
include(GNUInstallDirs)
install(TARGETS lib_gpio
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

if(CMAKE_BUILD_TYPE MATCHES "Debug")
  # Setup coverage with gcov
  include(tests/CodeCoverage.cmake)
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
    GIT_TAG 7e09f07e5b262b1cc826189dc5057379e40ce886
  )
  FetchContent_MakeAvailable(googletest fff)
  # remove gtest confliction
  if(NOT fff_POPULATED)
    FetchContent_Populate(fff)
    file(REMOVE_RECURSE ${fff_SOURCE_DIR}/gtest)
  endif()

  enable_testing()
  add_subdirectory(tests)
endif()