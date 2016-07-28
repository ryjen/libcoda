
add_library(rj_term vt100.cpp)

install(FILES base_terminal.h vt100.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/rj/term)

install(TARGETS rj_term LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
