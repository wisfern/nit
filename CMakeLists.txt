cmake_minimum_required (VERSION 2.8)

project(nit)

#if(NOT CMAKE_BUILD_TYPE)
#  set(CMAKE_BUILD_TYPE "Debug")
#endif()

#set(CMAKE_VERBOSE_MAKEFILE ON)
set(NIT_MK_SHARED_LIB FALSE)
option(BUILD_64_BITS '±‡“Î64Œª≥Ã–Ú∫Õø‚' FALSE)

configure_file (
  "${PROJECT_SOURCE_DIR}/libtech/libconfig.h.in"
  "${PROJECT_BINARY_DIR}/libconfig.h"
  )

# include directories
include_directories("${PROJECT_SOURCE_DIR}/libos")
include_directories("${PROJECT_SOURCE_DIR}/libtech")
include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_BINARY_DIR}")

# lib directories
LINK_DIRECTORIES(
  ${PROJECT_BINARY_DIR}/lib
  )

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

if(BUILD_64)
  if(AIX)
    add_definitions(-q64)
  endif(AIX)
  if(LINUX)
    add_definitions(-m64)
  endif(AIX)
endif(BUILD_64)

#add_definitions("-Wall")

#if(MSVC)
    #set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DNIT_EXPORTS -D_CRT_SECURE_NO_WARNINGS")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNIT_EXPORTS -D_CRT_SECURE_NO_WARNINGS")
#endif()

add_subdirectory(libtech)
add_subdirectory(libnet)
add_subdirectory(test)

