#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>
#include "wordExtractor.h"

#define MAP_WIDTH 60
#define MAP_HEIGHT 20
#define TEXT_WIDTH 1
#define TEXT_HEIGHT 1

int textX=0,textY=0;
int obstacleX=0, obstacleY=0;
int xCopy=0,yCopy=0;
int cursorX,cursorY;
int score = 0;								//count the current score of the game
//int gameStatus=0;							//check if the player is out and start score from 0;
bool gameOver = false;
char fallingWord[50];
char destruction[50];

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
                    printf("|");											//previously here was border  printf("|")
                } else {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
}


void blowText()
{
	gotoxy(xCopy,yCopy);
	printf("                ");
	xCopy=obstacleX;
	yCopy=obstacleY;
}


void drawTextHolder() {
    gotoxy(0,MAP_HEIGHT + 3);
    printf("Enter the falling word : ");
    
//    new oneeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee/*************************************************************************************
	char b[100];
	fgets(b,strlen(fallingWord)+1,stdin);	
	if (strcmp(b,fallingWord)==0)
	{
        gotoxy(0, MAP_HEIGHT + 6);
		printf("you did it");
		score++;
		blowText();
		gameScreen();
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}


//void clearTextHolder() {
//    gotoxy(textX, textY);
//    printf("	");
//}



//void createObstacle() {
//    char *wordPtr = getWord();
//    strcpy(fallingWord, wordPtr);
//}
void createObstacle() {
    char *wordPtr = getWord();
    strcpy(fallingWord, wordPtr);

    // Adjust the obstacleX position to ensure the word stays within the border
    obstacleX = rand() % (MAP_WIDTH - strlen(fallingWord) - 2) + 1;
}



void drawObstacle() {
    // Clear previous positions of the falling word
    for (int i = 0; i < strlen(fallingWord); i++) {
        gotoxy(obstacleX + i, obstacleY);
        printf(" ");
    }
	xCopy=obstacleX;
	yCopy=obstacleY;
    // Draw the falling word at its current position
    gotoxy(obstacleX, obstacleY);
    printf("%s", fallingWord);
}
//void drawObstacle() {
//    int originalX, originalY;
//    CONSOLE_SCREEN_BUFFER_INFO csbi;
//    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
//    originalX = csbi.dwCursorPosition.X;
//    originalY = csbi.dwCursorPosition.Y;
//
//    gotoxy(obstacleX, obstacleY);
//    printf("%s", fallingWord);
//
//}

void moveObstacle() {
    if (obstacleY >= MAP_HEIGHT - 2) { // Change the condition to check if the obstacle reaches the bottom of the map
        blowText();
        gameOver = true; // Set gameOver flag to true
    } else {
//    	system("cls");
//    	drawMap();		//putting here also didn't work!
        blowText();
	    Sleep(20);        //Changing the speed of sleep will help in changing the falling speed of the word
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
    char *destroy = destructionWord();
    strcpy(destruction, destroy);
    printf("The word that %s you is : %s\n",destruction,fallingWord);  
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
    obstacleX = rand() % (MAP_WIDTH - 3) -8;
    obstacleY = 1;

    system("cls");
    drawMap();
    createObstacle(); // Initialize fallingWord

    gotoxy(0, MAP_HEIGHT + 4);
    printf("Esc - Quit\n");
    
    while (!gameOver) {
        if (kbhit()) {
            key = getch();
            if (key == 27) {
                break;
                //here i can add the pause screen!
            }
        }
        
        drawTextHolder();
        
        moveObstacle();
        if (checkCollision()) {
            gameOver = true;
        }
        gotoxy(0, MAP_HEIGHT + 5);
        printf("Score: %d", score);
//        Sleep(200); 							//Hawa jasto ya sleep hanera kasari hunxa!!
    }

    gameOverScreen();
    getch();
    return 0;
}
