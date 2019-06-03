#include <iostream>
#include <climits>
#include <chrono>
#include <time.h>
#include <stdlib.h>
#include <cstdio>
#include <unistd.h>


using namespace std;


/*
 *  ASCII X = 88
 *  ASCII O = 79
 */

// FUNCTION PROTOTYPES
void drawBoard(void);
void choseType(void);
bool checkGameState(void);
void getUSERMove(void);
bool isMoveValid(int, int, char);
char USER(void);
char CPU(void);
bool isWinner(char);
void getCPUMove(void);
int boardEvaluate(void);
int minimmax(bool);
//

char board[3][3] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

char PLAYER1; //Minimizer
char PLAYER2; //Maximizer

int currentPlayer;

void drawBoard(void) //GAME LOOP
{
    cout << "\033[2J\033[1;1H"; //clear the whole Screen
    cout << "         ******* GAME OF TIC-TAC-TOE ******* \n\n\n";
    cout << "PLAYER 1 (USER) : " << PLAYER1
         << "           "
         << "PLAYER 2 (CPU) : " << PLAYER2
         << "\n\n\n";

    cout << "              |"
         << "     |\n";
    cout << "           " << board[0][0] << "  |  " << board[0][1] << "  |  " << board[0][2] << endl;
    cout << "              |"
         << "     |\n";
    cout << "         ------------------" << endl;
    cout << "              |"
         << "     |\n";
    cout << "           " << board[1][0] << "  |  " << board[1][1] << "  |  " << board[1][2] << endl;
    cout << "              |"
         << "     |\n";
    cout << "         ------------------" << endl;
    cout << "              |"
         << "     |\n";
    cout << "           " << board[2][0] << "  |  " << board[2][1] << "  |  " << board[2][2] << endl;
    cout << "              |"
         << "     |\n";

    cout << "\n\n";
}

void choseType(void) //Init USER with O or X
{
inLabel:
    cout << "\033[2J\033[1;1H";
    cout << "\n\n   PLAYER 1  : \n\n\n";
    cout << "             |\n";
    cout << "       X     |     O\n";
    cout << "             |\n\n\n";
    cout << "ENTER YOUR CHOICE : ";
    char choice;
    cin >> choice;

    switch (choice)
    {
    case 'X':
        PLAYER1 = 'X';
        PLAYER2 = 'O';
        break;
    case 'O':
        PLAYER1 = 'O';
        PLAYER2 = 'X';
        break;
    default:
        goto inLabel;
    }
}

bool checkGameState(void) // TRUE for Empty, False for No empty cells
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return true;
        }
    }

    return false;
}

void getUSERMove(void) //Gets the move from USER
{
    int location, loc_row, loc_col;
correctLoc:
    cout << "Enter the Board Position : ";
    cin >> location;
    if (!(location <= 9 && location >= 1))
    {
        drawBoard();
        goto correctLoc;
    }
    location--;
    loc_row = location / 3;
    loc_col = location % 3;

    if (isMoveValid(loc_row, loc_col, PLAYER1))
    {
        board[loc_row][loc_col] = PLAYER1;
    }
    else
    {
        drawBoard();
        goto correctLoc;
    }
}

bool isMoveValid(int i, int j, char player) //Pass the arguements of row, column and the current player
{
    if (player == 'X')
    {
        if (board[i][j] == 'O')
            return false;
    }
    else if (player == 'O')
    {
        if (board[i][j] == 'X')
            return false;
    }
    return true;
}

char USER(void)
{
    getUSERMove();
    return PLAYER1;
}

char CPU(void)
{ 
    getCPUMove();
    return PLAYER2;
}

int boardEvaluate(void) //Returns +10 for CPU Win, -10 for PLAYER win, 0 for No-wins till
{
    char hold;

    //For all Rows
    for (int i = 0; i < 3; i++)
    {
        hold = (board[i][0]) & (board[i][1]) & (board[i][2]);
        if (hold == PLAYER2)
        {
            return +10;
        }

        if (hold == PLAYER1)
        {
            return -10;
        }
    }

    //For all Columns
    for (int j = 0; j < 3; j++)
    {
        hold = (board[0][j]) & (board[1][j]) & (board[2][j]);
        if (hold == PLAYER2)
        {
            return +10;
        }

        if (hold == PLAYER1)
        {
            return -10;
        }
    }

    //For diagonal Elements

    //Principle Diagonal
    {
        hold = (board[0][0]) & (board[1][1]) & (board[2][2]);
        if (hold == PLAYER2)
        {
            return +10;
        }
        if (hold == PLAYER1)
        {
            return -10;
        }
    }

    //Secondary Diagonal
    {
        hold = (board[0][2]) & (board[1][1]) & (board[2][0]);
        if (hold == PLAYER2)
        {
            return +10;
        }
        if (hold == PLAYER1)
        {
            return -10;
        }
    }

    return 0;
}

int minimax(bool isMax) //Minimax Algorithm for AI
{
    int score = boardEvaluate();

    if (score != 0)
    {
        return score;
    }

    if (!checkGameState())
    {
        return 0;
    }

    if (isMax)
    {
        int bestMove = INT_MIN;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] != 'O' && board[i][j] != 'X')
                {
                    char tempMemory = board[i][j];
                    board[i][j] = PLAYER2;
                    bestMove = max(bestMove, minimax(!isMax));
                    board[i][j] = tempMemory;
                }
            }
        }

        return bestMove;
    }
    else
    {
        int bestMove = INT_MAX;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] != 'O' && board[i][j] != 'X')
                {
                    char tempMemory = board[i][j];
                    board[i][j] = PLAYER1;
                    bestMove = min(bestMove, minimax(!isMax));
                    board[i][j] = tempMemory;
                }
            }
        }

        return bestMove;
    }
}

void getCPUMove(void)
{
    cout << "\n\n\nCPU is thinking\n\n";
    for(int i = 0; i < rand() % 8; i++)
    {
       usleep(120000);
    }
    int bestMoveValue = INT_MIN;
    int row = -1, col = -1;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != 'X' && board[i][j] != 'O')
            {
                int moveValue;
                char tempMemory = board[i][j];
                board[i][j] = PLAYER2;
                moveValue = minimax(false);
                board[i][j] = tempMemory;

                if (moveValue > bestMoveValue)
                {
                    bestMoveValue = moveValue;
                    row = i;
                    col = j;
                }
            }
        }
    }

    board[row][col] = PLAYER2;
}

int main()
{
    srand(time(0));
    choseType();
    char player;
    char isWinner;
    int continuity = PLAYER1;
    while (checkGameState())
    {
        drawBoard();
        player = (++continuity % 2) ? (USER()) : (CPU());
        drawBoard();
        int win = boardEvaluate();
        if (win == +10)
        {
            cout << "\n\nPLAYER 2 Wins\n\n";
            cout << "         !!!! BETTER LUCK NEXT TIME !!!! \n\n\n";
            break;
        }

        // if (win == -10)
        // {
        //     cout << "\n\nPLAYER 1 Wins\n\n";
        //     break;
        // }

        if (checkGameState() == false)
            cout << "\n\nMatch Ties\n\n";
    }

    return 0;
}
