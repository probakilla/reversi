#ifndef RANDOM_IA_HH
#define RANDOM_IA_HH

#include "player.hh"
#include "board.hh"

namespace reversi
{
  class random_ia: public player
  {
  public:
    random_ia();
    virtual ~random_ia();
    virtual void ask_move(board & b);
  };
}

#endif /* !defined(RANDOM_IA_HH) */
