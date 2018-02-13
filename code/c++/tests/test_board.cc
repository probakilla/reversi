#include <iostream>

#include "test_board.hh"

namespace tests
{
  CPPUNIT_TEST_SUITE_REGISTRATION (test_board);
  
  void test_board::setUp ()
  {
    _fixture = new reversi::board ();
  }

  void test_board::tearDown ()
  {
    delete _fixture;
    _fixture = NULL;
  }
}
