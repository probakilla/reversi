#include "board.hh"
#include "player.hh"
#include <iostream>

using namespace reversi;

int main()
{
  board* brd = new board ();
  brd->display ();
  return 0;
}
