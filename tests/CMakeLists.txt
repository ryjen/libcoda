
add_executable(${PROJECT_NAME}-test arg3.test.cpp bigint.test.cpp collections.test.cpp string.test.cpp argument.test.cpp buffer.test.cpp log.test.cpp terminal.test.cpp)

include_directories(SYSTEM vendor/bandit ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/src/math)

target_link_libraries (${PROJECT_NAME}-test ${PROJECT_NAME})


