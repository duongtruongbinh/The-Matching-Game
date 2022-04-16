#include "Matching.h"

Node *CreateNode(pokemon data)
{
    Node *p = new Node;
    p->data = data;
    p->next = NULL;
    return p;
}

List *CreateList(Node *p)
{
    List *L = new List;
    L->Head = p;
    L->Tail = p;
    return L;
}

void AddHead(List *&L, Node *p)
{
    p->next = L->Head;
    L->Head = p;
}

void RemoveHead(List *&L)
{
    if (L->Head == NULL)
        return;
    Node *p = L->Head;
    L->Head = p->next;
    delete p;
}

void AddTail(List *&L, Node *p)
{
    L->Tail->next = p;
    L->Tail = p;
}

void Push(List ***&L, int size, int i, int j, pokemon temp)
{
    //    cout << L[i][j]->Tail->data.value << " ";
    if (temp.status == 0)
    {
        temp.pre_pos.x = i;
        temp.pre_pos.y = j;
        AddTail(L[i][j], CreateNode(temp));
        //    q[i * size + j].push(temp);
        //    	cout << i << " and " << j << " pos " << temp.pos.x << " " << temp.pos.y << endl;
    }
}

void Build(pokemon **board, int size, List ***&L)
{

    for (int i = 0; i < size + 2; i++)
    {
        for (int j = 0; j < size + 2; j++)
        {
            //    cout << i << " " << j << endl;
            pokemon root;
            L[i][j] = CreateList(CreateNode(root));
            if (i - 1 >= 0)
            {
                Push(L, size + 2, i, j, board[i - 1][j]);
                //		cout << "True1";
            }
            if (i + 1 <= size + 1)
            {
                Push(L, size + 2, i, j, board[i + 1][j]);
                //		cout << "True2";
            }
            if (j - 1 >= 0)
            {
                Push(L, size + 2, i, j, board[i][j - 1]);
                //		cout << "True3";
            }
            if (j + 1 <= size + 1)
            {
                Push(L, size + 2, i, j, board[i][j + 1]);
                //		cout << "True4";
            }
            RemoveHead(L[i][j]);
            //    cout << "end"<<endl;
        }
    }
}

int Turn(int x, int y, pokemon p)
{
    if (x == p.pos.x || y == p.pos.y)
        return 0;
    else
        return 1;
}

bool Matching(pokemon **&board, int size, int I_x, int I_y, int F_x, int F_y)
{
    if (board[I_x][I_y].status == 0 || board[F_x][F_y].status == 0)
        return 0;
    if (board[I_x][I_y].value != board[F_x][F_y].value || (I_x == F_x && I_y == F_y))
    {
        //	cout << a[I_x * n + I_y]<<"  "<< a[F_x * n + F_y]<<"False";
        return 0;
    }
    board[F_x][F_y].status = 0;

    //    queue<pokemon> q[144];
    List ***L = new List **[size + 2];
    for (int i = 0; i < size + 2; i++)
        L[i] = new List *[size + 2];
    //    cout << "List";
    Build(board, size, L);
    /*for (int i = 0; i < (size + 2); i++)
    {
        for (int j = 0; j < (size + 2); j++)
        {
         //   cout << i << " " << j << endl;
            int count = 0;
            Node* g = new Node;
            g = L[i][j]->Head;
            while (g != NULL)
            {
                count++;
                cout << g->data.value << " " << g->data.pos.x
                    << " " << g->data.pos.y << endl;
                g = g->next;
            }
            cout << count << endl;
        }
    }
    cout << endl << "Queue\n";
    for (int i = 0; i < (size + 2); i++)
    {
        for (int j = 0; j < (size + 2); j++)
        {
            int n= q[i * (size + 2) + j].size() ;
            printf("Queue [%d][%d]:\n", i, j);
            for (int k = 0; k < n; k++)
            {
                cout << q[i * (size + 2) + j].front().pos.x << " " << q[i * (size + 2) + j].front().pos.y << endl;
                q[i * (size + 2) + j].pop();
            }
        }
        cout << endl;
    }
    Build(board, size, q);*/
    int **Checking = new int *[size + 2];
    for (int i = 0; i < (size + 2); i++)
        Checking[i] = new int[size + 2];
    for (int i = 0; i < (size + 2); i++)
        for (int j = 0; j < (size + 2); j++)
            Checking[i][j] = 0;
    //    int check = 0;
    // cout << I_x<<" "<< I_y<<" "<< q[I_x * (size + 2) + I_y].size() << endl;
    //   while (!q[I_x * (size + 2) + I_y].empty())
    Node *i = new Node;
    while (L[I_x][I_y]->Head != NULL)
    {
        //    pokemon temp = q[I_x * (size + 2) + I_y].front();
        pokemon temp = L[I_x][I_y]->Head->data;
        //    cout << temp.pos.x << " " << temp.pos.y << endl;
        if (!temp.status)
        {
            //	cout << temp.pos.x << " " << temp.pos.y << endl;
            if (temp.pos.x == F_x && temp.pos.y == F_y && temp.turn <= 2)
            {
                board[I_x][I_y].status = 0;
                return 1;
            }
            //    q[I_x * (size + 2) + I_y].pop();

            int u = temp.pos.x;
            int v = temp.pos.y;
            int pre_x = temp.pre_pos.x;
            int pre_y = temp.pre_pos.y;
            Checking[u][v] = 1;
            //    int N = q[u * (size + 2) + v].size();
            //		cout << N<<endl;
            //    for (int i = 0; i < N; i++)
            Node *i = new Node;
            i = L[u][v]->Head;
            while (i != NULL)
            {
                //    pokemon p = q[u * (size + 2) + v].front();
                pokemon p = i->data;
                /*cout << "ppos " << p.pos.x << " " << p.pos.y << "\ndd "
                    << Checking[p.pos.x][p.pos.y] << "\nu v " << u << " and " << v
                    << "\ntemp.turn" << temp.turn << " " << Turn(pre_x, pre_y, p)
                    << "\npre " << temp.pre_pos.x << " " << pre_y << endl;*/
                if (Checking[p.pos.x][p.pos.y] == 0)
                {
                    //    cout << "1\n";
                    if (p.status == 0)
                    {
                        p.turn = temp.turn + Turn(pre_x, pre_y, p);
                        //	cout << pre_x << " " << pre_y << " " << u << " and " << v << " pos " << p.pos.x << " " << p.pos.y << " turn " << p.turn << endl;
                        if (p.turn <= 2)
                        {
                            /*if (p.pos.x == F_x && p.pos.y == F_y)
                            {
                                board[F_x][F_y].status = 0;
                                return 1;
                            }*/
                            //    q[I_x * (size + 2) + I_y].push(p);
                            AddTail(L[I_x][I_y], CreateNode(p));
                        }
                    }
                }
                i = i->next;
                //   q[u * (size + 2) + v].pop();
                //    RemoveHead(L[I_x][I_y]);
                //   system("pause");
            }
        }
        RemoveHead(L[I_x][I_y]);
    }
    delete[] Checking;
    board[F_x][F_y].status = 1;
    return 0;
}

void UpdateBoard(pokemon **&board, int size, int count)
{
    const int COUNT = count;
    //   cout << "update\n";
    count = 0;
    position *Pos = new position[size * size];
    for (int i = 1; i < size + 1; i++)
    {
        for (int j = 1; j < size + 1; j++)
        {
            if (board[i][j].status != 0)
            {
                Pos[count] = board[i][j].pos;
                //   cout << Pos[count].x << " " << Pos[count].y << endl;
                count++;
            }
        }
    }
    srand((int)time(0));
    int n = rand() % 100;
    //    cout << n << " u and v\n";
    for (int i = 0; i < n; i++)
    {
        int u = rand() % COUNT;
        int v = u;
        do
        {
            v = rand() % COUNT;
        } while (v == u);
        //   cout << u << " " << v << endl;
        //    cout << board[Pos[u].x][Pos[u].y].value << " " << board[Pos[v].x][Pos[v].y].value << endl;
        char temp = board[Pos[u].x][Pos[u].y].value;
        board[Pos[u].x][Pos[u].y].value = board[Pos[v].x][Pos[v].y].value;
        board[Pos[v].x][Pos[v].y].value = temp;
    }
    //    for (int u = 1; u < size + 1; u++)
    //    {
    //        for (int v = 1; v < size + 1; v++)
    //        {
    //            cout << board[u][v].value << " ";
    //        }
    //        cout << endl;
    //    }
}

List *Hint_board(pokemon **board, int size)
{
    for (int I = 1; I < size + 1; I++)
    {
        for (int J = 1; J < size + 1; J++)
        {
            if (board[I][J].status != 0)
            {
                for (int i = 1; i < size + 1; i++)
                {
                    for (int j = 1; j < size + 1; j++)
                    {
                        bool t = Matching(board, size, I, J, i, j);
                        if (t)
                        {
                            board[I][J].status = 1;
                            board[i][j].status = 1;
                            //    cout << I << " " << J << " with " << i << " " << j << endl;
                            List *l = CreateList(CreateNode(board[I][J]));
                            AddTail(l, CreateNode(board[i][j]));
                            return l;
                        }
                    }
                }
            }
        }
    }
    return NULL;
}

void playGame(pokemon **&board, int size, int timeMax)
{
    int current_x = 0, current_y = 0;
    int chosen_x = -1, chosen_y = -1;
    int pokemon_unchecked = size * size;
    while (!Hint_board(board, size))
    {
        UpdateBoard(board, size, size * size);
    }

    printBoard(board, size);

    SetColor(7, 0);
    printSquare(current_x + 1, current_y + 1, board[current_y + 1][current_x + 1].value);
    SetColor(0, 7);

    clock_t start, end;
    double time_used;

    start = clock();
    while (pokemon_unchecked)
    {
        char c = _getch();
        c = tolower(c);
        int temp_x = current_x, temp_y = current_y;
        // printBoard(board, size);

        if (board[current_y + 1][current_x + 1].status == 0)
            printEmpty(current_x + 1, current_y + 1);

        switch (c)
        {
        case 'a':
            if (current_x - 1 >= 0)
                current_x--;

            if (board[temp_y + 1][temp_x + 1].status == 0)
                printEmpty(temp_x + 1, temp_y + 1);
            else
            {
                SetColor(0, 7);
                printSquare(temp_x + 1, temp_y + 1, board[temp_y + 1][temp_x + 1].value);
            }

            if (board[current_y + 1][current_x + 1].status != 0)
            {
                SetColor(7, 0);
                printSquare(current_x + 1, current_y + 1, board[current_y + 1][current_x + 1].value);
                SetColor(0, 7);
            }
            else
            {
                SetColor(7, 0);
                printEmpty(current_x + 1, current_y + 1);
                SetColor(0, 7);
            }

            break;
        case 'd':
            if (current_x + 1 <= size - 1)
                current_x++;
            if (board[temp_y + 1][temp_x + 1].status == 0)
                printEmpty(temp_x + 1, temp_y + 1);
            else
            {
                SetColor(0, 7);
                printSquare(temp_x + 1, temp_y + 1, board[temp_y + 1][temp_x + 1].value);
            }
            if (board[current_y + 1][current_x + 1].status != 0)
            {
                SetColor(7, 0);
                printSquare(current_x + 1, current_y + 1, board[current_y + 1][current_x + 1].value);
                SetColor(0, 7);
            }
            else
            {
                SetColor(7, 0);
                printEmpty(current_x + 1, current_y + 1);
                SetColor(0, 7);
            }

            break;
        case 's':
            if (current_y + 1 <= size - 1)
                current_y++;

            if (board[temp_y + 1][temp_x + 1].status == 0)
                printEmpty(temp_x + 1, temp_y + 1);
            else
            {
                SetColor(0, 7);
                printSquare(temp_x + 1, temp_y + 1, board[temp_y + 1][temp_x + 1].value);
            }

            if (board[current_y + 1][current_x + 1].status != 0)
            {
                SetColor(7, 0);
                printSquare(current_x + 1, current_y + 1, board[current_y + 1][current_x + 1].value);
                SetColor(0, 7);
            }
            else
            {
                SetColor(7, 0);
                printEmpty(current_x + 1, current_y + 1);
                SetColor(0, 7);
            }

            break;
        case 'w':
            if (current_y - 1 >= 0)
                current_y--;

            if (board[temp_y + 1][temp_x + 1].status == 0)
                printEmpty(temp_x + 1, temp_y + 1);
            else
            {
                SetColor(0, 7);
                printSquare(temp_x + 1, temp_y + 1, board[temp_y + 1][temp_x + 1].value);
            }

            if (board[current_y + 1][current_x + 1].status != 0)
            {
                SetColor(7, 0);
                printSquare(current_x + 1, current_y + 1, board[current_y + 1][current_x + 1].value);
                SetColor(0, 7);
            }
            else
            {
                SetColor(7, 0);
                printEmpty(current_x + 1, current_y + 1);
                SetColor(0, 7);
            }

            break;
        case 'h':
            if (Hint_board(board, size))
            {
                List *l = Hint_board(board, size);
                position temp1, temp2;
                temp1 = l->Head->data.pos;
                temp2 = l->Tail->data.pos;
                SetColor(7, 0);
                printSquare(temp1.y, temp1.x, board[temp1.x][temp1.y].value);
                SetColor(0, 7);
                SetColor(7, 0);
                printSquare(temp2.y, temp2.x, board[temp2.x][temp2.y].value);
                SetColor(0, 7);
            }
            break;
        case 13:
            if (board[current_y + 1][current_x + 1].status)
            {
                SetColor(9, 0);
                printSquare(current_x + 1, current_y + 1, board[current_y + 1][current_x + 1].value);
                SetColor(0, 7);
            }
            else
            {
                SetColor(7, 0);
                printEmpty(current_x + 1, current_y + 1);
                SetColor(0, 7);
                break;
            }

            if (chosen_x != -1 && chosen_y != -1)

                if (Matching(board, size, current_y + 1, current_x + 1, chosen_y + 1, chosen_x + 1) && board[current_y + 1][current_x + 1].value == board[chosen_y + 1][chosen_x + 1].value && !(current_x == chosen_x && chosen_y == current_y))
                {
                    Sleep(400);

                    SetColor(2, 0);
                    printSquare(chosen_x + 1, chosen_y + 1, board[chosen_y + 1][chosen_x + 1].value);
                    printSquare(current_x + 1, current_y + 1, board[current_y + 1][current_x + 1].value);
                    SetColor(0, 7);
                    printf("%c", 7);

                    Sleep(200);
                    printEmpty(chosen_x + 1, chosen_y + 1);
                    printEmpty(current_x + 1, current_y + 1);

                    board[current_y + 1][current_x + 1].status = board[chosen_y + 1][chosen_x + 1].status = 0;
                    chosen_x = chosen_y = -1;

                    SetColor(7, 0);
                    printEmpty(current_x + 1, current_y + 1);
                    SetColor(0, 7);

                    pokemon_unchecked -= 2;
                    if (!pokemon_unchecked)
                    {
                        break;
                    }
                    if (!Hint_board(board, size))
                    {
                        while (!Hint_board(board, size))
                        {
                            UpdateBoard(board, size, pokemon_unchecked);
                            for (int u = 1; u < size + 1; u++)
                            {
                                for (int v = 1; v < size + 1; v++)
                                {
                                    //    cout << board[u][v].value << " ";
                                }
                                //   cout << endl;
                            }
                            //   break;
                        }
                        //    cout << "cac";
                        //   system("pause");
                        printBoard(board, size);
                    }
                }
                else
                {
                    Sleep(200);

                    SetColor(4, 0);
                    printSquare(chosen_x + 1, chosen_y + 1, board[chosen_y + 1][chosen_x + 1].value);
                    printSquare(current_x + 1, current_y + 1, board[current_y + 1][current_x + 1].value);
                    SetColor(0, 7);
                    printf("%c", 7);

                    Sleep(800);

                    printSquare(chosen_x + 1, chosen_y + 1, board[chosen_y + 1][chosen_x + 1].value);
                    SetColor(7, 0);
                    printSquare(current_x + 1, current_y + 1, board[current_y + 1][current_x + 1].value);
                    SetColor(0, 7);

                    chosen_x = chosen_y = -1;
                }
            else
            {
                chosen_x = current_x;
                chosen_y = current_y;
            }
            break;
        default:
            if (board[current_y + 1][current_x + 1].status != 0)
            {
                SetColor(7, 0);
                printSquare(current_x + 1, current_y + 1, board[current_y + 1][current_x + 1].value);
                SetColor(0, 7);
            }
            else
            {
                SetColor(7, 0);
                printEmpty(current_x + 1, current_y + 1);
                SetColor(0, 7);
            }
            break;
        }

        if (chosen_x != -1 && chosen_y != -1)
        {
            SetColor(9, 0);
            printSquare(chosen_x + 1, chosen_y + 1, board[chosen_y + 1][chosen_x + 1].value);
            SetColor(0, 7);
        }
    }
    system("cls");
    end = clock();
    time_used = double(end - start) / CLOCKS_PER_SEC - 0.5;

    if (time_used <= timeMax * 60)
    {
        printWon();
        GoTo(35, 20);
        cout << "Congratulation ! Please enter your name: ";
        ShowCur(1);
        string name;
        cin >> name;
        GoTo(35, 22);
        cout << "Your time: " << time_used << " s.";
        Sleep(500);

        fstream leaderboard;
        switch (size)
        {
        case 4:
            leaderboard.open("4x4.txt", ios::app);
            break;
        case 6:
            leaderboard.open("6x6.txt", ios::app);
            break;
        case 8:
            leaderboard.open("8x8.txt", ios::app);
            break;
        }
        leaderboard << name << " " << time_used << endl;

        player *rank;
        int sizeofRank;
        readFile(rank, sizeofRank, size);
        sortPlayer(rank, sizeofRank);
        writeFile(rank, sizeofRank, size);
        leaderboard.close();
        delete[] rank;
        ShowCur(0);

        Sleep(500);
        system("cls");
        Leaderboard();
    }
    else
    {
        printLose();

        GoTo(38, 20);
        cout << "----------------------------";
        GoTo(40, 21);
        cout << "Enter to go back to menu";
        GoTo(38, 22);
        cout << "----------------------------";
        while (true)
        {
            char c = getch();
            if (c == 13)
                break;
        }
        
    }
}