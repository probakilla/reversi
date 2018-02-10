#include <isotream>
#include <cppunit>

#include "test_board.hh"

using namespace CppUnit;
using namespace reversi;

void test_board::setUp (void)
{
  _board = new Board ();
}

void test_board::tearDown (void)
{
  delete _board;
}

void test_board::test_switch_turn (void)
{
  CPPUNIT_ASSERT (get_black_turn ());
  _board->switch_turn ();  
  CPPUNIT_ASSERT (!get_black_turn ());
}


