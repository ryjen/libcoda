
add_executable(${TEST_PROJECT_NAME} main.test.cpp bigint.test.cpp collections.test.cpp string.test.cpp argument.test.cpp buffer.test.cpp log.test.cpp terminal.test.cpp)

target_include_directories(${TEST_PROJECT_NAME} SYSTEM PUBLIC vendor/bandit PUBLIC ${PROJECT_SOURCE_DIR}/src PUBLIC ${PROJECT_SOURCE_DIR}/src/math)

target_link_libraries (${TEST_PROJECT_NAME} ${PROJECT_NAME})


