
add_library(rj_log log.cpp)

install(FILES log.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/rj/log)

install(TARGETS rj_log LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

create_package(TARGET rj_log VERSION 0.1.0 DESCRIPTION "A logging library")

