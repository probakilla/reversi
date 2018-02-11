#ifndef TEST_BOARD_HH
#define TEST_BOARD_HH

#include "board.hh"
#include <cppunit/TestCase.h>

namespace tests
{
  class test_board : public CppUnit::TestFixture
  {    
  private:
    reversi::board* _board;
    
  public:
    void setUp (void);
    void tearDown (void);
    void test_switch_turn (void);
  };
  
}
#endif /* !defined(TEST_BOARD_HH) */
