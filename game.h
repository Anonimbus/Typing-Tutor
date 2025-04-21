#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "wordExtractor.h"
#ifdef _WIN32
    #include <conio.h>    // for getch()
    #include <windows.h>  // for system("cls")


    void gotoxy(int x, int y) {												//function to move the cursor to the given position
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        #define SleepMS(ms) Sleep(ms)
    }

#else
    #include <termios.h>
    #include <unistd.h>
    int getch(void) {
        struct termios oldattr, newattr;
        int ch;
        tcgetattr(STDIN_FILENO, &oldattr);              // get current terminal attributes
        newattr = oldattr;
        newattr.c_lflag &= ~(ICANON | ECHO);            // disable buffering & echo
        tcsetattr(STDIN_FILENO, TCSANOW, &newattr);     // set new attributes
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);     // restore old attributes
        return ch;
    }

    void gotoxy(int x, int y) {
        printf("\033[%d;%dH", y, x);  // ANSI escape code to move cursor
    }
    #define SleepMS(ms) usleep((ms) * 1000)  // Convert to microseconds
    
#endif

void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}


#define MAP_WIDTH 60
#define MAP_HEIGHT 20
#define TEXT_WIDTH 1
#define TEXT_HEIGHT 1

// int textX=0,textY=0;						//to store the current position of text we are writing.
int obstacleX=0, obstacleY=0;
int xCopy=0,yCopy=0;
int lp=0;
int score = 0;								//count the current score of the game
int lenWord=0;
bool gameOver = false;
char fallingWord[50];
char destruction[50];
char b[100];


// Function prototype for gameScreen
int gameScreen();						
//added because the error:[Warning] implicit declaration of function 'gameScreen'; did you mean 'gameOverScreen'? [-Wimplicit-function-declaration]

// ******************************************************************REST OF THE CODE*******************************************************************************


void drawMap() {														//draws the game area border; it also provides a base for gameOver condition
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


void blowText() {														//clears out the previous instance of fallingWord
	gotoxy(xCopy,yCopy);
    for (int i = 0; i < lenWord; i++) {
        printf(" ");
	}
	xCopy=obstacleX;
	yCopy=obstacleY;
}


void drawTextHolder() {													//the location where the user inputs the fallingWord
    gotoxy(0,MAP_HEIGHT + 3);
    printf("Enter the falling word : ");
    

    //CODE TO GIVE THE CURRENT POSITION OF THE CURSOR
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
    
    
        gotoxy(25+lp,MAP_HEIGHT+3);                     //here 25 is the length of the string""
        b[lp] = getch();

            if (b[lp] == 27) 
                gameOver=true;
            else if (b[lp] == 13)
            {
                gotoxy(0,MAP_HEIGHT+4);
                printf("hello hurrah burrah");
                b[lp]='\0';
                printf("the length of falling word is : %zu ", strlen(fallingWord) );
                printf("the length of entered word is : %zu ", strlen(b));                  //here the length of fallingWord and b is not same!!! #most imp concern
                if (strcmp(b,fallingWord)==0) {
                    gotoxy(0, MAP_HEIGHT + 6);
                    printf("you did it");
                    SleepMS(2000);
                    lp=0;
                    score++;
                    // blowText();
                    gameScreen();
                }
                else {
                    lp=0;
                    gotoxy(25,MAP_HEIGHT+3);
                    printf("                        ");
                    memset(b, '\0', sizeof(b));                                     //now this cleared all the memory and didn't let it fill 
                }
            }
        printf("%c",b[lp]);
        lp++;
}

// *****************************************************OBSTACLE/WORD PROPERTIES********************************************************

void createObstacle() {                                                 //selects a word from file and generates a X-spawn location of word
    char *wordPtr = getWord();
    strcpy(fallingWord, wordPtr);
	lenWord=strlen(fallingWord);
    // Adjust the obstacleX position to ensure the word stays within the border
    obstacleX = rand() % (MAP_WIDTH - strlen(fallingWord) - 2) + 1;
}



void moveObstacle() {                                                   //tests if reached bottom
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
        // drawTextHolder();
        SleepMS(200);        //Changing the speed of sleep will help in changing the falling speed of the word
    }
}

// ****************************************************THE GAME OVER SCREEN********************************************************
void gameOverScreen() {
    clear_screen();
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
            	break;
            } else {						// Otherwise, restart the game
                gameOver = false;
                score = 0;
                gameScreen();
            }
        }
    }
}


// *******************************************************THIS IS OUR MAIN SCREEN***************************************************

int gameScreen() {
    char key;

    srand(time(NULL));
    obstacleX = rand() % (MAP_WIDTH - 3) -8;        //the word with max length is 16 may cause some trouble if spawned in right side
    obstacleY = 1;

    clear_screen();
    drawMap();
    createObstacle(); // Initialize fallingWord
    
    while (!gameOver) {
                
        gotoxy(0, MAP_HEIGHT + 5);
        printf("Score: %d", score);

        moveObstacle();
        drawTextHolder();
    }

    gameOverScreen();
    return 0;
}

// int main(){
//     gameScreen();
//     return 0;
// }