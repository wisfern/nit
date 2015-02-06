PROJECT(libtech)

set(base_SRCS
  Date.cpp
  Digest.cpp
  Exception.cpp
  hash.cpp
  Mutex.cpp
  StringUtils.cpp
  libmissing.cpp
)

if(MSVC)
    add_definitions("-DNIT_EXPORTS -D_CRT_SECURE_NO_WARNINGS")
    #set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DNIT_EXPORTS -D_CRT_SECURE_NO_WARNINGS")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNIT_EXPORTS -D_CRT_SECURE_NO_WARNINGS")
endif()

add_library(tech STATIC ${base_SRCS}) 
set_target_properties(tech PROPERTIES CLEAN_DIRECT_OUTPUT 1)

if (NIT_MK_SHARED_LIB)
  add_library(tech_s SHARED ${base_SRCS})	
  set_target_properties(tech PROPERTIES OUTPUT_NAME "tech")	
  set_target_properties(tech_s PROPERTIES VERSION 1.0 SOVERSION 1)
  set_target_properties(tech_s PROPERTIES CLEAN_DIRECT_OUTPUT 1)
endif(NIT_MK_SHARED_LIB)

if (UNIX)
  target_link_libraries(tech pthread)
endif(UNIX)

add_subdirectory(tests)

