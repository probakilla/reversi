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

  void board::place_disc (int x, int y)
  { 
    __int128 coordinates ((x - 1) * _board_size + (y - 1));       // Number of the bit we want to change in the bitboard.
    (_black_turn)? _black_bitboard |= (DISC << coordinates) :     // Change the black bitboard if the var black is true.
      _white_bitboard |= (DISC << coordinates);                   // Change the white bitboard if the var white is false.
    _black_turn = !_black_turn;                                   // Switch turn  
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

  int board::end_game ()
  {
  }
  
}
