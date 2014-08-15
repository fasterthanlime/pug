cmake_minimum_required (VERSION 2.6)
project (pug)

# External projects
include(ExternalProject)

set(DEPS_LIST gc libcollections libjit greg jansson bstring)
set(DEPS ${CMAKE_SOURCE_DIR}/deps)
set(DEPS_PREFIX ${CMAKE_BINARY_DIR}/deps-prefix)

# Boehm's garbage collector
ExternalProject_add(
  gc
  SOURCE_DIR ${DEPS}/gc
  CONFIGURE_COMMAND ${DEPS}/gc/configure --prefix=${DEPS_PREFIX} --disable-shared
  BUILD_COMMAND make
  INSTALL_COMMAND make install
)

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

# Parser generator
ExternalProject_add(
  greg
  SOURCE_DIR ${DEPS}/greg
  CMAKE_COMMAND ${CMAKE_COMMAND}
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:STRING=${DEPS_PREFIX}
)

# JSON loading/saving
ExternalProject_add(
  jansson
  SOURCE_DIR ${DEPS}/jansson
  CMAKE_COMMAND ${CMAKE_COMMAND}
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:STRING=${DEPS_PREFIX} -DBUILD_DOCS:BOOL=OFF -DWITHOUT_TESTS:BOOL=ON
)

# C string manipulation
ExternalProject_add(
  bstring
  SOURCE_DIR ${DEPS}/bstring
  CMAKE_COMMAND ${CMAKE_COMMAND}
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:STRING=${DEPS_PREFIX} -DGC_INCLUDE_DIR:STRING=${DEPS_PREFIX}/include
  DEPENDS gc
)

# We'd like C99 support please.
set(CMAKE_C_FLAGS "-std=gnu99 -g -O0 -Wno-implicit-int")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,-rpath,${DEPS_PREFIX}/lib -pthread")
set(PUG_LIBS_NAMES jit collections jansson bstring gc)
foreach(lib ${PUG_LIBS_NAMES})
  find_library(
    ${lib}_LIB
    NAMES ${lib}
    PATHS ${DEPS_PREFIX}/lib
  )
  set(PUG_LIBS ${PUG_LIBS} ${${lib}_LIB})
endforeach()

# Generate the parser from the grammar please?
add_custom_command(
  OUTPUT ${CMAKE_SOURCE_DIR}/src/pug-parser/parser.c
  COMMAND ${CMAKE_BINARY_DIR}/deps-prefix/bin/greg -o ${CMAKE_SOURCE_DIR}/src/pug-parser/parser.c ${CMAKE_SOURCE_DIR}/grammar/pug.leg
  DEPENDS ${CMAKE_SOURCE_DIR}/grammar/pug.leg
)

# All source files
file(GLOB_RECURSE PUG_HEADERS src/pug/*.h)
file(GLOB_RECURSE PUG_SOURCES src/pug/*.c)

set(PUG_HEADERS ${PUG_HEADERS} src/pug-parser/parser.h)
set(PUG_SOURCES ${PUG_SOURCES} src/pug-parser/parser.c)

set(PUG_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src)
include_directories(${PUG_INCLUDE_DIR} ${DEPS_PREFIX}/include)

add_executable(pug ${PUG_HEADERS} ${PUG_SOURCES})
target_link_libraries(pug ${PUG_LIBS})

# We need our deps to build the compiler
add_dependencies(pug ${DEPS_LIST})

# test target
add_custom_target(tests "${CMAKE_SOURCE_DIR}/tests.sh")
add_dependencies(tests pug)

