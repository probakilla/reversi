#include <board.hh>
#include <player.hh>
#include <user.hh>
#include <random_ia.hh>
#include <iostream>

using namespace reversi;

int main()
{
    board brd;
    user usr;
    random_ia ria;

    while (1)
    {
        brd.display ();
        usr.ask_move(brd);
        brd.display ();
        ria.ask_move(brd);
    }
    return 0;
}