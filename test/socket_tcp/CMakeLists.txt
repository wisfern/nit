include_directories("${PROJECT_SOURCE_DIR}/libos")
include_directories("${PROJECT_SOURCE_DIR}/libnet")

add_executable(socket_s socket_s.cpp)
target_link_libraries(socket_s nsocket)

add_executable(socket_c socket_c.cpp)
target_link_libraries(socket_c nsocket)