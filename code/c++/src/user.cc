#include "player.hh"
#include "user.hh"
#include "board.hh"
#include <iostream>

namespace reversi
{
  using namespace std;
  
  user::user () {}
  
  user::~user () {}
  
  void user::ask_move (board &b)
  {
    while (1) {
      int x, y;
      string move;
      char min_abscissa = 'a', max_abscissa = 'z';
      char abscissa;
      int ordinate;
      cout << "Veuillez entrer le coup que vous souhaitez jouer (ex. A1) :"
	   << endl;
    WHILE:while (1)
	{
	  while (!getline (cin, move))
	    {
	      /* To disable ctrl-D, otherwise there is an infinite loop. */
	      cin.clear ();
	      cout << "Entrée invalide, veuillez réessayer." << endl;
	    }
	  abscissa = move[0];
	  /* Erases the first character. */
	  move.erase (0,1);
	  try
	    {
	      /* Converts the string to an int. */
	      ordinate = stoi (move);
	    }
	  /* The second character is not an int. */
	  catch (const invalid_argument & i)
	    {
	      cout << "Entrée invalide, veuillez réessayer." << endl;
	      /* Goes to the beginning of the while instruction. */
	      goto WHILE;
	    }
	  /* The input is not in a good range. (we can possibly change that) */
	  if ((((abscissa >= min_abscissa && abscissa <= max_abscissa) ||
		(abscissa >= toupper (min_abscissa) &&
		 abscissa <= toupper (max_abscissa))))
	      && (ordinate <= 8 || ordinate >= 0))
	    break;
	  else
	    cout << "Entrée invalide, veuillez réessayer." << endl;
	}
      if (abscissa >= min_abscissa && abscissa <= max_abscissa)
	x = abscissa - min_abscissa + 1;
      else if (abscissa >= toupper (min_abscissa) &&
	       abscissa <= toupper (max_abscissa))
	x = abscissa - toupper (min_abscissa) + 1;
      y = ordinate;
      try {
	b.move (x, y);
	break;
      }
      catch (exception &e) {
	cout << "Coup non valide, veuillez réessayer." << endl;
      }
    }
  }
}
