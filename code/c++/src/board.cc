#include "board.hh"
#include <iostream>
#include <cmath>

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
  board::board () : _black_turn (DEFAULT_INIT_TURN), _board_size (DEFAULT_SIZE)
  {
    // Place the 4th initial discs.              
    place_disc (_board_size/2 + 1, _board_size/2);    // First black disc
    place_disc (_board_size/2, _board_size/2);        // First white disc
    place_disc (_board_size/2, _board_size/2 + 1);    // Second black disc
    place_disc (_board_size/2 + 1, _board_size/2 + 1);// Second white disc
  }

  board::~board () {}

  bool board::get_black_turn ()
  {
    return _black_turn;
  }

  void board::switch_turn ()
  {
    _black_turn = !_black_turn;
  }
  
  void board::place_disc (int x, int y)
  { 
    __int128 coordinates ((x - 1) * _board_size + (y - 1));       // Number of the bit we want to change in the bitboard.
    (_black_turn)? _black_bitboard |= (DISC << (__int128)coordinates) :     // Change the black bitboard if the var black is true.
      _white_bitboard |= (DISC << (__int128)coordinates);                   // Change the white bitboard if the var white is false.
    switch_turn ();
  }

  
  
  // Fonction a factoriser
  bool board::flip_discs (int coordinates, int dir)
  {
    int nb_discs_flipped = 0, nb_cases = pow(_board_size, 2);
    
    __int128 bitboard_losing_discs, bitboard_wining_discs;

    //We used a copy of the bitboards
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

    //Placement of the disc on the copy
     bitboard_wining_discs |= (DISC << coordinates);
     
    switch (dir) {
    case north :
      while (coordinates < (nb_cases - _board_size))// Test if the given direction is in the board
	{
	  coordinates += _board_size;
	  // Check if we flip at least one disc
	  if ((bitboard_wining_discs >> (coordinates) & 1ULL) == 1)
	    if (nb_discs_flipped == 0)
	      return false;
	    else
	      {
		//Move llegal so real bitboards become the copied. 
		if (_black_turn)
		  {
		    _white_bitboard = bitboard_losing_discs;
		    _black_bitboard = bitboard_wining_discs;
		  }
		else
		  {
		    _black_bitboard  = bitboard_losing_discs;
		    _white_bitboard = bitboard_wining_discs;
		  }
		return true;
	      }

	  // There isn't a white disc so we can't flip
	  if ((bitboard_losing_discs >> (coordinates) & 1ULL) == 0)
	    return false;

	  ++nb_discs_flipped;
	  bitboard_losing_discs &= ~(DISC << coordinates);// Remove the disc
	  bitboard_wining_discs |= (DISC << coordinates); // Add the disc  
	}
      return false;
      break;
      
    case south :
      while (coordinates > (_board_size - 1))// Test if the given direction is in the board
	{
	  coordinates -= _board_size;
	  // Check if we flip at least one disc
	  if ((bitboard_wining_discs >> (coordinates) & 1ULL) == 1)
	    if (nb_discs_flipped == 0)
	      return false;
	    else
	      {
		//Move llegal so real bitboards become the copied. 
		if (_black_turn)
		  {
		    _white_bitboard = bitboard_losing_discs;
		    _black_bitboard = bitboard_wining_discs;
		  }
		else
		  {
		    _black_bitboard  = bitboard_losing_discs;
		    _white_bitboard = bitboard_wining_discs;
		  }
		return true;
	      }

	  // There isn't a white disc so we can't flip
	  if ((bitboard_losing_discs >> (coordinates) & 1ULL) == 0)
	    return false;

	  ++nb_discs_flipped;
	  bitboard_losing_discs &= ~(DISC << coordinates);// Remove the disc
	  bitboard_wining_discs |= (DISC << coordinates); // Add the disc  
	}
      return false;
      break;
	
    case north_west :
      while ((coordinates % _board_size) != _board_size && coordinates > _board_size - 1)// Test if the given direction is in the board
	{
	  coordinates += _board_size + 1;
	  // Check if we flip at least one disc
	  if ((bitboard_wining_discs >> (coordinates) & 1ULL) == 1)
	    if (nb_discs_flipped == 0)
	      return false;
	    else
	      {
		//Move llegal so real bitboards become the copied. 
		if (_black_turn)
		  {
		    _white_bitboard = bitboard_losing_discs;
		    _black_bitboard = bitboard_wining_discs;
		  }
		else
		  {
		    _black_bitboard  = bitboard_losing_discs;
		    _white_bitboard = bitboard_wining_discs;
		  }
		return true;
	      }

	  // There isn't a white disc so we can't flip
	  if ((bitboard_losing_discs >> (coordinates) & 1ULL) == 0)
	    return false;

	  ++nb_discs_flipped;
	  bitboard_losing_discs &= ~(DISC << coordinates);// Remove the disc
	  bitboard_wining_discs |= (DISC << coordinates); // Add the disc  
	}
      return false;
      break;
	
    case north_east :
      while ((coordinates % _board_size) == _board_size - 1 && coordinates > _board_size - 1)// Test if the given direction is in the board
	{
	  coordinates += _board_size - 1;
	  // Check if we flip at least one disc
	  if ((bitboard_wining_discs >> (coordinates) & 1ULL) == 1)
	    if (nb_discs_flipped == 0)
	      return false;
	    else
	      {
		//Move llegal so real bitboards become the copied. 
		if (_black_turn)
		  {
		    _white_bitboard = bitboard_losing_discs;
		    _black_bitboard = bitboard_wining_discs;
		  }
		else
		  {
		    _black_bitboard  = bitboard_losing_discs;
		    _white_bitboard = bitboard_wining_discs;
		  }
		return true;
	      }

	  // There isn't a white disc so we can't flip
	  if ((bitboard_losing_discs >> (coordinates) & 1ULL) == 0)
	    return false;
	  
	  ++nb_discs_flipped;
	  bitboard_losing_discs &= ~(DISC << coordinates);// Remove the disc
	  bitboard_wining_discs |= (DISC << coordinates); // Add the disc  
	}
      return false;
      break;
	
    case south_west :
      while ((coordinates % _board_size) == _board_size && (coordinates < (nb_cases - _board_size)))// Test if the given direction is in the board
	{
	  coordinates -= _board_size - 1;
	  // Check if we flip at least one disc
	  if ((bitboard_wining_discs >> (coordinates) & 1ULL) == 1)
	    if (nb_discs_flipped == 0)
	      return false;
	    else
	      {
		//Move llegal so real bitboards become the copied. 
		if (_black_turn)
		  {
		    _white_bitboard = bitboard_losing_discs;
		    _black_bitboard = bitboard_wining_discs;
		  }
		else
		  {
		    _black_bitboard  = bitboard_losing_discs;
		    _white_bitboard = bitboard_wining_discs;
		  }
		return true;
	      }

	  // There isn't a white disc so we can't flip
	  if ((bitboard_losing_discs >> (coordinates) & 1ULL) == 0)
	    return false;

	  ++nb_discs_flipped;
	  bitboard_losing_discs &= ~(DISC << coordinates);// Remove the disc
	  bitboard_wining_discs |= (DISC << coordinates); // Add the disc  
	}
      return false;

      break;
    case south_east :
      while ((coordinates % _board_size) == _board_size - 1 && (coordinates < (nb_cases - _board_size)))// Test if the given direction is in the board
	{
	  coordinates -= _board_size + 1;
	  // Check if we flip at least one disc
	  if ((bitboard_wining_discs >> (coordinates) & 1ULL) == 1)
	    if (nb_discs_flipped == 0)
	      return false;
	    else
	      {
		//Move llegal so real bitboards become the copied. 
		if (_black_turn)
		  {
		    _white_bitboard = bitboard_losing_discs;
		    _black_bitboard = bitboard_wining_discs;
		  }
		else
		  {
		    _black_bitboard  = bitboard_losing_discs;
		    _white_bitboard = bitboard_wining_discs;
		  }
		return true;
	      }

	  // There isn't a white disc so we can't flip
	  if ((bitboard_losing_discs >> (coordinates) & 1ULL) == 0)
	    return false;

	  ++nb_discs_flipped;
	  bitboard_losing_discs &= ~(DISC << coordinates);// Remove the disc
	  bitboard_wining_discs |= (DISC << coordinates); // Add the disc  
	}
      return false;
	  
      break;
    case east :
      while ((coordinates % _board_size) != _board_size - 1)// Test if the given direction is in the board
	{
	  --coordinates;
	  // Check if we flip at least one disc
	  if ((bitboard_wining_discs >> (coordinates) & 1ULL) == 1)
	    if (nb_discs_flipped == 0)
	      return false;
	    else
	      {
		//Move llegal so real bitboards become the copied. 
		if (_black_turn)
		  {
		    _white_bitboard = bitboard_losing_discs;
		    _black_bitboard = bitboard_wining_discs;
		  }
		else
		  {
		    _black_bitboard  = bitboard_losing_discs;
		    _white_bitboard = bitboard_wining_discs;
		  }
		return true;
	      }

	  // There isn't a white disc so we can't flip
	  if ((bitboard_losing_discs >> (coordinates) & 1ULL) == 0)
	    return false;

	  ++nb_discs_flipped;
	  bitboard_losing_discs &= ~(DISC << coordinates);// Remove the disc
	  bitboard_wining_discs |= (DISC << coordinates); // Add the disc  
	}
      return false;  
      break;
      
    case west:
      while ((coordinates % _board_size) != _board_size)// Test if the given direction is in the board
	{
	  ++coordinates;
	  // Check if we flip at least one disc
	  if ((bitboard_wining_discs >> (coordinates) & 1ULL) == 1)
	    if (nb_discs_flipped == 0)
	      return false;
	    else
	      {
		//Move llegal so real bitboards become the copied. 
		if (_black_turn)
		  {
		    _white_bitboard = bitboard_losing_discs;
		    _black_bitboard = bitboard_wining_discs;
		  }
		else
		  {
		    _black_bitboard  = bitboard_losing_discs;
		    _white_bitboard = bitboard_wining_discs;
		  }
		return true;
	      }

	  // There isn't a white disc so we can't flip
	  if ((bitboard_losing_discs >> (coordinates) & 1ULL) == 0)
	    return false;

	  ++nb_discs_flipped;
	  bitboard_losing_discs &= ~(DISC << coordinates);// Remove the disc
	  bitboard_wining_discs |= (DISC << coordinates); // Add the disc  
	}
      return false;
      break;
    default :
      //lancer une exeption
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
    for (i = pow(_board_size, 2) - 1; i >= 0; i--)
      {
	if ((i % _board_size) == _board_size - 1)          // If we reach the end of the line (i multiple of _board_size)
	  {
	    cout << endl << line << " ";
	    line++;
	  }
	check = (_white_bitboard >> i) & 1ULL;           // Get the i-th bit of the white bitboard.
	if (check == EMPTY)                                // Check if there is not white disc.
	  {
	    check = (_black_bitboard >> i) & 1ULL;         // Get the i-th bit of the black bitboard.
	    (check == EMPTY)? cout << "_ " : cout << "X "; // Check if there is black disc or nothing.
	  }
	else                                               // There is a white disc.
	  cout << "O ";
      }
    cout << endl;
  }

  bool board::move (int x, int y)
  {
    int coordinates ((x - 1) * _board_size + (y - 1));
    bool flipped = false;
    for (int i = board::north; i != board::end_enum; i++)
      if (flip_discs (coordinates, i))
	flipped = true;
    return flipped;
  }

  int board::end_game ()
  {
    int nb_white_discs = 0, nb_black_discs = 0;
    int i;
    for (i = 0; i < pow(_board_size, 2); i++)
      {
	if ((_white_bitboard >> 1) & 1ULL == 1)
	  nb_white_discs ++;
	_white_bitboard >= 1;
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
}
