#ifndef BOARD_HH
#define BOARD_HH

#include <iostream>

namespace reversi
{
  class board
  {
  public:
    
    board (/*int size*/); /* ==== PROTOTYPE ==== */ // size will be a parameter in final version
    ~board ();

    typedef __int128 bitboard;
    
    //Whereas black win the game at the end or if he lose eg white wins, or if there is a tie. 
    enum Winner {black, white, tie};

    // The 8 directions to look for flip discs when we do a llegal move
    enum Direction {north, north_east, east, south_east, south, south_west, west, north_west, end_enum};
    
  /* ==== PROTOTYPE
    /**
     * Display in the terminal the board.
     * Bitboards are supposed to be correct here.
     */
    const void display ();

    /**
     * Flip discs in the indicate dir.
     * If no discs where flipped, return false.
     */
    bool flip_discs (int coordinates, int dir);

    /**
     * Do the move if it's legal, update the _mobility_bitboard, and swithc the current player.
     * Otherwise, throw an exception.
     */
    void move (int x, int y);

    /**
     * Check if the current player can move.
     * Return true if he can move.
     * Otherwise return false.
     */
    const bool can_move ();
    
    /**
     * Used to know the winner of the game.
     * Return black if black won, white if white won and tie if there is a tie.
     */
    const int end_game_state ();

    const bool is_game_over ();
    
    /**
     * Do the calculation of the mobility bitboard for the current_player.
     */
    const void mobility_calculation (const bitboard & current_bitboard, const bitboard & opponent_bitboard);

    /*
     * Return the _mobility_bitboard.
     */
    const bitboard get_mobility_bitboard ();
    
    /**
     * TODO : DOC
     * wrapper for serialization in an output stream.
     */
    void serialize(std::ostream&) const;
    
  private: 
    // Size of the board (between 2 & 10).
    int _board_size, _nb_cases;
    bool _black_turn; // False means the white must play.
    
    // One bitboard for each player (black & white) the game is initialized with the classic four discs in the center.
    bitboard _black_bitboard, _white_bitboard, _mobility_bitboard;

    // Switch the current player.
    void switch_turn ();

    /**
     * Place a disc in the bitboard with this coordinates. 
     * / ! \ coordinates are supposed to be verrified by the player, just used by the constructor
     */
    void place_disc (int x, int y);

    /**
     * Check if the move is legal.
     * Return 1 if the move is legal, and modify the bitboard.
     * Return -1 if the move isn't legal.
     * Return 0 if we don't already know.
     */
    int check_legal_move (const bitboard & current_bitboard, const bitboard & opponent_bitboard, int coordinate, bool disc_flipped);

    /**
     * Display rules of the games.
     */
    const void display_rules ();
  };

  /**
   * TODO : DOC
   * operator overload for board's serialization.
   */
  std::ostream & operator<<(std::ostream&, const board&);

  /**
   * TODO : DOC
   * wrapper to save the board in a file.
   * @param 
   * @param 
   */
  void save_at(const std::string&, const board&);
}

#endif /* !defined(BOARD_HH) */
