
add_library(rj_math bigint.cpp)

install(FILES bigint.h util.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/rj/math)

install(TARGETS rj_math LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

# create the package config install
include(CreatePackage)
create_package_named(rj_math 0.1.0 "A math library")
