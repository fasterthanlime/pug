cmake_minimum_required(VERSION 2.8)

project(bstring)

add_definitions(-DBSTR_USE_GC)
set(CMAKE_C_FLAGS "-I${GC_INCLUDE_DIR}")

set(BSTRING_HEADERS
  bstraux.h
  bstrlib.h
  bstrwrap.h
)

set(BSTRING_SOURCES
  bstraux.c
  bstrlib.c
)

add_library(bstring STATIC ${BSTRING_HEADERS} ${BSTRING_SOURCES})

install (TARGETS bstring
   ARCHIVE DESTINATION lib
   LIBRARY DESTINATION lib
   RUNTIME DESTINATION bin
)

install (FILES ${BSTRING_HEADERS}
  DESTINATION include
)

