#ifndef TEST_BOARD_HH
#define TEST_BOARD_HH

#include "board.hh"

namespace tests
{
  class test_board : public CppUnit::TestFixture
  {
  public:
    void setUp (void);
    void tearDown (void);

  private:
    Board* _board;
  };
  
}
#endif /* !defined(TEST_BOARD_HH) */
