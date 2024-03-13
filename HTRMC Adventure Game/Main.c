/*********************************************************************
* Author: H.T.R.M. Cox
* Date: 05/02/2024
* Description: Improved C program treasure hunt with more paths and outcomes
* Version: 0.1.0
* Compile: gcc main.c -o treasure
* Compile windows: cl main.c /Fetreasure
**********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#define WIDTH 20
#define HEIGHT 20
#define GAME_SPEED 100 // Game speed in milliseconds

int i, j, gameOver;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
int inGame = 0;

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
enum eDirection dir;

enum GameState { MAIN_MENU, CAVE_ENCOUNTER, RIVER_ENCOUNTER, FOREST_ENCOUNTER, SECRET_GAME };
enum GameState currentState = MAIN_MENU;

void Setup() {
    gameOver = 0;
    dir = STOP;
    x = WIDTH / 2;
    y = HEIGHT / 2;
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
    score = 0;
}

void Draw() {
    system("cls"); // system("clear") on Linux
    for (i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");

    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            if (j == 0)
                printf("#");
            if (i == y && j == x)
                printf("O");
            else if (i == fruitY && j == fruitX)
                printf("F");
            else {
                int print = 0;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        printf("o");
                        print = 1;
                    }
                }
                if (!print) printf(" ");
            }

            if (j == WIDTH - 1)
                printf("#");
        }
        printf("\n");
    }

    for (i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");
    printf("Score: %d\n", score);
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            if (inGame) dir = LEFT;
            break;
        case 'd':
            if (inGame) dir = RIGHT;
            break;
        case 'w':
            if (inGame) dir = UP;
            break;
        case 's':
            if (inGame) dir = DOWN;
            break;
        case 'x':
            gameOver = 1;
            break;
        }
    }
}

void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir) {
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
    if (x >= WIDTH) x = 0; else if (x < 0) x = WIDTH - 1;
    if (y >= HEIGHT) y = 0; else if (y < 0) y = HEIGHT - 1;

    for (i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = 1;

    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
        nTail++;
    }
}

int SecretMain() {
    inGame = 1;
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(GAME_SPEED);
    }
    inGame = 0;
    gameOver = 0;
    return 0;
}



void printTreasureChest() {
    printf("\033[0;33m"); // ANSI escape code to set text color to yellow
    printf("\nYou found the golden treasure chest!!! Congratulations!!!\n\n");
    printf("      ___________\n"
        "     '._==_==_=_.'\n"
        "     .-\\:      /-.\n"
        "    | (|:.     |) |\n"
        "     '-|:.     |-' \n"
        "       \\::.    /\n"
        "        '::. .'\n"
        "          ) (\n"
        "        _.' '._\n"
        "       `\"\"\"\"\"\"\"`\n");
    printf("\033[0m"); // ANSI escape code to reset text color
}

void encounterCave() {
    currentState = CAVE_ENCOUNTER;
    printf("You push through the thicket, finding a hidden cave.\n");
    printf("1. Enter the cave\n"
        "2. Continue on the path\n");
    int choice = getUserChoice();
    if (choice == 1) {
        printTreasureChest();
    }
    else {
        printf("You continue on the path, but find nothing of interest. THE END\n");
    }
}

void encounterRiver() {
    currentState = RIVER_ENCOUNTER;
    printf("Following the path, you come across a river.\n");
    printf("1. Attempt to cross the river\n"
        "2. Look for a different route\n");
    int choice = getUserChoice();
    if (choice == 1) {
        printf("You manage to find a shallow part and cross the river safely.\n");
        printTreasureChest();
    }
    else {
        printf("After years of searching, you did not find the treasure... THE END\n");
    }
}

void encounterForest() {
    currentState = FOREST_ENCOUNTER;
    printf("The forest is dense but beautiful, with sunlight filtering through the leaves.\n"
        "1. Explore deeper into the forest\n"
        "2. Stay on the outskirts and search\n");
    int choice = getUserChoice();
    if (choice == 1) {
        printf("You come across an ancient ruin, hiding a secret passage.\n");
        printTreasureChest();
    }
    else {
        printf("You find some old coins but nothing else of value. THE END\n");
    }
}

int mainMenu() {
    printf("\n"
        " _    _      _                           \n"
        "| |  | |    | |                          \n"
        "| |  | | ___| | ___ ___  _ __ ___   ___  \n"
        "| |/\\| |/ _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ \n"
        "\\  /\\  /  __/ | (_| (_) | | | | | |  __/\n"
        " \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___|\n"
        "                                                     \n"
        "                                                     \n");
    printf("to the treasure hunt game!\n\n");

    printf("You find yourself at the edge of a jungle with two paths:\n"
        "1. Through a dense thicket of thorns\n"
        "2. A clear, well-trodden path\n");
    currentState = MAIN_MENU;
}

int getUserChoice() {
    char ch;
    while (1) {
        if (_kbhit()) {
            ch = _getch();
            if (ch == 'b' || ch == 'B') {
                switch (currentState) {
                case MAIN_MENU:
                    mainMenu();
                    break;
                case CAVE_ENCOUNTER:
                    encounterCave();
                    break;
                case RIVER_ENCOUNTER:
                    encounterRiver();
                    break;
                case FOREST_ENCOUNTER:
                    encounterForest();
                    break;
                default:
                    printf("Invalid state.\n");
                    break;
                }
                continue; // Skip the rest of the loop to wait for next input
            }
            else if (ch == '1' || ch == '2' || ch == 's' || ch == 'S') {
                return ch; // Return the character for further processing
            }
            else {
                printf("Invalid input. Please enter 1 or 2, or 's' to play the secret game:\n");
            }
        }
    }
}

int main() {
    srand(time(0)); // seed random number generator

    mainMenu(); // Start by showing the main menu

    char choice = getUserChoice();

    if (choice == '1') {
        encounterCave();
    }
    else if (choice == '2') {
        int encounter = rand() % 2; // Randomly choose between river and forest
        if (encounter == 0) {
            encounterRiver();
        }
        else {
            encounterForest();
        }
    }
    else if (choice == 's' || choice == 'S') {
        SecretMain();
    }

    return 0;
}