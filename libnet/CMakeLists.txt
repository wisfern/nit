PROJECT(libnet)

set(net_SRCS
  nsocket.cpp
)

if(MSVC)
    add_definitions("-DNIT_EXPORTS -D_CRT_SECURE_NO_WARNINGS")
    #set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DNIT_EXPORTS -D_CRT_SECURE_NO_WARNINGS")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNIT_EXPORTS -D_CRT_SECURE_NO_WARNINGS")
endif()

add_library(net_s STATIC ${net_SRCS}) 
set_target_properties(net_s PROPERTIES OUTPUT_NAME "nsocket")
set_target_properties(net_s PROPERTIES CLEAN_DIRECT_OUTPUT 1)

if (NIT_MK_SHARED_LIB)
  add_library(net SHARED ${net_SRCS})		
  set_target_properties(net PROPERTIES OUTPUT_NAME "nsocket")
  set_target_properties(net PROPERTIES VERSION 1.0 SOVERSION 1)
  set_target_properties(net PROPERTIES CLEAN_DIRECT_OUTPUT 1)
endif(NIT_MK_SHARED_LIB)

#add_subdirectory(tests)

