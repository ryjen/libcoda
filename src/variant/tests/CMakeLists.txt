
add_executable(${TARGET_NAME}_test main.test.cpp variant.test.cpp)

add_executable(${TARGET_NAME}_binary_test main.test.cpp binary.test.cpp)

include_directories(SYSTEM vendor/bandit ${PROJECT_SOURCE_DIR}/src)

target_link_libraries (${TARGET_NAME}_test ${TARGET_NAME})

target_link_libraries(${TARGET_NAME}_binary_test ${TARGET_NAME})
