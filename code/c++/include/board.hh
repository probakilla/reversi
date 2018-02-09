#ifndef BOARD_HH
#define BOARD_HH

namespace reversi
{
  class board
  {
  public:
    
    board (/*int size*/); /* ==== PROTOTYPE ==== */ // size will be a parameter in final version
    virtual ~board ();

    //Whereas black win the game at the end or if he lose eg white wins, or if there is a tie. 
    enum Black_End_State {black_win, black_lose, tie};

    // The 8 directions to look for flip discs when we do a llegal move
    enum Direction {north, north_east, east, south_east, south, south_west, west, north_west, end_enum};
    
  /* ==== PROTOTYPE
    /**
     * Display in the terminal the board.
     * Bitboards are supposed to be correct here.
     */
    void display ();

    /**
     * Flip discs in the indicate dir.
     * If no discs where flipped, return false.
     */
    bool flip_discs (int coordinates, int dir);

    /**
     * If the move is legal, place, flip discs and return true.
     * Otherwise, do nothing and return false.
     */
    bool move (int x, int y);
    
    /**
     * Used to know the winner of the game.
     * Return 1 if black won, 0 if white won and -1 if there is a tie.
    */
    int end_game ();
    
  private: 
    // Size of the board (between 2 & 10).
    int _board_size;
    bool _black_turn; // False means the white must play.
    
    // One bitboard for each player (black & white) the game is initialized with the classic four discs in the center.
    __int128 _black_bitboard, _white_bitboard;

    // Switch the current player
    void switch_turn ();

        /**
     * Place a disc in the bitboard with this coordinates. 
     * / ! \ coordinates are supposed to be verrified by the player, just used by the constructor
     */
    void place_disc (int x, int y);
  };
}

#endif /* !defined(BOARD_HH) */
