#ifndef TEST_BOARD_HH
#define TEST_BOARD_HH

#include "board.hh"
#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

namespace tests
{
  class test_board : public CppUnit::TestCase
  {
    CPPUNIT_TEST_SUITE (test_board);
    CPPUNIT_TEST (dummy_test);
    CPPUNIT_TEST_SUITE_END ();
    
  private:
    reversi::board* _fixture;
	
    /*
     * Function used to check if a bitboard correspond the wanted
     * value by dividing it in two __int64.
     */
    void check_bitboard (__int128 expected, __int128 acutal);
  public:

    /*
     * Used for the instanciation of _fixture.
     */
    void setUp ();

    /*
     * Used for freeing _fixture.
     */
    void tearDown ();

    /* TO DELETE */
    void dummy_test ();
  };
}

#endif /* !defined(TEST_BOARD_HH) */
