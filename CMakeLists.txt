cmake_minimum_required (VERSION 2.6)
project (pug)

# External projects
include(ExternalProject)

set(DEPS ${CMAKE_CURRENT_SOURCE_DIR}/deps)
set(DEPS_PREFIX ${DEPS}/prefix)

# Development dependencies
add_subdirectory(devdeps)

# Basic data structures for C
ExternalProject_add(
  libcollections
  SOURCE_DIR ${DEPS}/libcollections
  CONFIGURE_COMMAND ${DEPS}/libcollections/configure --prefix=${DEPS_PREFIX}
  BUILD_COMMAND make
  INSTALL_COMMAND make install
)

# GNU libjit - doesn't support out-of-tree build
# so our 'download' step is to copy it, then we enable
# CMake's BUILD_IN_SOURCE.
ExternalProject_add(
  libjit
  DOWNLOAD_COMMAND cmake -E copy_directory ${DEPS}/libjit ${CMAKE_CURRENT_BINARY_DIR}/libjit-source
  SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/libjit-source
  CONFIGURE_COMMAND ./configure --prefix=${DEPS_PREFIX}
  BUILD_IN_SOURCE 1
  BUILD_COMMAND make
  INSTALL_COMMAND make install
)

# We'd like C99 support please.
set(CMAKE_C_FLAGS "-std=gnu99")

# Generate the parser from the grammar please?
add_custom_command(
  OUTPUT ${CMAKE_SOURCE_DIR}/src/pug-parser/parser.c ${CMAKE_SOURCE_DIR}/src/pug-parser/parser.h
  COMMAND ${CMAKE_BINARY_DIR}/devdeps/packcc/packcc -o parser ${CMAKE_SOURCE_DIR}/grammar/pug.peg
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/src/pug-parser
  COMMAND ${CMAKE_COMMAND} -E rename ${CMAKE_BINARY_DIR}/parser.c ${CMAKE_SOURCE_DIR}/src/pug-parser/parser.c
  COMMAND ${CMAKE_COMMAND} -E rename ${CMAKE_BINARY_DIR}/parser.h ${CMAKE_SOURCE_DIR}/src/pug-parser/parser.h
  DEPENDS ${CMAKE_SOURCE_DIR}/grammar/pug.peg devdeps
)

# All source files
file(GLOB_RECURSE PUG_HEADERS src/pug/*.h)
file(GLOB_RECURSE PUG_SOURCES src/pug/*.c)

set(PUG_HEADERS ${PUG_HEADERS} src/pug-parser/parser.h)
set(PUG_SOURCES ${PUG_SOURCES} src/pug-parser/parser.c)

set(PUG_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src)
include_directories(${PUG_INCLUDE_DIR} ${DEPS_PREFIX}/include)

add_executable(pug ${PUG_HEADERS} ${PUG_SOURCES})

