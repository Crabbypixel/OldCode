#include <iostream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <windows.h>

using namespace std;

// Game controls

// Declare and define
int height = 20;
int width = 40;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
bool gameover;

enum eDir
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
eDir dir;

void Intro() // Intro Page
{
    cout << "Snake Game" << endl;
    cout << "Beta version - 0.2" << endl;
    cout << "Play in CMD. Go towards * to score more!\nPress 'p' to end game. Use W, A, S and D keys to control." << endl;
    cout << "\n\nGame created by: Crabbyfeet.\nThis is my first game that I've ever made - October 2019" << endl;

    cout << "Press any key to play: " << endl;
    if (_getch())
        system("cls");
}

void Setup() // Set all values to default
{
    gameover = false;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Draw() // Draw the box and fruit (random)
{
    system("cls");
    int i, j;
    for (i = 0; i < width + 2; i++)
        cout << "_";
    cout << endl;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            if (j == 0 || j == (width - 1))
                cout << "|";

            if (i == y && j == x)
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "*";
            else
            {
                bool print = false;
                for (int k = 0; k < score; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }
        }
        cout << endl;
    }

    for (i = 0; i < width + 2; i++)
        cout << "_";
    cout << endl;
}

void Input() // Input values from keybrd
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;

        case 'd':
            dir = RIGHT;
            break;

        case 'w':
            dir = UP;
            break;

        case 's':
            dir = DOWN;
            break;

        case 'p':
            gameover = true;
            break;
        }
    }
}

void Logic() // Main logic
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < score; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
    case LEFT:
        x--;
        break;

    case RIGHT:
        x++;
        break;

    case UP:
        y--;
        break;

    case DOWN:
        y++;
        break;

    default:
        break;
    }
    /*if(x > width || x < 0 || y > height || y < 0)
          gameover = true;      -> Debug */

    if (x >= width)
        x = 0;
    else if (x < 0)
        x = width - 1;
    if (y >= height)
        y = 0;
    else if (y < 0)
        y = height - 1;

    for (int i = 0; i < score; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameover = true;

    if (x == fruitX && y == fruitY) // If fruit found
    {
        score++;
        srand(time(0));
        fruitX = rand() % width;
        fruitY = rand() % height;
    }
}

int main()
{
    Intro();
    Setup();
    while (!gameover)
    {
        Draw();
        Input();
        Logic();
        cout << "Score: " << score << endl;
    }

    system("cls");
    cout << "GAME OVER!" << endl;
    cout << "Score: " << score << endl;
    cout << "Press any key to quit..." << endl;

    _getch();
    return 0;
}