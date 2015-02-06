include_directories("${PROJECT_SOURCE_DIR}/libos")
include_directories("${PROJECT_SOURCE_DIR}/libnet")

add_executable(udp_s socket_s.cpp)
target_link_libraries(udp_s nsocket)

add_executable(udp_c socket_c.cpp)
target_link_libraries(udp_c nsocket)