#include "Menu.h"



Node *CreateNode(pokemon data);

List *CreateList(Node *p);

void AddHead(List *&L, Node *p);

void RemoveHead(List *&L);

void AddTail(List *&L, Node *p);

void Push(List ***&L, int size, int i, int j, pokemon temp);

void Build(pokemon **board, int size, List ***&L);

int Turn(int x, int y, pokemon p);

bool Matching(pokemon **&board, int size, int I_x, int I_y, int F_x, int F_y);

void UpdateBoard(pokemon **&board, int size, int count);

List *Hint_board(pokemon **board, int size);

