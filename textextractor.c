#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

char* getPhrase(){
    srand(time(NULL));//giving seed for rand() function

    FILE* fp=fopen("text.txt","r");

    int lineNo =rand()%100;
    char* line=(char*)malloc(100*sizeof(char));// allocate space for 100 character(same as string)

    strcpy(line,"");
    char ch[2];

    for(int i=0;i<lineNo;i++){
        strcpy(line,"");
        while(1){
            ch[0]=fgetc(fp);
            if(ch[0]=='\n'){
                break;
            }
            strcat(line,ch);
            //printf("%c",ch);
        }
        strcat(line,"\0");
    }

    return line;
}