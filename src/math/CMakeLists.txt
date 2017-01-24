
add_library(rj_math bigint.cpp)

install(FILES bigint.h util.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/rj/math)

install(TARGETS rj_math LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

create_package(TARGET rj_math VERSION 0.1.0 DESCRIPTION "Math utils")
