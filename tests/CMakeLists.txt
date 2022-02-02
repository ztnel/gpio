include_directories("${PROJECT_SOURCE_DIR}/include")

message(STATUS "Running test configuration")
set(SOURCES 
    ${PROJECT_SOURCE_DIR}/src/pwm.c
)

set(TESTS
    ${PROJECT_SOURCE_DIR}/tests/test_pwm.cpp
)

foreach(file ${TESTS})
  set(name)
  get_filename_component(name ${file} NAME_WE)
  add_executable("${name}"
    ${SOURCES}
    ${file}
    "${PROJECT_SOURCE_DIR}/tests/main.cpp")
  target_link_libraries("${name}" gtest_main)
  add_test(NAME ${name} COMMAND "${name}")
endforeach()