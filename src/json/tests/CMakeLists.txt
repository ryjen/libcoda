
add_executable(${TEST_PROJECT_NAME} main.test.cpp array.test.cpp object.test.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DROOT_PATH=\\\"${PROJECT_SOURCE_DIR}/tests\\\"")

target_include_directories(${TEST_PROJECT_NAME} SYSTEM PUBLIC ${CMAKE_SOURCE_DIR}/tests/vendor/bandit PUBLIC ${PROJECT_SOURCE_DIR}/src SYSTEM PUBLIC ${JSON_C_INCLUDE_DIR})

target_link_libraries(${TEST_PROJECT_NAME} ${PROJECT_NAME})


