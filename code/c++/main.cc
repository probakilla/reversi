#include "board.hh"
#include <iostream>

using namespace reversi;

int main()
{
  board* brd = new board ();
  brd->display ();
  brd->move (3, 4);
  brd->display ();
  return 0;
}
