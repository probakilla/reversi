#include <player.hh>
#include <iostream>

namespace reversi
{
  using namespace std;

  player::player() {}

  player::~player() {}

  //Prototype
  void player::ask_move ()
  {
    string move;
    char max_abscissa = 'm', min_abscissa = 'a';
    char abscissa;
    int ordinate;
    cout << "Veuillez entrez le coup que vous voulez jouez (ex A1)" << endl;
  WHILE:while (1)
      {
	while ((!getline(cin, move) || move.size() != 2))
	  {
	    cin.clear (); // To disable ctrl-D, otherwise there is an infinite loop.
	    cout << "L'entrée est invalide, réessayer." << endl;
	  }
	abscissa = move[0];
	move.erase(0,1);// Erase the first character
	try
	  {
	    ordinate = stoi(move);// Convert the string to an int
	  }
	catch (const invalid_argument & i)// The second charactere isn't a int
	  {
	    cout << "L'entrée est invalide, réessayer." << endl;
	    goto WHILE;// We go to the begining of the while instruction
	  }
	// The input isn't in a good range. (We can possibly change that)
	if (((abscissa < min_abscissa || abscissa > max_abscissa) && (abscissa < toupper(min_abscissa) || abscissa > toupper(max_abscissa))) && (ordinate <= 9 || ordinate >= 0))
	  cout << "L'entrée est invalide, réessayer." << endl;
	else    
	  break;
      }
  }
}
