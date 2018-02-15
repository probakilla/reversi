#include "board.hh"
#include <exception>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>

#define BLANK_C "_ "
#define BLACK_C "X "
#define WHITE_C "O "
#define POSSIBLE_MOVE_C "* "
#define SEP_C " "

using namespace std;

class illegal_move : public exception
{
  virtual const char *what () const throw ()
  {
    return "Coup illégal !\n";
  }
} illegal_move;

const int DEFAULT_SIZE = 8;
const int NB_PLAYER = 2;
const __int128 DISC = 1;
const int EMPTY = 0;
const bool DEFAULT_INIT_TURN = true;
const bool BLACK_TURN = true;
const bool WHITE_TURN = false;

namespace reversi
{
  /* ==== PROTOTYPE ==== Initialization is temporary. */
  board::board () :  _board_size (DEFAULT_SIZE),
		     _nb_cases (pow (_board_size, 2)),
		     _black_turn (DEFAULT_INIT_TURN)
  {
    /* Because there is one bit for the end of a row. */
    ++_board_size;
    _black_bitboard = _white_bitboard = 0;
    /* Places the four initial discs. */
    /* First black disc. */
    place_disc (_board_size / 2, _board_size / 2 + 1);
    /* First white disc. */
    place_disc (_board_size / 2, _board_size / 2);
    /* Second black disc. */
    place_disc (_board_size / 2 + 1, _board_size / 2);
    /* Second white disc. */
    place_disc (_board_size / 2 + 1, _board_size / 2 + 1);
    mobility_calculation (_black_bitboard, _white_bitboard);
  }
  
  board::~board () {}
  
  /* Prototype d'affichage des rêgles. */
  void board::display_rules ()
  {
    cout << "Bienvenue dans le jeu de reversi.\n";
    cout << "Le but du jeu est d'avoir plus de pions que son adversaire ";
    cout << "dici la fin de la partie, qui se produit lorsque plus aucun ";
    cout << "joueur ne peut jouer.\n";
    cout << "Vous ne pouvez placer un pion que sur les cases représentées ";
    cout << "par une *.\n";
    cout << "Une fois placé, le pion capture les pions adverses se trouvant ";
    cout << "entre le pion posé et un autre de vos pions (et ceci à ";
    cout << "l'horizontale, comme à la vertivale ou la diagonale).\n\n";
  }
  
  void board::switch_turn ()
  {
    _black_turn = !_black_turn;
  }
  
  void board::place_disc (int x, int y)
  {
    /* Number of the bit we want to change in the bitboard. */
    __int128 coordinates ((x) + (_board_size) * (y - 1));
    /**
     * Change the black bitboard if the var black is true.
     * Change the black bitboard if the var black is true.
     * Change the white bitboard if the var white is false.
     */
    (_black_turn) ? _black_bitboard |= (DISC << (coordinates)) :
      _white_bitboard |= (DISC << (coordinates));
    switch_turn ();
  }
  
  int board::check_legal_move (const bitboard &current_bitboard,
			       const bitboard &opponent_bitboard,
			       int coordinates, bool disc_flipped)
  {
    if ((current_bitboard >> (coordinates) & 1ULL) == 1)
      {
	/* There is a disc of the same player next to the placed discs
	   so the move is illegal */
	if (!disc_flipped)
	  return -1;
    
	else
	  {
	    /* Move is legal so real bitboards become the copied. */
	    if (_black_turn)
	      {
		_white_bitboard = opponent_bitboard;
		_black_bitboard = current_bitboard;
	      }
	    else
	      {
		_black_bitboard = opponent_bitboard;
		_white_bitboard = current_bitboard;
	      }
	    return 1;
	  }
      }
    /* There is not a disc so we can not flip. */
    if ((opponent_bitboard >> (coordinates) & 1ULL) == 0)
      return -1;
    
    /* We do not know if the move is legal. */
    return 0;
  }
  
  bool board::flip_discs (int coordinates, int dir)
  {
    bool disc_flipped = false;
    bitboard bitboard_losing_discs, bitboard_wining_discs;
    
    /* We save the bitboards to use copies of them. */
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
    
    /* Placement of the disc on the copy. */
    bitboard_wining_discs |= (DISC << coordinates);
    switch (dir)
      {
      case north :
	/* Tests if the given direction is in the board. */
	while ((coordinates % _board_size) != 0 &&
	       coordinates > (_board_size - 1))
	  {
	    /* Coordinates at the north of the disc. */
	    coordinates -= _board_size;

	    if (check_legal_move (bitboard_wining_discs, bitboard_losing_discs,
				  coordinates, disc_flipped) == -1)
	      return false;
	    if (check_legal_move (bitboard_wining_discs, bitboard_losing_discs,
				  coordinates, disc_flipped) == 1)
	      return true;
	    /* At least one disc is flipped. */
	    disc_flipped = true;
	    /* Removes the disc. */
	    bitboard_losing_discs &= ~(DISC << coordinates);
	    /* Adds the disc. */
	    bitboard_wining_discs |= (DISC << coordinates);
	  }
	return false;
	break;
        
      case north_east :
	/* Tests if the given direction is in the board. */
	while ((coordinates % _board_size) != 0 &&
	       (coordinates % _board_size) != (_board_size - 1) &&
	       coordinates > (_board_size - 1))
	  {
	    /* Coordinates at the north-east of the disc. */
	    coordinates -= _board_size - 1;
	    
	    if (check_legal_move (bitboard_wining_discs, bitboard_losing_discs,
				  coordinates, disc_flipped) == -1)
	      return false;
	    if (check_legal_move (bitboard_wining_discs, bitboard_losing_discs,
				  coordinates, disc_flipped) == 1)
	      return true;

	    /* At least one disc is flipped. */
	    disc_flipped = true;
	    /* Removes the disc. */
	    bitboard_losing_discs &= ~(DISC << coordinates);
	    /* Adds the disc. */
	    bitboard_wining_discs |= (DISC << coordinates);
	  }
	return false;
	break;
        
      case east :
	/* Tests if the given direction is in the board. */
	while ((coordinates % _board_size) != 0 &&
	       (coordinates % _board_size) != (_board_size - 1))
	  {
	    /* Coordinates at the east of the disc. */
	    ++coordinates;
	    
	    if (check_legal_move (bitboard_wining_discs, bitboard_losing_discs,
				  coordinates, disc_flipped) == -1)
	      return false;
	    if (check_legal_move (bitboard_wining_discs, bitboard_losing_discs,
				  coordinates, disc_flipped) == 1)
	      return true;

	    /* At least one disc is flipped. */
	    disc_flipped = true;
	    /* Removes the disc. */
	    bitboard_losing_discs &= ~(DISC << coordinates);
	    /* Adds the disc. */
	    bitboard_wining_discs |= (DISC << coordinates); 
	  }
	return false;
	break;
        
      case south_east :
	/* Tests if the given direction is in the board. */
	while ((coordinates % _board_size) != 0 &&
	       (coordinates % _board_size) != (_board_size - 1) &&
	       coordinates < (_nb_cases - _board_size))
	  {
	    /* Coordinates at the south_east of the disc. */
	    coordinates += _board_size + 1;
	    
	    if (check_legal_move (bitboard_wining_discs, bitboard_losing_discs,
				  coordinates, disc_flipped) == -1)
	      return false;
	    if (check_legal_move (bitboard_wining_discs, bitboard_losing_discs,
				  coordinates, disc_flipped) == 1)
	      return true;
	    
	    /* At least one disc is flipped. */
	    disc_flipped = true;
	    /* Removes the disc. */
	    bitboard_losing_discs &= ~(DISC << coordinates);
	    /* Adds the disc. */
	    bitboard_wining_discs |= (DISC << coordinates);
	  }
	return false;	  
	break;
        
      case south :
	/* Tests if the given direction is in the board. */
	while ((coordinates % _board_size) != 0 &&
	       coordinates < (_nb_cases - _board_size))
	  {
	    /* Coordinates at the south of the disc. */
	    coordinates += _board_size;
	    
	    if (check_legal_move (bitboard_wining_discs, bitboard_losing_discs,
				  coordinates, disc_flipped) == -1)
	      return false;
	    if (check_legal_move (bitboard_wining_discs, bitboard_losing_discs,
				  coordinates, disc_flipped) == 1)
	      return true;

	    /* At least one disc is flipped. */
	    disc_flipped = true;
	    /* Removes the disc. */
	    bitboard_losing_discs &= ~(DISC << coordinates);
	    /* Adds the disc. */
	    bitboard_wining_discs |= (DISC << coordinates); 
	  }
	return false;
	break;
        
      case south_west :
	/* Tests if the given direction is in the board. */
	while ((coordinates % _board_size) != 0 &&
	       (coordinates % _board_size) != 1 &&
	       coordinates < (_nb_cases - _board_size))
	  {
	    /* Coordinates at the south_west of the disc. */
	    coordinates += _board_size - 1;
	    
	    if (check_legal_move (bitboard_wining_discs, bitboard_losing_discs,
				  coordinates, disc_flipped) == -1)
	      return false;
	    if (check_legal_move (bitboard_wining_discs, bitboard_losing_discs,
				  coordinates, disc_flipped) == 1)
	      return true;

	    /* At least one disc is flipped. */
	    disc_flipped = true;
	    /* Removes the disc. */
	    bitboard_losing_discs &= ~(DISC << coordinates);
	    /* Adds the disc. */
	    bitboard_wining_discs |= (DISC << coordinates); 
	  }
	return false;
	break;
        
      case west:
	/* Tests if the given direction is in the board. */
	while ((coordinates % _board_size) != 0 &&
	       (coordinates % _board_size) != 1)
	  {
	    /* Coordinates at the west of the disc. */
	    --coordinates;
	  
	    if (check_legal_move (bitboard_wining_discs, bitboard_losing_discs,
				  coordinates, disc_flipped) == -1)
	      return false;
	    if (check_legal_move (bitboard_wining_discs, bitboard_losing_discs,
				  coordinates, disc_flipped) == 1)
	      return true;

	    /* At least one disc is flipped. */
	    disc_flipped = true;
	    /* Removes the disc. */
	    bitboard_losing_discs &= ~(DISC << coordinates);
	    /* Adds the disc. */
	    bitboard_wining_discs |= (DISC << coordinates);
	  }
	return false;
	break;
        
      case north_west :
	/* Tests if the given direction is in the board. */
	while ((coordinates % _board_size) != 0 &&
	       (coordinates % _board_size) != 1 &&
	       coordinates > (_board_size - 1))
	  {
	    /* Coordinates at the north-west of the disc. */
	    coordinates -= _board_size + 1;
	    
	    if (check_legal_move (bitboard_wining_discs, bitboard_losing_discs,
				  coordinates, disc_flipped) == -1)
	      return false;
	    if (check_legal_move (bitboard_wining_discs, bitboard_losing_discs,
				  coordinates, disc_flipped) == 1)
	      return true;
	    
	    /* At least one disc is flipped. */
	    disc_flipped = true;
	    /* Removes the disc. */
	    bitboard_losing_discs &= ~(DISC << coordinates);
	    /* Adds the disc. */
	    bitboard_wining_discs |= (DISC << coordinates);
	  }
	return false;
      }
    return false;
  }
  
  void board::display ()
  {
    char collumn ('A');
    int i, j = 0, check, line = 1;
    /* Shifting for the display of letters. */
    cout << "  ";
    /* Display of letters. */
    for (i = 1; i < _board_size; i++)
      cout << collumn++ << SEP_C;
    for (i = 1; i < (_nb_cases + _board_size); i++)
      {
	j++;
	/* To not count the bit for the end of a row. */
	if ((i % _board_size) != 0)
	  {
	    j = i;
	    /* If we reach the end of the line (i multiple of _board_size). */
	    if ((i % _board_size) == 1)
	      cout << '\n' << line++ << SEP_C;
	    /* Gets the i-th bit of the white bitboard. */
	    check = (_white_bitboard >> j) & 1ULL;
	    /* Checks if there is no white disc. */
	    if (check == EMPTY)
	      {
		/* Gets the i-th bit of the black bitboard. */
		check = (_black_bitboard >> j) & 1ULL;
		if (check == EMPTY)
		  {
		    /* Gets the i-th bit of the black bitboard. */
		    check = (_mobility_bitboard >> j) & 1ULL;
		    /* Checks if there is black disc or nothing. */
		    (check == EMPTY)? cout << BLANK_C : cout << POSSIBLE_MOVE_C;
		  }
		else
		  cout << BLACK_C;
	      }
	    /* There is a white disc. */
	    else
	      cout << WHITE_C;
	  }
	else
	  j--;
      }
    cout << '\n';
  }
  
  void board::move (int x, int y)
  {
    int coordinates =  (x  + _board_size * (y - 1));
    bool flipped = false;
    for (int i = board::north; i != board::end_enum; i++)
      if (flip_discs (coordinates, i))
	flipped = true;
    if (!flipped)
      throw illegal_move;
    switch_turn ();
    if (_black_turn)
      mobility_calculation (_black_bitboard, _white_bitboard);
    else
      mobility_calculation (_white_bitboard, _black_bitboard);
    /* display (); */
  }
  
  bool board::can_move ()
  {
    if (_mobility_bitboard == 0)
      return false;
    return true;
  }
  
  int board::end_game_state ()
  {
    int nb_white_discs = 0, nb_black_discs = 0;
    int i;
    for (i = 0; i < _nb_cases; i++)
      {
	/* Counts the number of white discs. */
	if ((_white_bitboard >> 1) & (1ULL == 1))
	  nb_white_discs ++;
	_white_bitboard = _white_bitboard >> 1;
        
	/* Counts the number of black discs. */
	if ((_black_bitboard >> 1) & (1ULL == 1))
	  nb_black_discs ++;
	_black_bitboard = _black_bitboard >> 1;
      }
    
    if (nb_black_discs > nb_white_discs)
      return black;
    if (nb_black_discs < nb_white_discs)
      return white;
    return tie;
  }
  
  bool board::is_game_over ()
  {
    if (can_move ())
      return false;
    else
      {
	switch_turn ();
	if (_black_turn)
	  mobility_calculation (_black_bitboard, _white_bitboard);
	else
	  mobility_calculation (_white_bitboard, _black_bitboard);
	if (can_move ())
	  return false;
	else
	  return true;
      }
  }
  
  void board::mobility_calculation (const bitboard & current_bitboard,
				    const bitboard & opponent_bitboard)
  {
    /* Bitboard of empty cells. */
    bitboard empty = ~(opponent_bitboard | current_bitboard);
    bitboard candidates,  moves = 0;
    /* True if shift must be negative. */
    bool negative_shift;
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
	    negative_shift = false;
	    shift = 1;
	    break;
	    
	  case west :
	    negative_shift = true;	    
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
	    /* Invalid direction. */
	    throw string ("ERREUR : Direction invalide\n");
	    break;
	  }
	
	/* Because left shift with negative value does not work
	   when expected. */
	if (negative_shift)
	  candidates = opponent_bitboard & (current_bitboard << shift);
	
	else
	  candidates = opponent_bitboard & (current_bitboard >> shift);
        
	while (candidates != 0)
	  {
	    /* Because left shift with negative value does not work
	       when expected. */
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
    _mobility_bitboard = moves;
  }
  
  board::bitboard board::get_mobility_bitboard ()
  {
    return _mobility_bitboard;
  }
  
  void board::serialize(std::ostream &os) const
  {
    std::stringstream ss;
    
    ss << (_black_turn == true ? "X" : "O");
    for (int i = _nb_cases - 1; i >= 0; --i)
      {
	if (i % _board_size == _board_size - 1)
	  ss << std::endl;
	if (((_white_bitboard >> i) & 1ULL) == EMPTY)
          {
	    if (((_black_bitboard >> i) & 1ULL) == EMPTY)
	      ss << BLANK_C;
	    else
	      ss << BLACK_C;
          }
	else
	  ss << WHITE_C;
	ss << SEP_C;
      }
    ss << std::endl;
    os << ss.str();
  }
  
  std::ostream &operator<<(std::ostream &os, const board &brd)
  {
    brd.serialize(os);
    return os;
  }
  
  void save_at(const std::string &filename, const board &brd)
  {
    try
      {
	std::ofstream os;
        
	os.exceptions(std::ofstream::failbit);
	os.open(filename, std::ios::trunc);
	os << brd;
	
	os.close();
      }
    catch (std::ios_base::failure& e)
      {
	std::cerr << "An Error occured while saving to file " << filename
		  << std::endl;
      }
  }
}
