
set(LOG_LIBRARY coda_log)

add_library(${LOG_LIBRARY} log.cpp)

string(REPLACE "_" "/" INSTALL_DIRECTORY ${LOG_LIBRARY})

install(FILES log.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${INSTALL_DIRECTORY})

install(TARGETS ${LOG_LIBRARY} LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

create_packages(TARGET ${LOG_LIBRARY} VERSION 0.1.0 DESCRIPTION "A logging library")

