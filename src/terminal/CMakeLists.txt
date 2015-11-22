
add_library(argterm vt100.cpp)

install(FILES base_terminal.h vt100.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/arg3term)

