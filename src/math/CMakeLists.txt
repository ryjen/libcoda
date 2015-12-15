
add_library(arg3math bigint.cpp)

install(FILES bigint.h util.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/arg3math)

install(TARGETS arg3math LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

# create the package config install
include(CreatePackage)
create_package_named(arg3math 0.1.0 "A math library")
