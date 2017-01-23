
add_executable(${TEST_PROJECT_NAME} main.test.cpp variant.test.cpp binary.test.cpp)

target_include_directories(${TEST_PROJECT_NAME} SYSTEM PUBLIC ${CMAKE_SOURCE_DIR}/tests/vendor/bandit PUBLIC ${PROJECT_SOURCE_DIR}/src)

target_link_libraries(${TEST_PROJECT_NAME} ${PROJECT_NAME})

