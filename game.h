#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>
#include "wordExtractor.h"

#define MAP_WIDTH 20
#define MAP_HEIGHT 20
#define TEXT_WIDTH 1
#define TEXT_HEIGHT 1

int textX=0,textY=0;
int obstacleX=0, obstacleY=0;
int score = 0;
bool gameOver = false;
char fallingWord[50];

// Function prototype for gameScreen
int gameScreen();						
//added because the error:[Warning] implicit declaration of function 'gameScreen'; did you mean 'gameOverScreen'? [-Wimplicit-function-declaration]

/******************************************************************REST OF THE CODE*******************************************************************************/

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



void drawTextHolder() {
    gotoxy(textX, textY);
    printf("Enter the falling word : ");
}



void clearTextHolder() {
    gotoxy(textX, textY);
    printf("	");
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
//    drawMap();						tried to draw the map again but failed! :(
    printf("	");
}



void moveObstacle() {
    if (obstacleY >= MAP_HEIGHT - 2) { // Change the condition to check if the obstacle reaches the bottom of the map
        clearObstacle();
        gameOver = true; // Set gameOver flag to true
    } else {
//    	system("cls");
//    	drawMap();		//putting here also didn't work!
        clearObstacle();
	    Sleep(200);        //Changing the speed of sleep will help in changing the falling speed of the word
	    drawObstacle();
        obstacleY++;
    }
}



bool checkCollision() {
    if (textX >= obstacleX - TEXT_WIDTH && textX <= obstacleX + 2 && textY + TEXT_HEIGHT - 1 == obstacleY) {
        return true;
    }
    return false;
}


/*****************************************************THE GAME OVER SCREEN********************************************************/
void gameOverScreen() {
    system("cls");
    printf("Game Over!\n");
    printf("Your Score: %d\n", score);
    printf("Press any key to restart, or press Esc to exit...\n");

    char key;
    while (1) {
        if (kbhit()) {
            key = getch();
            if (key == 27) { 				// If Esc is pressed, exit the game		but for some reason we have to press esc twice
//            	return 404;
            	break;
            } else {						// Otherwise, restart the game
                gameOver = false;
                score = 0;
                gameScreen();
            }
        }
    }
}


/*******************************************************THIS IS OUR MAIN SCREEN***************************************************/
int gameScreen() {
    char key;
//    carX = MAP_WIDTH / 2 - CAR_WIDTH / 2;
//    carY = MAP_HEIGHT - CAR_HEIGHT - 1;
    textX = 100;
    textY = 100;

    srand(time(NULL));
    obstacleX = rand() % (MAP_WIDTH - 3) + 1;
    obstacleY = 1;

    system("cls");
    drawMap();
    drawTextHolder();
    createObstacle(); // Initialize fallingWord

    gotoxy(0, MAP_HEIGHT + 3);
    printf("Controls: A - Move Left, D - Move Right, Esc - Quit\n");

    while (!gameOver) {
        if (kbhit()) {
            key = getch();
            if (key == 27) {
                break;
                //here i can add the pause screen!
            }
        }
        moveObstacle();
        if (checkCollision()) {
            gameOver = true;
        }
        gotoxy(0, MAP_HEIGHT + 4);
        printf("Score: %d", score);
//        Sleep(200); 							//Hawa jasto ya sleep hanera kasari hunxa!!
    }

    gameOverScreen();
    getch();
    return 0;
}
