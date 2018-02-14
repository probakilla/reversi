#ifndef BOARD_HH
#define BOARD_HH

#include <iostream>

namespace reversi
{
  class board
  {
  public:
    /* ==== PROTOTYPE ==== size will be a parameter in the final version. */
    board (/* int size */);
    ~board ();
    
    typedef __int128 bitboard;
    
    /* Whereas black wins the game at the end, or he loses (eg. white wins),
       or there is a tie. */
    enum Winner {black, white, tie};
    
    /* The eight directions to look for flip discs when a legal move is done. */
    enum Direction {north, north_east, east, south_east,
		    south, south_west, west, north_west,
		    end_enum};
    
    /* ==== PROTOTYPE ====
     * Displays the board in the terminal.
     * Bitboards are supposed to be correct here.
     */
    const void display ();
    
    /**
     * Flips discs in the indicate direction.
     * If no disc was flipped, return false.
     */
    bool flip_discs (int coordinates, int dir);
    
    /**
     * Does the move if it is a legal one, updates the mobility bitboard,
     and switches the current player.
     * Otherwise, throw an exception.
     */
    void move (int x, int y);
    
    /**
     * Checks if the current player can move.
     * Returns true if he can move.
     * Otherwise return false.
     */
    const bool can_move ();
    
    /**
     * Used to know the winner of the game.
     * Returns black if black won, white if white won and tie if there is a tie.
     */
    const int end_game_state ();
    
    const bool is_game_over ();
    
    /**
     * Does the calculation of the mobility bitboard for the current player.
     */
    void mobility_calculation (const bitboard &current_bitboard,
			       const bitboard &opponent_bitboard);
    
    /*
     * Returns the mobility bitboard.
     */
    const bitboard get_mobility_bitboard ();
    
    /**
     * TODO : DOC
     * Wrapper for serialization in an output stream.
     */
    void serialize (std::ostream &) const;
    
  private: 
    /* Size of the board (between 2 and 10). */
    int _board_size, _nb_cases;
    /* False means the white must play. */
    bool _black_turn;
    
    /* One bitboard for each player (black and white),
       the game is initialized with the classic four discs in the center. */
    bitboard _black_bitboard, _white_bitboard, _mobility_bitboard;
    
    /* Switches the current player. */
    void switch_turn ();
    
    /**
     * Places a disc in the bitboard with this coordinates.
     * / ! \ Coordinates are supposed to be verified by the player,
     just used by the constructor.
    */
    void place_disc (int x, int y);
    
    /**
     * Checks if the move is legal.
     * Returns 1 if the move is legal, and modifies the bitboard.
     * Returns -1 if the move isn't legal.
     * Returns 0 if there are no clue.
     */
    int check_legal_move (const bitboard &current_bitboard,
			  const bitboard &opponent_bitboard,
			  int coordinate, bool disc_flipped);
    
    /**
     * Displays the rules of the game.
     */
    const void display_rules ();
  };
  
  /**
   * TODO : DOC
   * Operator overload for board's serialization.
   */
  std::ostream & operator<< (std::ostream &, const board &);
  
  /**
   * TODO : DOC
   * Wrapper to save the board in a file.
   * @param 
   * @param 
   */
  void save_at (const std::string &, const board &);
}

#endif /* !defined(BOARD_HH) */
