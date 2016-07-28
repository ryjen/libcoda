
add_library(rj_log log.cpp)

install(FILES log.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/rj/log)

install(TARGETS rj_log LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

# create the package config install
include(CreatePackage)
create_package_named(rj_log 0.1.0 "A logging library")

