#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include<conio.h>
#include "textextractor.c"
#include  "game.h"


#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

void timeisgreat();
void drill();
void regular();
void typingGame();
void typringSc(char *text);
char *randLine(char *str);

int main()
{
op:
    do
    {
        system("cls");

        int options;

        printf("Choose your option\n");
        printf("1. Typing practise with short sentences\n");
        printf("2. Typing Drill\n");
        printf("3. Typing Game\n");
        printf("4. Typing Test (limited time)\n\n");
        scanf("%d", &options);
        switch (options)
        {
        case 1:
            regular();
            break;
        case 2:
            drill();
            break;
        case 3:
            typingGame();
            break;
        default:
            printf("Invalid option");
            // Sleep(2);
        }
    } while (1);
}

void regular()
{
    do
    {
        char text[1000] = "";

        strcpy(text, getPhrase()); // getPhrase() returns a random text for typing

        typringSc(text);
        char deci =_getch();

        if (deci == 27)
            break;
    } while (1);
}

void typringSc(char *text)// this function takes a text and does all the functions while typing
	{
	    system("cls");
	
	    int start_time, end_time;
	
	    int i = 0, wordcnt = 0;
	
	    // Total Word Counter //
	    for (i = 0; text[i] != '\0'; i++)
	    {
	        if (text[i] == 32)
	            wordcnt++;
	    };
	    wordcnt = wordcnt + 1;
	    //////////////////////////               wordcnt counts total words in the text
	
	    ////////////// character Counter //////
	    for (i = 0; text[i] != '\0'; i++)
	        ;
	    i--;
	    int textcnt = 0;
	    //////////////////////////              Total characters in the text stored in i
	
	    char a;
	    int err = 0;
	    int check = 0;
	
	    printf("%s\n\n%s\r", text, text);
	
	    do
	    {
	        a = getch();
	
	        if (a != 13)
	        {
	            if (check == 0)
	                start_time = time(NULL);
	
	            check = 1;
	
	            if (a == 13)
	                break;
	
	            if (a == 8)
	            {
	                textcnt--;
	                printf("\b");
	                continue;
	            }
	
	            if (text[textcnt] == a)
	                printf(ANSI_COLOR_GREEN "%c" ANSI_COLOR_RESET, a);
	            else
	            {
	                printf(ANSI_COLOR_RED "%c" ANSI_COLOR_RESET, text[textcnt]);
	                err++;
	            }
	            textcnt++;
	        }
	    } while (textcnt <= i);
	
	    end_time = time(NULL);
	
	    float timediff = (end_time - start_time) / 60.0;
	    float speed = ((float)(i) / (5.0 * timediff)) - ((float)err / timediff);
	
	    if (speed < 0.0)
	        speed = 0.0;
	
	    printf("\n\nAverage typing speed : %.2f WPM", speed);
	
	    float acc = (((float)i - (float)err) / (float)i) * 100;
	
	    printf("\nAccuracy of typing is %.2f\n\n", acc);
	    printf("\x1b[34m");
	    printf("\n\n Want to close ? Hit esc\n\n");
	    printf("\x1b[0m");
	}
	
void typingGame()
	{
		gameScreen();
	}


void drill()
	{
	    char *charc = (char*)calloc(26, sizeof(char));
	    printf("Enter characters you want to drill\n");
	    scanf("%s",charc);
	    strtok(charc, "\n");
	
	    char text[51] = "";
	    while (1)
	    {
	        strcpy(text, randLine(charc));
	        //printf("%s",text);
	        typringSc(text);
	
	        char deci = _getch();
	
	        if (deci == 27)
	            break;
	    }
	}

char *randLine(char *str)
	{
	    int n = 0;
	    time_t t1;
	    srand(time(&t1));
	
	    char *line = (char *)calloc(50, sizeof(char));//creates memory space of 50 characters and initializes to 0
	    //printf("%s\n",str);
	
	    //copies random characters for str and creates random spaces in between
	    for (int i = 0; i < 50; i++)
	    {
	        do{
	            n = rand() % 26;
	        }while(str[n]==0);
	
	        if(n%3==0){
	            line[i]='\0';
	            continue;
	        }
	        line[i] = str[n];
	    }
	    ////
	
	    //we convert null character to space
	    for (int i = 0; i < 50; i++)
	    {
	        if (line[i] == '\0')
	        {
	            line[i] = 32;
	        }
	    }
	    //////
	
	    //printf("\n%s\n",line);
	
	    ///if there are two consecutive spaces, we fill a space with random character from str
	    for (int i = 0; i < 50; i++)
	    {
	        if (line[i] == 32 && line[i + 1] == 32)
	        {
	            do
	            {
	                n = rand() % 26;
	            } while (str[n] == 0);
	
	            line[i] = str[n];
	        }
	    }
	    return line;
	}