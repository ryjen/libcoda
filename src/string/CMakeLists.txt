find_package(PkgConfig)

set(STRING_LIBRARY coda_string)

pkg_search_module(UUID uuid)

set(${STRING_LIBRARY}_HEADERS argument.h buffer.h util.h )

add_library(${STRING_LIBRARY} ${${STRING_LIBRARY}_HEADERS} argument.cpp buffer.cpp util.cpp)
target_compile_features(${STRING_LIBRARY} PUBLIC cxx_std_17)

if (UUID_FOUND)
  target_compile_definitions(${STRING_LIBRARY} PRIVATE UUID_FOUND)
endif()

target_link_libraries(${STRING_LIBRARY} ${UUID_LIBRARIES})

string(REPLACE "_" "/" INSTALL_DIRECTORY ${STRING_LIBRARY})

install(FILES ${${STRING_LIBRARY}_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${INSTALL_DIRECTORY})

install(TARGETS ${STRING_LIBRARY} LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

create_packages(TARGET ${STRING_LIBRARY} VERSION 0.1.0 DESCRIPTION "A string library")

