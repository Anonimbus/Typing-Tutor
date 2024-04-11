#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>
#include "wordExtractor.h"

#define MAP_WIDTH 20
#define MAP_HEIGHT 20
#define CAR_WIDTH 3
#define CAR_HEIGHT 2

int carX, carY;
int obstacleX, obstacleY;
int score = 0;
bool gameOver = false;
char fallingWord[50];

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void drawMap() {
    int i, j;
    for (i = 0; i < MAP_HEIGHT; i++) {
        for (j = 0; j < MAP_WIDTH; j++) {
            if (i == 0 || i == MAP_HEIGHT - 1) {
                printf("-");
            } else {
                if (j == 0 || j == MAP_WIDTH - 1) {
                    printf("|");
                } else {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
}

void drawCar() {
    gotoxy(carX, carY);
    printf(" ^ ");
    gotoxy(carX, carY + 1);
    printf("|O|");
}

void clearCar() {
    gotoxy(carX, carY);
    printf("   ");
    gotoxy(carX, carY + 1);
    printf("   ");
}

void createObstacle() {
    char *wordPtr = getWord();
    strcpy(fallingWord, wordPtr);
}

void drawObstacle() {
    gotoxy(obstacleX, obstacleY);
    printf("%s", fallingWord);
}

void clearObstacle() {
    gotoxy(obstacleX, obstacleY);
    printf("   ");
}

void moveObstacle() {
    if (obstacleY >= MAP_HEIGHT - 2) { // Change the condition to check if the obstacle reaches the bottom of the map
        clearObstacle();
        gameOver = true; // Set gameOver flag to true
    } else {
        clearObstacle();
        obstacleY++;
    }
    drawObstacle();
}


void moveCar(int direction) {
    switch (direction) {
        case 'a':
            if (carX > 1) {
                clearCar();
                carX -= 2;
            }
            break;
        case 'd':
            if (carX < MAP_WIDTH - CAR_WIDTH - 1) {
                clearCar();
                carX += 2;
            }
            break;
    }
    drawCar();
}

bool checkCollision() {
    if (carX >= obstacleX - CAR_WIDTH && carX <= obstacleX + 2 && carY + CAR_HEIGHT - 1 == obstacleY) {
        return true;
    }
    return false;
}

void gameOverScreen() {
    system("cls");
    printf("Game Over!\n");
    printf("Your Score: %d\n", score);
    printf("Press any key to restart, or press Esc to exit...\n");

    char key;
    while (1) {
        if (kbhit()) {
            key = getch();
            if (key == 27) { // If Esc is pressed, exit the program
            	break;
            } else { // Otherwise, restart the game
                gameOver = false;
                score = 0;
                gameScreen();
            }
        }
    }
}


int gameScreen() {
    char key;
    carX = MAP_WIDTH / 2 - CAR_WIDTH / 2;
    carY = MAP_HEIGHT - CAR_HEIGHT - 1;

    srand(time(NULL));
    obstacleX = rand() % (MAP_WIDTH - 3) + 1;
    obstacleY = 1;

    system("cls");
    drawMap();
    drawCar();
    createObstacle(); // Initialize fallingWord

    gotoxy(0, MAP_HEIGHT + 3);
    printf("Controls: A - Move Left, D - Move Right, Esc - Quit\n");

    while (!gameOver) {
        if (kbhit()) {
            key = getch();
            if (key == 27) {
                break;
            }
            moveCar(key);
        }
        moveObstacle();
        if (checkCollision()) {
            gameOver = true;
        }
        gotoxy(0, MAP_HEIGHT + 4);
        printf("Score: %d", score);
        Sleep(200);
    }

    gameOverScreen();
    getch();
    return 0;
}

