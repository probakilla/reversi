#include "board.hh"
#include <iostream>
#include <cmath>
#include <bitset>

const int DEFAULT_SIZE = 8;
const __int128 DISC = 1;
const int NB_PLAYER = 2;
const int EMPTY = 0;
const bool DEFAULT_INIT_TURN = true;
const bool BLACK_TURN = true;
const bool WHITE_TURN = false;

namespace reversi
{
  using namespace std;
  
  /* ==== PROTOTYPE ==== */
  // initialization is temporary
  board::board () : _black_turn (DEFAULT_INIT_TURN), _board_size (DEFAULT_SIZE), _nb_cases (pow(_board_size, 2))
  {
    display_rules ();
    _black_bitboard = _white_bitboard = 0;
    // Place the 4th initial discs.              
    place_disc (_board_size/2 + 1, _board_size/2);    // First black disc
    place_disc (_board_size/2, _board_size/2);        // First white disc
    place_disc (_board_size/2, _board_size/2 + 1);    // Second black disc
    place_disc (_board_size/2 + 1, _board_size/2 + 1);// Second white disc
    _mobility_bitboard = get_mobility (_black_bitboard, _white_bitboard);
  }

  board::~board () {}

  void board::display_rules ()
  {
    cout << "Bienvenue dans le jeu de reversi\n" << endl;
  }

  void board::switch_turn ()
  {
    _black_turn = !_black_turn;
  }
  
  void board::place_disc (int x, int y)
  { 
    __int128 coordinates ((x - 1) * _board_size + (y - 1));                 // Number of the bit we want to change in the bitboard.
    (_black_turn)? _black_bitboard |= (DISC << (coordinates)) :     // Change the black bitboard if the var black is true.
      _white_bitboard |= (DISC << (coordinates));                   // Change the white bitboard if the var white is false.
    switch_turn ();
  }

  int board::check_legal_move (bitboard current_bitboard, bitboard opponent_bitboard, int coordinates, bool disc_flipped)
  {
    if ((current_bitboard >> (coordinates) & 1ULL) == 1)
      // There is a disc of the same player next to the placed_discs so the move is illegal    
      if (disc_flipped == 0)
	return -1;
    
      else
	{
	  // Move llegal so real bitboards become the copied. 
	  if (_black_turn)
	    {
	      _white_bitboard = opponent_bitboard;
	      _black_bitboard = current_bitboard;
	    }
	  else
	    {
	      _black_bitboard  = opponent_bitboard;
	      _white_bitboard = current_bitboard;
	    }
	  return 1;
	}

    // There isn't a disc so we can't flip
    if ((opponent_bitboard >> (coordinates) & 1ULL) == 0)
      return -1;
    
    return 0;//We don't know if the move is legal

  }

  
  bool board::flip_discs (int coordinates, int dir)
  {
    bool disc_flipped = false;
    bitboard bitboard_losing_discs, bitboard_wining_discs;

    // We save the bitboard to use a copy of them
    if (_black_turn)
      {
	bitboard_losing_discs = _white_bitboard;
	bitboard_wining_discs = _black_bitboard;
      }
    else
      {
	bitboard_losing_discs = _black_bitboard;
	bitboard_wining_discs = _white_bitboard;
      }

    // Placement of the disc on the copy
     bitboard_wining_discs |= (DISC << coordinates);
     
    switch (dir) {
    case north :
      while (coordinates < (_nb_cases - _board_size))// Test if the given direction is in the board
	{	  
	  coordinates -= _board_size;// Coordinates at the north of the disc

	  if (check_legal_move (bitboard_wining_discs, bitboard_losing_discs, coordinates, disc_flipped) == -1)
	    return false;
	  if (check_legal_move (bitboard_wining_discs, bitboard_losing_discs, coordinates, disc_flipped) == 1)
	    return true;
	  
	  disc_flipped = true;                            // At least one disc is flipped
	  bitboard_losing_discs &= ~(DISC << coordinates);// Remove the disc
	  bitboard_wining_discs |= (DISC << coordinates); // Add the disc  
	}
      return false;
      break;
      
    case south :
      while (coordinates > (_board_size - 1))// Test if the given direction is in the board
	{
	  coordinates += _board_size;// Coordinates at the south of the disc

	  if (check_legal_move (bitboard_wining_discs, bitboard_losing_discs, coordinates, disc_flipped) == -1)
	    return false;
	  if (check_legal_move (bitboard_wining_discs, bitboard_losing_discs, coordinates, disc_flipped) == 1)
	    return true;
	  
	  disc_flipped = true;                            // At least one disc is flipped
	  bitboard_losing_discs &= ~(DISC << coordinates);// Remove the disc
	  bitboard_wining_discs |= (DISC << coordinates); // Add the disc  
	}
      return false;
      break;
	
    case north_west :
      while ((coordinates % _board_size) != _board_size && coordinates > _board_size - 1)// Test if the given direction is in the board
	{
	  // Coordinates at the north-west of the disc
	  coordinates -= _board_size - 1;
	  
	  if (check_legal_move (bitboard_wining_discs, bitboard_losing_discs, coordinates, disc_flipped) == -1)
	    return false;
	  if (check_legal_move (bitboard_wining_discs, bitboard_losing_discs, coordinates, disc_flipped) == 1)
	    return true;
	  
	  disc_flipped = true;                            // At least one disc is flipped
	  bitboard_losing_discs &= ~(DISC << coordinates);// Remove the disc
	  bitboard_wining_discs |= (DISC << coordinates); // Add the disc  
	}
      return false;
      break;
	
    case north_east :
      while ((coordinates % _board_size) == _board_size - 1 && coordinates > _board_size - 1)// Test if the given direction is in the board
	{
	  coordinates -= _board_size + 1;// Coordinates at the north-east of the disc

	  if (check_legal_move (bitboard_wining_discs, bitboard_losing_discs, coordinates, disc_flipped) == -1)
	    return false;
	  if (check_legal_move (bitboard_wining_discs, bitboard_losing_discs, coordinates, disc_flipped) == 1)
	    return true;
	  
	  disc_flipped = true;                            // At least one disc is flipped
	  bitboard_losing_discs &= ~(DISC << coordinates);// Remove the disc
	  bitboard_wining_discs |= (DISC << coordinates); // Add the disc  
	}
      return false;
      break;
	
    case south_west :
      while ((coordinates % _board_size) == _board_size && (coordinates < (_nb_cases - _board_size)))// Test if the given direction is in the board
	{
	  coordinates = _board_size + 1;// Coordinates at the south_west of the disc

	  if (check_legal_move (bitboard_wining_discs, bitboard_losing_discs, coordinates, disc_flipped) == -1)
	    return false;
	  if (check_legal_move (bitboard_wining_discs, bitboard_losing_discs, coordinates, disc_flipped) == 1)
	    return true;
	  
	  disc_flipped = true;                            // At least one disc is flipped
	  bitboard_losing_discs &= ~(DISC << coordinates);// Remove the disc
	  bitboard_wining_discs |= (DISC << coordinates); // Add the disc  
	}
      return false;

      break;
    case south_east :
      while ((coordinates % _board_size) == _board_size - 1 && (coordinates < (_nb_cases - _board_size)))// Test if the given direction is in the board
	{
	  coordinates = _board_size - 1;// Coordinates at the south_east of the disc

	  if (check_legal_move (bitboard_wining_discs, bitboard_losing_discs, coordinates, disc_flipped) == -1)
	    return false;
	  if (check_legal_move (bitboard_wining_discs, bitboard_losing_discs, coordinates, disc_flipped) == 1)
	    return true;
	  
	  disc_flipped = true;                            // At least one disc is flipped
	  bitboard_losing_discs &= ~(DISC << coordinates);// Remove the disc
	  bitboard_wining_discs |= (DISC << coordinates); // Add the disc  
	}
      return false;
	  
      break;
    case east :
      while ((coordinates % _board_size) != _board_size - 1)// Test if the given direction is in the board
	{
	  ++coordinates;// Coordinates at the east of the disc

	  if (check_legal_move (bitboard_wining_discs, bitboard_losing_discs, coordinates, disc_flipped) == -1)
	    return false;
	  if (check_legal_move (bitboard_wining_discs, bitboard_losing_discs, coordinates, disc_flipped) == 1)
	    return true;
	  
	  disc_flipped = true;
	  bitboard_losing_discs &= ~(DISC << coordinates);// Remove the disc
	  bitboard_wining_discs |= (DISC << coordinates); // Add the disc  
	}
      return false;  
      break;
      
    case west:
      while ((coordinates % _board_size) != _board_size)// Test if the given direction is in the board
	{
	  --coordinates;// Coordinates at the west of the disc
	  
	  if (check_legal_move (bitboard_wining_discs, bitboard_losing_discs, coordinates, disc_flipped) == -1)
	    return false;
	  if (check_legal_move (bitboard_wining_discs, bitboard_losing_discs, coordinates, disc_flipped) == 1)
	    return true;
	  
	  disc_flipped = true;                            // At least one disc is flipped
	  bitboard_losing_discs &= ~(DISC << coordinates);// Remove the disc
	  bitboard_wining_discs |= (DISC << coordinates); // Add the disc  
	}
      return false;
      break;
    default :
      throw string ("ERREUR : Direction invalide\n");// Invalid direction
      break;
    }  
  }
  
  void board::display ()
  {
    char collumn ('A');
    int i, check, line;
    line = 1;
    cout << "  ";                                          // Shifting for the display of letters.
    for (i = 0; i < _board_size; i++)                      // Display of letters
      cout << collumn++ << " ";
    for (i = _nb_cases - 1; i >= 0; i--)
      {
	if ((i % _board_size) == _board_size - 1)          // If we reach the end of the line (i multiple of _board_size)
	  {
	    cout << endl << line << " ";
	    line++;
	  }
	check = (_white_bitboard >> i) & 1ULL;             // Get the i-th bit of the white bitboard.
	if (check == EMPTY)                                // Check if there is not white disc.
	  {
	    check = (_black_bitboard >> i) & 1ULL;         // Get the i-th bit of the black bitboard.
	    if (check == EMPTY)
	      {
		check = (_mobility_bitboard >> i) & 1ULL;    // Get the i-th bit of the black bitboard.
		(check == EMPTY)? cout << "_ " : cout << "* "; // Check if there is black disc or nothing.
	      }
	    else
	      cout << "X ";
	  }
	else                                               // There is a white disc.
	  cout << "O ";
      }
    cout << endl;
  }

  void board::move (int x, int y)
  {
    int coordinates ((x - 1) * _board_size + (y - 1));
    bool flipped = false;
    for (int i = board::north; i != board::end_enum; i++)
      if (flip_discs (coordinates, i))
	  flipped = true;
    if (!flipped)
        throw string ("ERREUR : coup invalide");
    _mobility_bitboard = get_mobility (_white_bitboard, _black_bitboard);
    switch_turn ();
  }

  int board::end_game ()
  {
    int nb_white_discs = 0, nb_black_discs = 0;
    int i;
    for (i = 0; i < _nb_cases; i++)
      {
	// Count the number of white discs
	if ((_white_bitboard >> 1) & 1ULL == 1)
	  nb_white_discs ++;
	_white_bitboard >= 1;

	// Count the number of black discs
	if ((_black_bitboard >> 1) & 1ULL == 1)
	  nb_black_discs ++;
	_black_bitboard >= 1;
      }
    
    if (nb_black_discs > nb_white_discs)
      return black_win;
    if (nb_black_discs < nb_white_discs)
      return black_lose;
    return tie;
  }

  __int128 board::get_mobility (bitboard current_bitboard, bitboard opponent_bitboard)
  {
    bitboard empty = ~(opponent_bitboard | current_bitboard);// Bitboard of empty cell
    bitboard candidates,  moves = 0;
    bool negative_shift;// True if shift must be negative
    __int128 shift;

    for (int i = north; i != end_enum; i++)
      {
	switch (i)
	  {	 
	  case north :
	    negative_shift = true;
	    shift = _board_size;
	    break;
	    
	  case south :
	    shift = _board_size;
	    negative_shift = false;
	    break;
	    
	  case east :
	    negative_shift = true;
	    shift = 1;
	    break;
	    
	  case west :
	    negative_shift = false;	    
	    shift = 1;
	    break;
	    
	  case north_west :
	    negative_shift = true;
	    shift = _board_size + 1;
	    break;
	    
	  case north_east :
	    negative_shift = true;
	    shift = _board_size - 1;
	    break;
	    
	  case south_west :
	    negative_shift = false;
	    shift = _board_size - 1;
	    break;
	    
	  case south_east :
	    negative_shift = false;
	    shift = _board_size + 1;
	    break;
	    
	  default :
	    throw string ("ERREUR : Direction invalide\n");// Invalid direction
	    break;
	  }
	
	//Because left shift with negative value doesn't work when expected
	if (negative_shift)
	  candidates = opponent_bitboard & (current_bitboard << shift);
	
	else
	  candidates = opponent_bitboard & (current_bitboard >> shift);

	while (candidates != 0)
	  {
	    //Because left shift with negative value doesn't work when expected	    
	    if (negative_shift)
	      {
		moves |= empty & (candidates << shift);
		candidates = opponent_bitboard & (candidates << shift);
	      }
	    else
	      {
		moves |= empty & (candidates >> shift);
		candidates = opponent_bitboard & (candidates >> shift);
	      }
	  }
      }

    return moves;
  }
}
