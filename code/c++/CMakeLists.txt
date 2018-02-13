add_library(libreversi src/board.cc src/application.cc src/player.cc)
target_include_directories (libreversi PUBLIC $(CMAKE_CURRENT_SOURCE_DIR))

include_directories(include)
include_directories(include_tests)

find_library( CPPUNIT_LIBRARY_DEBUG NAMES cppunit cppunit_dll cppunitd cppunitd_dll
  PATHS
  /usr/lib
  /usr/lib64
  /usr/local/lib
  /usr/local/lib64
  PATH_SUFFIXES debug )

find_library( CPPUNIT_LIBRARY_RELEASE NAMES cppunit cppunit_dll
  PATHS
  /usr/lib
  /usr/lib64
  /usr/local/lib
  /usr/local/lib64
  PATH_SUFFIXES release )

if(CPPUNIT_LIBRARY_DEBUG AND NOT CPPUNIT_LIBRARY_RELEASE)
  set(CPPUNIT_LIBRARY_RELEASE ${CPPUNIT_LIBRARY_DEBUG})
endif(CPPUNIT_LIBRARY_DEBUG AND NOT CPPUNIT_LIBRARY_RELEASE)

set( CPPUNIT_LIBRARY debug     ${CPPUNIT_LIBRARY_DEBUG}
  optimized ${CPPUNIT_LIBRARY_RELEASE} )

# ...


add_executable(reversi main.cc src/board.cc src/application.cc src/player.cc)
add_executable(test_reversi test_main.cc tests/test_board.cc src/board.cc)
target_link_libraries(test_reversi LINK_PUBLIC libreversi cppunit)
