
add_library(arg3log log.cpp)

install(FILES log.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/arg3log)

install(TARGETS arg3log LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

# create the package config install
include(CreatePackage)
create_package_named(arg3log 0.1.0 "A logging library")

