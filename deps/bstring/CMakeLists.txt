cmake_minimum_required(VERSION 2.8)

project(bstring)

add_library(bstring STATIC
  bstraux.h
  bstrlib.h
  bstrwrap.h
  bstraux.c
  bstrlib.c
)

install (TARGETS bstring
   ARCHIVE DESTINATION lib
   LIBRARY DESTINATION lib
   RUNTIME DESTINATION bin
)
