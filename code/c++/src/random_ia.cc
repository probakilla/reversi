#include "player.hh"
#include "random_ia.hh"
#include "board.hh"
#include <stdlib.h>

namespace reversi
{
  using namespace std;
  
  random_ia::random_ia () {}
  
  random_ia::~random_ia () {}
  
  void random_ia::ask_move (board &b)
  {
    int x, y;
    while (1) {
      x = rand() % 8 + 1;
      y = rand() % 8 + 1;
      try {
	b.move (x, y);
	break;
      }
      catch (exception &e) {}
    }
  }
}
