#ifndef USER_HH
#define USER_HH

#include "player.hh"
#include "board.hh"

namespace reversi
{
  class user: public player
  {
  public:
    user();
    virtual ~user();
    virtual void ask_move(board b);
  };
}

#endif /* !defined(USER_HH) */
