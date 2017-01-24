
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

add_library(${PROJECT_NAME} version.cpp)

target_link_libraries(${PROJECT_NAME} rj_db rj_dice rj_format rj_json rj_net rj_variant rj_log rj_math rj_string rj_term)

INSTALL(FILES thread/later.h collections/collections.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/rj)

