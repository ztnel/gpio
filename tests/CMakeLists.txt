message(STATUS "Adding fff dependancy")
add_library(fff INTERFACE)
target_include_directories(
  fff
  INTERFACE
  ${PROJECT_SOURCE_DIR}/build/_deps/fff-src
)

include_directories(
  ${PROJECT_SOURCE_DIR}/include
)

message(STATUS "Running test configuration")

set(TESTS
  ${PROJECT_SOURCE_DIR}/tests/test_pwm.cpp
  ${PROJECT_SOURCE_DIR}/tests/test_sysfs.cpp
)

foreach(file ${TESTS})
  set(name)
  get_filename_component(name ${file} NAME_WE)
  add_executable(
    ${name}
    ${file}
    ${PROJECT_SOURCE_DIR}/tests/main.cpp
  )
  target_link_libraries(${name} gtest_main fff gpio-static) 
  add_test(NAME ${name} COMMAND ${name})
endforeach()

