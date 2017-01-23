
add_executable(${PROJECT_NAME}_test main.test.cpp array.test.cpp object.test.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DROOT_PATH=\\\"${PROJECT_SOURCE_DIR}/tests\\\"")

include_directories(SYSTEM vendor/bandit ${PROJECT_SOURCE_DIR}/src SYSTEM ${JSON_C_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME})

add_test(${PROJECT_NAME} ${PROJECT_NAME}_test)

