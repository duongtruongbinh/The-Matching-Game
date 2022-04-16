#include "Menu.h"

int main()
{
    int size = 4;
    ShowCur(0);
    SetConsoleTitleW(L"The Matching Game");

    // playGame(board, size);
    MenuGame();

    system("pause");
    return 0;
}