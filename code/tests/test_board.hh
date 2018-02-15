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
    CPPUNIT_TEST (test_check_bitboard);
    CPPUNIT_TEST_SUITE_END ();
    
  private:
    reversi::board* _fixture;
	
    /*
     * Function used to check if a bitboard correspond the wanted
     * value by dividing it in two __int64.
     */
    bool check_bitboard (__int128 expected, __int128 acutal);
  public:

    /*
     * Used for the instanciation of _fixture.
     */
    void setUp ();

    /*
     * Used for freeing _fixture.
     */
    void tearDown ();

    /*
     * Testing the check_bitboard function.
     */
    void test_check_bitboard ();
  };
}

#endif /* !defined(TEST_BOARD_HH) */
