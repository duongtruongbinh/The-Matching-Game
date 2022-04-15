#include "Menu.h"


int main()
{
    int size = 4;
    ShowCur(0);
    SetConsoleTitleW(L"The Matching Game");

    pokemon **board;

    // playGame(board, size);
    MenuGame();

    delete[] board;

    system("pause");
    return 0;
}