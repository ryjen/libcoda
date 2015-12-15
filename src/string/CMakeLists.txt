find_package(PkgConfig)

pkg_search_module(UUID uuid)

if (UUID_FOUND)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DUUID_FOUND")
endif()

add_library(arg3str argument.cpp buffer.cpp util.cpp)

target_link_libraries(arg3str ${UUID_LIBRARIES})

install(FILES argument.h buffer.h util.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/arg3str)

install(TARGETS arg3str LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

# create the package config install
include(CreatePackage)
create_package_named(arg3str 0.1.0 "A string library")
