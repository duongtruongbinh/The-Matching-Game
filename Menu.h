#include "Library.h"
#include "WindowConsole.h"
struct position
{
    int x;
    int y;
};

struct pokemon
{
    char value = '+';
    position pos;
    position pre_pos;
    int turn = 0;
    bool status = 1;
};

struct player
{
    string name;
    double time;
};

struct Node
{
    pokemon data;
    Node *next = nullptr;
};

struct List
{
    Node *Head;
    Node *Tail;
};

void readFile(player *&rank, int &sizeofRank, int &size);

void writeFile(player *&rank, int &sizeofRank, int &size);

void sortPlayer(player *&rank, int &sizeofRank);

void printLeaderboard(player *&rank, int &sizeofRank);

void Leaderboard();

pokemon **GenerateBoard(int size);

void printSquare(int j, int i, char value);

void printEmpty(int j, int i);

void printBoard(pokemon **&board, int size);

void printWon();

void printLose();

void printPlaySquare();

void printLeaderboardSquare();

void printNameofGame();

void printSizeSquare(int size);

void printExitSquare();

int ChooseSize();

void MenuGame();

void playGame(pokemon **&board, int size, int timeMax);
