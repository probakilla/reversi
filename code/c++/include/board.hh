#ifndef BOARD_HH
#define BOARD_HH

namespace reversi
{
  class board
  {
  public:
    
    board (/*int size*/); /* ==== PROTOTYPE ==== */ // size will be a parameter in final version
    virtual ~board ();

    /**
     * Display in the terminal the board.
     * Bitboards are supposed to be correct here.
     */
    void display ();

    /**
     * Place a disc in the bitboard with this coordinates.
     * If the var black is true, the bitboard used is the bitboard of
     * the black player, otherwise the white one. 
     * / ! \ coordinates are supposed to be verrified by the player, eg by a method 'play move' / ! \
     * (maybe just for now)
     */
    void place_disc (int x, int y, bool black);
    
  private: 
    // Size of the board (between 2 & 10).
    int _board_size;
    bool _black_turn; // False means the white must play.
    
    // One bitboard for each player (black & white) the game is initialized with the classic four discs in the center.
    __int128 _black_bitboard, _white_bitboard;
  };
}

#endif /* !defined(BOARD_HH) */
