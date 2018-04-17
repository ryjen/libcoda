
set(TERM_LIBRARY coda_term)

set(${TERM_LIBRARY}_HEADERS output.h cursor.h progress.h color.h base_terminal.h)

add_library(${TERM_LIBRARY} ${${TERM_LIBRARY}_HEADERS} vt100.cpp color.cpp output.cpp cursor.cpp progress.cpp)

string(REPLACE "_" "/" INSTALL_DIRECTORY ${TERM_LIBRARY})

install(FILES base_terminal.h vt100.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${INSTALL_PATH})

install(TARGETS ${TERM_LIBRARY} LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
