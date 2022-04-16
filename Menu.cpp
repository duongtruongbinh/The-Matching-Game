#include "Menu.h"

void readFile(player *&rank, int &sizeofRank, int &size)
{
    fstream leaderboard;
    switch (size)
    {
    case 4:
        leaderboard.open("4x4.txt");
        break;
    case 6:
        leaderboard.open("6x6.txt");
        break;
    case 8:
        leaderboard.open("8x8.txt");
        break;
    }
    sizeofRank = 0;
    while (!leaderboard.eof())
    {
        char c;
        leaderboard.get(c);
        if (c == '\n')
            sizeofRank++;
    }
    sizeofRank--;
    rank = new player[sizeofRank];
    leaderboard.close();

    switch (size)
    {
    case 4:
        leaderboard.open("4x4.txt");
        break;
    case 6:
        leaderboard.open("6x6.txt");
        break;
    case 8:
        leaderboard.open("8x8.txt");
        break;
    }

    for (int i = 0; i < sizeofRank; i++)
    {
        leaderboard >> rank[i].name >> rank[i].time;
    }
    leaderboard.close();
}

void writeFile(player *&rank, int &sizeofRank, int &size)
{
    fstream leaderboard;
    switch (size)
    {
    case 4:
        leaderboard.open("4x4.txt");
        break;
    case 6:
        leaderboard.open("6x6.txt");
        break;
    case 8:
        leaderboard.open("8x8.txt");
        break;
    }
    for (int i = 0; i < sizeofRank; i++)
    {
        leaderboard << rank[i].name << " " << rank[i].time << endl;
    }
    leaderboard.close();
}

void sortPlayer(player *&rank, int &sizeofRank)
{
    for (int i = 0; i < sizeofRank - 1; i++)
        for (int j = i + 1; j < sizeofRank; j++)
            if (rank[i].time > rank[j].time)
                swap(rank[i], rank[j]);
}

void printLeaderboard(player *&rank, int &sizeofRank)
{
    GoTo(30, 10);
    cout << setfill('=');
    cout << setw(57) << "=";
    cout << setfill(' ');
    GoTo(30, 11);
    cout << "||" << setw(10) << " "
         << "|" << setw(26) << " "
         << "|" << setw(15) << " "
         << "||";

    GoTo(30, 12);
    cout << "||" << setw(7) << right << "RANK" << setw(3) << " "
         << "|" << setw(15) << right << "NAME" << setw(11) << " "
         << "|" << setw(10) << right << "TIME" << setw(5) << " "
         << "||";
    GoTo(30, 13);
    cout << "||" << setw(10) << " "
         << "|" << setw(26) << " "
         << "|" << setw(15) << " "
         << "||";
    GoTo(30, 14);
    cout << setfill('=');
    cout << setw(57) << "=";
    cout << setfill(' ');
    int i = 0;
    for (i = 0; i < 10; i++)
    {
        GoTo(30, 15 + i);
        cout << "||" << setw(5) << right << i + 1 << setw(5) << " "
             << "|" << setw(15) << right << rank[i].name << setw(11) << " "
             << "|" << setw(10) << right << rank[i].time << setw(5) << " "
             << "||";
        if (i >= sizeofRank - 1)
            break;
    }

    GoTo(30, 15 + i + 1);
    cout << setfill('=');
    cout << setw(57) << "=";
    cout << setfill(' ');
}

void Leaderboard()
{
    player *rank;
    int sizeofRank;
    int size = ChooseSize();
    readFile(rank, sizeofRank, size);
    sortPlayer(rank, sizeofRank);
    writeFile(rank, sizeofRank, size);
    readFile(rank, sizeofRank, size);
    GoTo(2, 2);
    SetColor(0, 9);
    cout << "      :::       ::::::::::    :::    ::::::::: ::::::::::::::::::: :::::::::  ::::::::     :::    ::::::::: :::::::::";
    GoTo(2, 3);
    SetColor(0, 3);
    cout << "     :+:       :+:         :+: :+:  :+:    :+::+:       :+:    :+::+:    :+::+:    :+:  :+: :+:  :+:    :+::+:    :+:";
    GoTo(2, 4);
    cout << "    +:+       +:+        +:+   +:+ +:+    +:++:+       +:+    +:++:+    +:++:+    +:+ +:+   +:+ +:+    +:++:+    +:+ ";
    GoTo(2, 5);
    cout << "   +#+       +#++:++#  +#++:++#++:+#+    +:++#++:++#  +#++:++#: +#++:++#+ +#+    +:++#++:++#++:+#++:++#: +#+    +:+  ";
    GoTo(2, 6);
    SetColor(0, 11);
    cout << "  +#+       +#+       +#+     +#++#+    +#++#+       +#+    +#++#+    +#++#+    +#++#+     +#++#+    +#++#+    +#+   ";
    GoTo(2, 7);
    SetColor(0, 13);
    cout << " #+#       #+#       #+#     #+##+#    #+##+#       #+#    #+##+#    #+##+#    #+##+#     #+##+#    #+##+#    #+#    ";
    GoTo(2, 8);
    cout << "#######################     ############ #############    ############  ######## ###     ######    ############      ";
    SetColor(0, 7);
    printLeaderboard(rank, sizeofRank);
    GoTo(43, 28);
    cout << "----------------------------";
    GoTo(45, 29);
    cout << "Enter to go back to menu";
    GoTo(43, 30);
    cout << "----------------------------";
    while (true)
    {
        char c = getch();
        if (c == 13)
            break;
    }
    delete[] rank;
}

pokemon **GenerateBoard(int size)
{
    pokemon **board = new pokemon *[size + 2];
    for (int i = 0; i < size + 2; i++)
        board[i] = new pokemon[size + 2];
    //  Create the border
    for (int i = 0; i < size + 2; i++)
        for (int j = 0; j < size + 2; j++)
        {
            board[i][j].value = char(43);
            board[i][j].pos.x = i;
            board[i][j].pos.y = j;
            if (i == 0 || j == 0 || i == size + 1 || j == size + 1)
                board[i][j].status = 0;
        }

    srand((int)time(0));
    // Create board
    int count = 0;
    while (count != size * size)
    {
        int column, row;
        char a = char('A' + char(rand() % 26));
        for (int i = 0; i < 2; i++)
        {
            do
            {
                column = rand() % size + 1;
                row = rand() % size + 1;

            } while (int(board[column][row].value) != 43);
            board[column][row].value = a;
            count++;
        }
    }
    return board;
}

void printSquare(int j, int i, char value)
{
    GoTo(5 + j * 10, 1 + i * 5);
    cout << " ------- ";
    GoTo(5 + j * 10, 1 + i * 5 + 1);
    cout << "|       |";
    GoTo(5 + j * 10, 1 + i * 5 + 2);
    cout << "|   " << value << "   |";
    GoTo(5 + j * 10, 1 + i * 5 + 3);
    cout << "|       |";
    GoTo(5 + j * 10, 1 + i * 5 + 4);
    cout << " ------- ";
}

void printEmpty(int j, int i)
{
    GoTo(5 + j * 10, 1 + i * 5);
    cout << "         ";
    GoTo(5 + j * 10, 1 + i * 5 + 1);
    cout << "         ";
    GoTo(5 + j * 10, 1 + i * 5 + 2);
    cout << "         ";
    GoTo(5 + j * 10, 1 + i * 5 + 3);
    cout << "         ";
    GoTo(5 + j * 10, 1 + i * 5 + 4);
    cout << "         ";
}

void printBoard(pokemon **&board, int size)
{
    for (int i = 0; i < size + 1; i++)
    {
        for (int j = 0; j < size + 1; j++)
            if (board[i][j].status)
                printSquare(j, i, board[i][j].value);
    }
}

void printWon()
{
    GoTo(30, 10);
    SetColor(0, 14);
    cout << "   __     __          __          __         ";
    GoTo(30, 11);
    cout << "   \\ \\   / /          \\ \\        / /         ";
    GoTo(30, 12);

    cout << "    \\ \\_/ /__  _   _   \\ \\  /\\  / /__  _ __  ";
    GoTo(30, 13);
    SetColor(0, 15);
    cout << "     \\   / _ \\| | | |   \\ \\/  \\/ / _ \\| '_ \\ ";
    GoTo(30, 14);
    cout << "      | | (_) | |_| |    \\  /\\  / (_) | | | |";
    GoTo(30, 15);
    SetColor(0, 12);
    cout << "      |_|\\___/ \\__,_|     \\/  \\/ \\___/|_| |_|";
    SetColor(0, 7);
}

void printLose()
{
    GoTo(30, 10);
    SetColor(0, 13);
    cout << " __     __           _                    ";
    GoTo(30, 11);
    cout << " \\ \\   / /          | |                   ";
    GoTo(30, 12);
    cout << "  \\ \\_/ /__  _   _  | |     ___  ___  ___ ";
    GoTo(30, 13);
    SetColor(0, 9);
    cout << "   \\   / _ \\| | | | | |    / _ \\/ __|/ _ \\";
    GoTo(30, 14);
    cout << "    | | (_) | |_| | | |___| (_) \\__ \\  __/";
    GoTo(30, 15);
    SetColor(0, 3);
    cout << "    |_|\\___/ \\__,_| |______\\___/|___/\\___|";
    SetColor(0, 7);
}

void printPlaySquare()
{
    GoTo(45, 13);
    cout << " =================== ";
    GoTo(45, 14);
    cout << "|                   |";
    GoTo(45, 15);
    cout << "|        PLAY       |";
    GoTo(45, 16);
    cout << "|                   |";
    GoTo(45, 17);
    cout << " =================== ";
}

void printLeaderboardSquare()
{
    GoTo(45, 19);
    cout << " =================== ";
    GoTo(45, 20);
    cout << "|                   |";
    GoTo(45, 21);
    cout << "|    LEADERBOARD    |";
    GoTo(45, 22);
    cout << "|                   |";
    GoTo(45, 23);
    cout << " =================== ";
}

void printNameofGame()
{
    system("cls");
    GoTo(12, 3);
    cout << " _______ _            __  __       _       _     _                _____                      ";
    GoTo(12, 4);
    SetColor(0, 10);
    cout << "|__   __| |          |  \\/  |     | |     | |   (_)              / ____|                     ";
    GoTo(12, 5);
    cout << "   | |  | |__   ___  | \\  / | __ _| |_ ___| |__  _ _ __   __ _  | |  __  __ _ _ __ ___   ___ ";
    GoTo(12, 6);
    SetColor(0, 14);
    cout << "   | |  | '_ \\ / _ \\ | |\\/| |/ _` | __/ __| '_ \\| | '_ \\ / _` | | | |_ |/ _` | '_ ` _ \\ / _ \\";
    GoTo(12, 7);
    cout << "   | |  | | | |  __/ | |  | | (_| | || (__| | | | | | | | (_| | | |__| | (_| | | | | | |  __/";
    GoTo(12, 8);
    SetColor(0, 12);
    cout << "   |_|  |_| |_|\\___| |_|  |_|\\__,_|\\__\\___|_| |_|_|_| |_|\\__, |  \\_____|\\__,_|_| |_| |_|\\___|";
    GoTo(12, 9);
    cout << "                                                          __/ |                              ";
    GoTo(12, 10);
    cout << "                                                         |___/                               ";
}

void printSizeSquare(int size)
{
    GoTo(45, 10 + (size - 4) * 3);
    cout << " =================== ";
    GoTo(45, 11 + (size - 4) * 3);
    cout << "|                   |";
    GoTo(45, 12 + (size - 4) * 3);
    cout << "|       " << size << " X " << size << "       |";
    GoTo(45, 13 + (size - 4) * 3);
    cout << "|                   |";
    GoTo(45, 14 + (size - 4) * 3);
    cout << " =================== ";
}

void printExitSquare()
{
    GoTo(45, 25);
    cout << " =================== ";
    GoTo(45, 26);
    cout << "|                   |";
    GoTo(45, 27);
    cout << "|       EXIT        |";
    GoTo(45, 28);
    cout << "|                   |";
    GoTo(45, 29);
    cout << " =================== ";
}

int ChooseSize()
{
    int choice = 1;
    SetColor(0, 11);
    GoTo(30, 5);
    cout << " ____ ____ _    ____ ____ ___    ____ _ ___  ____";
    GoTo(30, 6);
    cout << " [__  |___ |    |___ |     |     [__  |   /  |___ ";
    GoTo(30, 7);
    cout << " ___] |___ |___ |___ |___  |     ___] |  /__ |___ ";
    SetColor(7, 0);
    printSizeSquare(4);
    SetColor(0, 7);
    printSizeSquare(6);
    printSizeSquare(8);
    while (true)
    {
        if (choice == 1)
        {
            SetColor(7, 0);
            printSizeSquare(4);
            SetColor(0, 7);
            printSizeSquare(6);
            printSizeSquare(8);
        }
        if (choice == 2)
        {
            SetColor(7, 0);
            printSizeSquare(6);
            SetColor(0, 7);
            printSizeSquare(4);
            printSizeSquare(8);
        }
        if (choice == 3)
        {
            SetColor(7, 0);
            printSizeSquare(8);
            SetColor(0, 7);
            printSizeSquare(4);
            printSizeSquare(6);
        }
        char c = _getch();
        c = tolower(c);
        switch (c)
        {
        case 's':
            if (choice == 1)
            {
                SetColor(7, 0);
                printSizeSquare(6);
                SetColor(0, 7);
                choice = 2;
                break;
            }
            if (choice == 2)
            {
                SetColor(7, 0);
                printSizeSquare(8);
                SetColor(0, 7);
                choice = 3;
                break;
            }
            if (choice == 3)
            {
                SetColor(7, 0);
                printSizeSquare(4);
                SetColor(0, 7);
                choice = 1;
                break;
            }
            break;
        case 'w':
            if (choice == 1)
            {
                SetColor(7, 0);
                printSizeSquare(8);
                SetColor(0, 7);
                choice = 3;
                break;
            }
            if (choice == 2)
            {
                SetColor(7, 0);
                printSizeSquare(4);
                SetColor(0, 7);
                choice = 1;
                break;
            }
            if (choice == 3)
            {
                SetColor(7, 0);
                printSizeSquare(6);
                SetColor(0, 7);
                choice = 2;
                break;
            }
            break;
        case 13:
            if (choice == 1)
            {
                system("cls");
                return 4;
            };
            if (choice == 2)
            {
                system("cls");
                return 6;
            }
            if (choice == 3)
            {
                system("cls");
                return 8;
            }
            break;
        }
    }
}

void MenuGame()
{
    printNameofGame();

    int choice = 1;

    while (true)
    {
        SetColor(0, 7);
        printPlaySquare();
        printLeaderboardSquare();
        printExitSquare();
        if (choice == 1)
        {
            SetColor(7, 0);
            printPlaySquare();
            SetColor(0, 7);
            printLeaderboardSquare();
        }
        if (choice == 2)
        {
            SetColor(7, 0);
            printLeaderboardSquare();
            SetColor(0, 7);
            printPlaySquare();
        }
        if (choice == 3)
        {
            SetColor(7, 0);
            printExitSquare();
            SetColor(0, 7);
            printPlaySquare();
        }
        char c = _getch();
        c = tolower(c);
        switch (c)
        {
        case 's':
            if (choice == 1)
            {
                SetColor(7, 0);
                printLeaderboardSquare();
                SetColor(0, 7);
                choice = 2;
                break;
            }
            if (choice == 2)
            {
                SetColor(7, 0);
                printExitSquare();
                SetColor(0, 7);
                choice = 3;
                break;
            }
            if (choice == 3)
            {
                SetColor(7, 0);
                printPlaySquare();
                SetColor(0, 7);
                choice = 1;
                break;
            }
        case 'w':
            if (choice == 1)
            {
                SetColor(7, 0);
                printExitSquare();
                SetColor(0, 7);
                choice = 3;
                break;
            }
            if (choice == 2)
            {
                SetColor(7, 0);
                printPlaySquare();
                SetColor(0, 7);
                choice = 1;
                break;
            }
            if (choice == 3)
            {
                SetColor(7, 0);
                printLeaderboardSquare();
                SetColor(0, 7);
                choice = 2;
                break;
            }
        case 13:
            if (choice == 1)
            {
                system("cls");
                int size = ChooseSize();
                pokemon **board = GenerateBoard(size);
                int timemax = 0;
                if (size == 4)
                    timemax = 3;
                if (size == 6)
                    timemax = 5;
                if (size == 8)
                    timemax = 8;
                playGame(board, size, timemax);
                delete[] board;
                MenuGame();
                return;
            }
            if (choice == 2)
            {
                system("cls");
                Leaderboard();

                while (true)
                {
                    char c = getch();
                    if (c == 13)
                        break;
                }
                MenuGame();
                return;
            }

            if (choice == 3)
            {
                system("cls");
                return;
            }
            break;
        }
    }
}
