add_library(${PROJECT_NAME} array.cpp array_iterator.cpp object.cpp object_iterator.cpp)

include_directories(${JSON_C_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} ${JSON_C_LIBRARIES})

set(${PROJECT_NAME}_HEADERS
  array.h
  array_iterator.h
  exception.h
  json.h
  object.h
  object_iterator.h
)

string(REPLACE "_" "/" INSTALL_DIRECTORY ${PROJECT_NAME})

install(FILES ${${PROJECT_NAME}_HEADERS} DESTINATION "${CMAKE_INSTALL_PREFIX}/include/${INSTALL_DIRECTORY}")

install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)

