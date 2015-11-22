
add_library(arg3math bigint.cpp)

install(FILES bigint.h math_util.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/arg3math)

