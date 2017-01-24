find_package(PkgConfig)

pkg_search_module(UUID uuid)

if (UUID_FOUND)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DUUID_FOUND")
endif()

add_library(rj_string argument.cpp buffer.cpp util.cpp)

target_link_libraries(rj_string ${UUID_LIBRARIES})

install(FILES argument.h buffer.h util.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/rj/string)

install(TARGETS rj_string LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

create_package(TARGET rj_string VERSION 0.1.0 DESCRIPTION "A string library")
