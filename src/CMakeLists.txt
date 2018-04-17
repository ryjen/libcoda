
add_subdirectory(db)
add_subdirectory(dice)
add_subdirectory(format)
add_subdirectory(log)
add_subdirectory(math)
add_subdirectory(net)
add_subdirectory(string)
add_subdirectory(terminal)
add_subdirectory(thread)
add_subdirectory(utility)
#add_subdirectory(json)
#add_subdirectory(variant)

add_library(${PROJECT_NAME} ${${PROJECT_NAME}_HEADERS} version.cpp)

target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_log ${PROJECT_NAME}_math ${PROJECT_NAME}_string ${PROJECT_NAME}_term)
