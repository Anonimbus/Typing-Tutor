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

// int textX=0,textY=0;						//to store the current position of text we are writing.
int obstacleX=0, obstacleY=0;
int xCopy=0,yCopy=0;
int lp=0;
int score = 0;								//count the current score of the game
int lenWord;
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
    for (int i = 0; i < lenWord; i++) {
        printf(" ");
	}
	xCopy=obstacleX;
	yCopy=obstacleY;
}


void drawTextHolder() {
    gotoxy(0,MAP_HEIGHT + 3);
    printf("Enter the falling word : ");
    

    //CODE TO GIVE THE POSISION OF THE CURSOR CURRENTLY
    // {

    //     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //     CONSOLE_SCREEN_BUFFER_INFO csbi;
        
    //     // Get the console screen buffer information
    //     if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
    //         // Print the current cursor position
    //         printf("Current Cursor Position: X=%d, Y=%d\n", csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y);
    //     } else {
    //         printf("Failed to get console screen buffer information.\n");
    //     }

    // }
    
    
	char b[100];
    for (lp;b[lp]!='\0';lp++)
    {
    gotoxy(25+lp,MAP_HEIGHT+3);
	b[lp] = _getch();
    }
    if(strcmp)

    
	if (strcmp(b,fallingWord)==0)
	{
        gotoxy(0, MAP_HEIGHT + 6);
		printf("you did it");
        lp=0;
		score++;
		blowText();
		gameScreen();
	}
}

/*****************************************************OBSTACLE/WORD PROPERTIES********************************************************/

void createObstacle() {
    char *wordPtr = getWord();
    strcpy(fallingWord, wordPtr);
	lenWord=strlen(fallingWord);
    // Adjust the obstacleX position to ensure the word stays within the border
    obstacleX = rand() % (MAP_WIDTH - strlen(fallingWord) - 2) + 1;
}



void moveObstacle() {
    if (obstacleY >= MAP_HEIGHT-2) { // Change the condition to check if the obstacle reaches the bottom of the map
        blowText();
        gameOver = true; // Set gameOver flag to true
    } else {
        blowText();                                                         //clearing the previous text
        obstacleY++;

        xCopy=obstacleX;
        yCopy=obstacleY;
        // Draw the falling word at its current position
        gotoxy(obstacleX, obstacleY);
        printf("%s", fallingWord);	                                        //printing the falling word

        Sleep(200);        //Changing the speed of sleep will help in changing the falling speed of the word
    }
}

/*****************************************************THE GAME OVER SCREEN********************************************************/
void gameOverScreen() {
    system("cls");
    printf("Game Over!\n");
//    char *destroy = destructionWord();
//    strcpy(destruction, destroy);																//something went wrong! it sometime works
//    printf("The word that\t %s you is : %s\n",destruction,fallingWord);
	printf("Your Score: %d\n", score);
    printf("Press any key to restart, or hold Esc to exit...\n");

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

    srand(time(NULL));
    obstacleX = rand() % (MAP_WIDTH - 3) -8;        //the word with max length is 16 may cause some trouble if spawned in right side
    obstacleY = 1;

    system("cls");
    drawMap();
    createObstacle(); // Initialize fallingWord
    
    while (!gameOver) {
                
        drawTextHolder();
        
        moveObstacle();

        gotoxy(0, MAP_HEIGHT + 5);
        printf("Score: %d", score);
    }

    gameOverScreen();
    return 0;
}