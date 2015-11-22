
add_subdirectory(db)
add_subdirectory(dice)
add_subdirectory(format)
add_subdirectory(json)
add_subdirectory(log)
add_subdirectory(math)
add_subdirectory(net)
add_subdirectory(string)
add_subdirectory(terminal)
add_subdirectory(variant)

add_library(${PROJECT_NAME} arg3.cpp)

target_link_libraries(${PROJECT_NAME} arg3db arg3dice arg3format arg3json arg3net arg3variant arg3log arg3math arg3str arg3term)

INSTALL(FILES thread/later.h collections/collections.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/arg3)

