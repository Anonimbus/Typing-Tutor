#include <stdio.h>    // standard input output
#include <time.h>     // time(NULL)
#include <stdlib.h>   // rand() 
#include  "game.c"	  // custom header for game

#define RED printf("\x1b[31m");
#define YELLOW printf("\x1b[33m");
#define BLUE printf("\x1b[34m");
#define GREEN printf("\x1b[32;1m");
#define RESET printf("\x1b[0m");

//_____________________________________________________________________________________________________________________________
int totalLines()   // calculates total lines of texts in the file named text.txt . allows for unlimeted addition of random text by the user
                   
{
    FILE *FP;
    FP = fopen("text.txt","r");
    char op[2];
    int bsncnt = 0;
    do
    {
        op[0] = fgetc(FP);
        if(op[0] ==  10)
            bsncnt++;
    }while(op[0] != EOF);
    return (bsncnt + 1);
}

void Headmaster(char text[1000])// this function takes a text and does all the functions while typing
{
    system("cls");
    int start_time, end_time;
    int i;
    int textcnt = 0;

    for (i = 0; text[i] != '\0'; i++); // Length of text
  
    char a;
    int err = 0;
    int check = 0;

    printf("%s\n\n%s\r", text, text);
  
  
    do
    {
        a = getch();
        
        if (a != 13)
        {
            if (check == 0)                 // For start counting time just after the user hits any key
                start_time = time(NULL);

            check = 1;                      // Makes sure the user already pressed key
           

            if (a == 8)                     // For backspace (Not necessary after the latest update but doen't harm code either)
            {
                textcnt--;
                printf("\b");
                continue;
            }

            if (text[textcnt] == a)          // If the typed character by the user is correct
            {
            GREEN
                printf("%c", a);
            RESET
            }
            else                    // If the typed character is not correct
            {
                RED
                printf("%c", text[textcnt]);
                printf("\b");
                do {}while (getch() != text[textcnt]);                
                RESET
                YELLOW
                printf("%c",text[textcnt]);
                RESET
                err++;
            }
            textcnt++;
        }
    } while (textcnt < i);
    end_time = time(NULL);
//_______________________________________________--_--______________________________________________________________________
    
    float wordsH = (float)i / (float)5;
    float timediff = (end_time - start_time) / 60.0;
    
    float speed = ( wordsH )/ timediff;
    float acc = (((float)i - (float)err) / (float)i) * 100;
    
    if (speed < 0.0) speed = 0.0;

    
    FILE *FP;
    FP = fopen("Score.txt","a");

    printf("\n\nAverage typing speed : %.2f WPM", speed);
    printf("\nAccuracy of typing is %.2f\n\n", acc);
            
            
    fprintf(FP, "Speed : %.2f ; Acc %.2f\n", speed, acc);
    fclose(FP);
 
 
  BLUE
    printf("\n\n Want to close ? Hit esc\n\n");
  RESET
//_____________________________________________________________________________________________________________________
}

void RandomSentence(char text[1000]) // This function provides random sentences extrating from file named text.txt
{
       
    int textcnt = 0;
    srand(time(NULL));                  // Seed the rand function to get new no each time 
    int lineNo = rand()%totalLines();
    FILE* fp=fopen("text.txt","r");
    
    char ch[2]={'\0','\0'};
    int bscnt=0, check =1;

          do{


            ch [0] = fgetc(fp);
            //printf("%s",ch);
            
            if(ch[0] == 10)
             { 
                if(check == 1)
                { bscnt ++;
                 continue;
                }
                else
                 break;
              }
              
            if((bscnt+1) == lineNo)
            {      
            check = 0;   
            text [textcnt] = ch[0];
            textcnt ++;
            }

            } while(ch[0] != EOF);
    text[textcnt]='\0';
    fclose(fp);
}

void TypingTest()
{       do{
        char text[1000] = "";
        RandomSentence(text); // Fills Text with characters
        Headmaster(text);
        }while(getch()!= 27);
}

void drill()
{ 
   system("cls");
   char charc[100]="";
   printf("Enter characters you want to Practise with :\n");
   scanf("%99s",charc);
   int space;
       do{ 
   for(space = 0; charc[space] !='\0';space++);
    srand(time(NULL));   
    char text[1000] = "";
    int textcnt = 0;
    int ab;
    int spacebar=0;
    //printf("%d",space);
    while (textcnt<30)
    {  
        spacebar ++;
        if(spacebar == 4)
        {
            text[textcnt] = ' ';
            textcnt++;
            spacebar  = 0;
        }
        ab = rand() % space;
        text[textcnt] = charc[ab];
        textcnt++;
    }   

        Headmaster(text);
    }while(getch() != 27);
}

int main()
{
    FILE *FP;
    FP = fopen("Score.txt","r");
    if(FP == NULL)
    {
        fclose(FP);
        FILE *FP;
        FP = fopen("Score.txt","w");
        fclose(FP);
    }
op:
    do
    {
        system("cls");

        int options;
        YELLOW
        printf("Choose your option\n");
        RESET
        printf("0. Exit\n");
        printf("1. Typing practise with short sentences\n");
        printf("2. Typing Drill\n");
        // printf("3. Typing Game\n");
        scanf("%d", &options);
        switch (options)
        {
            case 0:
                return 0;
            case 1:
                TypingTest();
                break;
            case 2:
                drill();
                break;
            default:
                printf("Invalid option\n\n");
                SleepMS(1000);
        }
    } while (1);
}
//_____________________________________________________________________________________________________________________________
