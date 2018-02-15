#include "test_board.hh"
#include <iostream>
#include <cmath>

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

  bool test_board::check_bitboard (__int128 expected, __int128 actual)
  {
    /* Splitting the first int128 in half */
    uint64_t expected_first_half = expected;
    uint64_t expected_second_half = expected>>HALF_BITBOARD;
    /* Splitting the second int128 in half */
    uint64_t actual_first_half = actual;
    uint64_t actual_second_half = actual>>HALF_BITBOARD;

    if (expected_first_half == actual_first_half)
      return (expected_second_half == actual_second_half);
    return false;
  }

  void test_board::test_check_bitboard ()
  {
    __int128 first = 0;
    __int128 second = 0;
    CPPUNIT_ASSERT (check_bitboard(first, second));

    first = 1024;
    second = 1024;
    CPPUNIT_ASSERT (check_bitboard(first, second));

    first = pow (64, 2) - 1;
    second = pow (64, 2) - 1;
    CPPUNIT_ASSERT (check_bitboard(first, second));

    first = pow (128, 2) - 1;
    second = pow (128, 2) - 1;
    CPPUNIT_ASSERT (check_bitboard(first, second));

    first = pow (64, 2) - 1;
    second = pow (128, 2) - 1;
    CPPUNIT_ASSERT (!check_bitboard(first, second));

    first = pow (128, 2) - 1;
    second = -first;
    CPPUNIT_ASSERT (!check_bitboard(first, second));

    first = -64;
    second = -64;
    CPPUNIT_ASSERT (check_bitboard(first, second));
  }
}
