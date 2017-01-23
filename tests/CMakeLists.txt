
add_executable(${PROJECT_NAME}_test main.test.cpp bigint.test.cpp collections.test.cpp string.test.cpp argument.test.cpp buffer.test.cpp log.test.cpp terminal.test.cpp)

target_include_directories(${PROJECT_NAME}_test SYSTEM PUBLIC vendor/bandit PUBLIC ${PROJECT_SOURCE_DIR}/src PUBLIC ${PROJECT_SOURCE_DIR}/src/math)

target_link_libraries (${PROJECT_NAME}_test ${PROJECT_NAME})


