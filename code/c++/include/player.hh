#ifndef PLAYER_HH
#define PLAYER_HH

namespace reversi
{
  class player
  {
  public:
    player();
    virtual ~player();

    void ask_move ();
  };
}

#endif /* !defined(PLAYER_HH) */
