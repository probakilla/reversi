#include "player.hh"
#include "user.hh"
#include "board.hh"
#include <iostream>

namespace reversi
{
    using namespace std;

    user::user() {}

    user::~user() {}

    void user::ask_move (board b)
    {
        int x, y;
        string move;
        char max_abscissa = 'z', min_abscissa = 'a';
        char abscissa;
        int ordinate;
        cout << "Veuillez entrez le coup que vous voulez jouez (ex. A1) : " << endl;
    WHILE:while (1)
    {
        while (!getline(cin, move))
        {
            cin.clear (); // To disable ctrl-D, otherwise there is an infinite loop.
            cout << "L'entrée est invalide, veuillez réessayer." << endl;
        }
        abscissa = move[0];
        move.erase(0,1); // Erases the first character.
        try
        {
            ordinate = stoi(move); // Converts the string to an int.
        }
        catch (const invalid_argument & i) // The second charactere is not an int.
        {
            cout << "L'entrée est invalide, veuillez réessayer." << endl;
            goto WHILE; // We go to the beginning of the while instruction.
        }
        // The input is not in a good range. (we can possibly change that)
        if ((((abscissa >= min_abscissa && abscissa <= max_abscissa) || (abscissa >= toupper(min_abscissa) && abscissa <= toupper(max_abscissa)))) && (ordinate <= 8 || ordinate >= 0))
            break;
        else    
            cout << "L'entrée est invalide, veuillez réessayer." << endl;
    }
        if (abscissa >= min_abscissa && abscissa <= max_abscissa)
            x = abscissa - min_abscissa + 1;
        else if (abscissa >= toupper(min_abscissa) && abscissa <= toupper(max_abscissa))
            x = abscissa - toupper(min_abscissa) + 1;
        y = ordinate;
        try {
            b.move(x, y);
        }
        catch (exception& e) {
            cout << "Ce coup n'est pas valide, veuillez réessayer." << endl;
            ask_move(b);
        }
    }
}
