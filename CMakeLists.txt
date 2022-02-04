cmake_minimum_required(VERSION 3.16)
project(lib_gpio LANGUAGES CXX C VERSION "1.0.0" DESCRIPTION "Lightweight Drivers for RPi GPIO")
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
add_library(lib_gpio STATIC src/pwm.c)
set_target_properties(lib_gpio PROPERTIES VERSION ${PROJECT_VERSION} PREFIX "" SUFFIX ".a.${PROJECT_VERSION}")
target_include_directories(lib_gpio PUBLIC ${PROJECT_SOURCE_DIR}/include)
include(GNUInstallDirs)
install(TARGETS lib_gpio
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

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
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_Declare(
  fff
  GIT_REPOSITORY https://github.com/meekrosoft/fff
  GIT_TAG 7e09f07e5b262b1cc826189dc5057379e40ce886
)

FetchContent_MakeAvailable(googletest fff)

enable_testing()
add_subdirectory(tests)