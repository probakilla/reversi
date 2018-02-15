cmake_minimum_required(VERSION 3.5.1)
project(Reversi)
enable_language(CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
add_compile_options(-Wall -Wextra)
add_library (libreversi src/board.cc src/player.cc src/user.cc src/random_ia.cc)
target_include_directories (libreversi PUBLIC $(CMAKE_CURRENT_SOURCE_DIR))
include_directories (include)
add_executable (reversi main.cc src/board.cc src/player.cc src/user.cc src/random_ia.cc)

option(PEDANTIC "PEDANTIC FLAG ON" OFF)
if (PEDANTIC)
  add_compile_options(-Wpedantic)
endif()

option(TESTS "BUILING TESTS" OFF)
if (TESTS)

include_directories (tests)

find_library (CPPUNIT_LIBRARY_DEBUG NAMES cppunit cppunit_dll
  cppunitd cppunitd_dll
  PATHS
  /usr/lib
  /usr/lib64
  /usr/local/lib
  /usr/local/lib64
  PATH_SUFFIXES debug)

find_library(CPPUNIT_LIBRARY_RELEASE NAMES cppunit cppunit_dll
  PATHS
  /usr/lib
  /usr/lib64
  /usr/local/lib
  /usr/local/lib64
  PATH_SUFFIXES release)

if (CPPUNIT_LIBRARY_DEBUG AND NOT CPPUNIT_LIBRARY_RELEASE)
  set(CPPUNIT_LIBRARY_RELEASE ${CPPUNIT_LIBRARY_DEBUG})
endif(CPPUNIT_LIBRARY_DEBUG AND NOT CPPUNIT_LIBRARY_RELEASE)

set( CPPUNIT_LIBRARY debug ${CPPUNIT_LIBRARY_DEBUG}
  optimized ${CPPUNIT_LIBRARY_RELEASE})

add_executable (test_reversi tests_main.cc tests/test_board.cc src/board.cc)

target_link_libraries (test_reversi LINK_PUBLIC libreversi cppunit)
endif()
