#include "test_board.hh"
#include <iostream>

#define HALF_BITBOARD 64

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

  void test_board::check_bitboard (__int128 expected, __int128 actual)
  {
    /* Splitting the first int128. */
    uint64_t expected_first_half = expected;
    uint64_t expected_second_half = expected>>HALF_BITBOARD;
    /* Splitting the second int128 */
    uint64_t actual_first_half = actual;
    uint64_t actual_second_half = actual>>HALF_BITBOARD;
    
    CPPUNIT_ASSERT_EQUAL (expected_first_half, actual_first_half);
    CPPUNIT_ASSERT_EQUAL (expected_second_half, actual_second_half);
    
  }

  void test_board::dummy_test ()
  {
    reversi::board::bitboard bit1 = 127;
    reversi::board::bitboard bit2 = 127;
    check_bitboard (bit1, bit2);
  }
}
