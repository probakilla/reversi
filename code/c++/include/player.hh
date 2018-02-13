#ifndef PLAYER_HH
#define PLAYER_HH

#include "board.hh"

namespace reversi
{
  class player
  {
  public:
    player();
    virtual ~player();
    virtual void ask_move(board & b) = 0;
  };
}

#endif /* !defined(PLAYER_HH) */
