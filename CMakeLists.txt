cmake_minimum_required (VERSION 2.6)
project (pug)

# External projects
include(ExternalProject)

set(DEPS ${CMAKE_CURRENT_SOURCE_DIR}/deps)
set(DEPS_PREFIX ${DEPS}/prefix)

# Basic data structures for C
ExternalProject_add(
  libcollections
  SOURCE_DIR ${DEPS}/libcollections
  CONFIGURE_COMMAND ${DEPS}/libcollections/configure --prefix=${DEPS_PREFIX}
  BUILD_COMMAND make
  INSTALL_COMMAND make install
)

ExternalProject_add(
  libjit
  SOURCE_DIR ${DEPS}/libjit
  CONFIGURE_COMMAND ${DEPS}/libjit/configure --prefix=${DEPS_PREFIX}
  BUILD_IN_SOURCE 1
  BUILD_COMMAND make
  INSTALL_COMMAND make install
)

# We'd like C99 support please.
set(CMAKE_C_FLAGS "-std=c99")

# All source files
file(GLOB_RECURSE HDRS src/*.h)
file(GLOB_RECURSE SRCS src/*.c)
set(PUG_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${PUG_INCLUDE_DIR} ${DEPS_PREFIX}/include)

add_executable(pug ${HDRS} ${SRCS})
