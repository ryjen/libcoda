
add_subdirectory(db)
add_subdirectory(dice)
add_subdirectory(format)
add_subdirectory(log)
add_subdirectory(math)
add_subdirectory(net)
add_subdirectory(string)
add_subdirectory(terminal)
#add_subdirectory(json)
#add_subdirectory(variant)

set(${PROJECT_NAME}_HEADERS thread/later.h utility/collections.h)

add_library(${PROJECT_NAME} ${${PROJECT_NAME}_HEADERS} version.cpp)

target_link_libraries(${PROJECT_NAME} coda_log coda_math coda_string coda_term)

INSTALL(FILES ${${PROJECT_NAME}_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/coda)

