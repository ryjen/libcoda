
add_library(arg3str argument.cpp buffer.cpp str_util.cpp)

install(FILES argument.h buffer.h str_util.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/arg3str)

