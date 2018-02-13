#include "board.hh"
#include "player.hh"
#include "user.hh"
#include <iostream>

using namespace reversi;

int main()
{
  board brd;
  user usr;
  while (1) {
    brd.display ();
    usr.ask_move(brd);
  }
  return 0;
}
