#include "board.hh"
#include <iostream>

using namespace reversi;

int main()
{
  board* brd = new board ();
  brd->display ();
  int coordinates ((3 - 1) * 8 + (4 - 1));
  for (int i = board::north; i != board::end_enum; i++)
     brd->flip_discs (coordinates, i);
  brd->display ();
  return 0;
}
