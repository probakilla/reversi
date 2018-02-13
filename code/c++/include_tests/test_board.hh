#ifndef TEST_BOARD_HH
#define TEST_BOARD_HH

#include "board.hh"
#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

namespace tests
{
  class test_board : public CppUnit::TestCase
  {
    CPPUNIT_TEST_SUITE(test_board);
    CPPUNIT_TEST_SUITE_END();
    
  private:
    reversi::board* _fixture;
        
  public:
    void setUp ();
    void tearDown ();
  };
}
#endif /* !defined(TEST_BOARD_HH) */
