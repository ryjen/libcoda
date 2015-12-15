
add_library(arg3term vt100.cpp)

install(FILES base_terminal.h vt100.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/arg3term)

install(TARGETS arg3term LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
