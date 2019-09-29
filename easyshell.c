// C Program to design a shell in Linux 
#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<readline/readline.h> 
#include<readline/history.h> 
#include "ls.h"
  
#define MAXCOM 80 // número maximo de letras a serem suportadas 
#define MAXLIST 5 // numero maximo de comandos
  
// Clearing the shell using escape sequences 
#define clear() printf("\033[H\033[J") 
  
// Greeting shell during startup 
void init_shell() 
{ 
    clear(); 
printf("\n\n\n");
printf("EEEEEEE   AAA    SSSSS  YY    YY       SSSSS  HH   HH EEEEEEE LL      LL     \n");       
printf("EE       AAAAA  SS      YY   YY       SS      HH   HH EE      LL      LL     \n");      
printf("EEEEE   AA   AA  SSSSS   YYYYY         SSSSS  HHHHHHH EEEEE   LL      LL     \n");     
printf("EE      AAAAAAA      SS   YYY              SS HH   HH EE      LL      LL     \n");
printf("EEEEEEE AA   AA  SSSSS    YYY          SSSSS  HH   HH EEEEEEE LLLLLLL LLLLLLL\n");
                                                                                   
  
    printf("\n\n\n\n*************************************************************************"); 
    printf("\n\n\n\t****Bem vindo ao Easy Shell****"); 
    printf("\n\n\n\t****Atualizando arquivos****"); 
    printf("\n\n\n\t****configurando ambiente****"); 
    printf("\n\n\n\t****Espere alguns seculos****"); 
    printf("\n\n\t----> VirusScan - Windows found: Remove it? (Y/Y)"); 
    printf("\n\n\n\n*************************************************************************"); 
    char* username = getenv("USER"); 
    printf("\n\n\nUSER is: @%s", username); 
    printf("\n"); 
    sleep(1); 
    clear(); 
} 
  
// Receber input
int takeInput(char* str) 
{ 
    char* buf; 
    char* username = getenv("USER"); 
    
    printf("%s", username);
    buf = readline(" $ "); 
    if (strlen(buf) != 0) { 
        add_history(buf); 
        strcpy(str, buf); 
        return 0; 
    } else { 
        return 1; 
    } 
} 
  
// Function to print Current Directory. 
void printDir() 
{ 
    char cwd[1024]; 
    getcwd(cwd, sizeof(cwd)); 
    printf("%s\n", cwd); 
} 
  
// Function where the system command is executed 
void execArgs(char** parsed) 
{ 
    // Forking a child 
    pid_t pid = fork();  
  
    if (pid == -1) { 
        printf("\nFailed forking child.."); 
        return; 
    } else if (pid == 0) { 
        if (execvp(parsed[0], parsed) < 0) { 
            printf("\nCould not execute command.."); 
        } 
        exit(0); 
    } else { 
        // waiting for child to terminate 
        wait(NULL);  
        return; 
    } 
} 
  
  
// Help command builtin 
void openHelp() 
{ 
    puts("\n***WELCOME TO MY SHELL HELP***"
        "\nCopyright @ Suprotik Dey"
        "\n-Use the shell at your own risk..."
        "\nList of Commands supported:"
        "\n>cd"
        "\n>ls"
        "\n>exit"
        "\n>all other general commands available in UNIX shell"
        "\n>pipe handling"
        "\n>improper space handling"); 
  
    return; 
} 
  
// Function to execute builtin commands 
int ownCmdHandler(char** parsed) 
{ 
    int NoOfOwnCmds = 6, i, switchOwnArg = 0; 
    char* ListOfOwnCmds[NoOfOwnCmds]; 
    char* username; 
  
    ListOfOwnCmds[0] = "exit"; 
    ListOfOwnCmds[1] = "cd"; 
    ListOfOwnCmds[2] = "help"; 
    ListOfOwnCmds[3] = "hello";
    ListOfOwnCmds[4] = "pwd"; 
    ListOfOwnCmds[5] = "dir"; 
  
    for (i = 0; i < NoOfOwnCmds; i++) { 
        if (strcmp(parsed[0], ListOfOwnCmds[i]) == 0) { 
            switchOwnArg = i + 1; 
            break; 
        } 
    } 
  
    switch (switchOwnArg) { 
    case 1: 
        printf("\nGoodbye\n"); 
        exit(0); 
    case 2: 
        chdir(parsed[1]); //Chamada de sistema para mudança de repositorio.
        return 1; 
    case 3: 
        openHelp(); 
        return 1; 
    case 4: 
        username = getenv("USER"); 
        printf("\nHello %s.\nMind that this is "
            "not a place to play around."
            "\nUse help to know more..\n", 
            username); 
        return 1; 
    case 5: 
        printDir(); 
        return 1; 
    case 6:
        if(parsed[1] == NULL)         
            listDir(".");       
        else
            listDir(parsed[1]); 
        printf("\n");           
        return 1; 
    default:        
        break; 
    } 
  
    return 0; 
} 
  
  
// function for parsing command words 
void parseSpace(char* str, char** parsed) 
{ 
    int i; 
  
    for (i = 0; i < MAXLIST; i++) { 
        parsed[i] = strsep(&str, " "); 
  
        if (parsed[i] == NULL) 
            break; 
        if (strlen(parsed[i]) == 0) 
            i--; 
    } 
} 
  
int processString(char* str, char** parsed) 
{ 

    parseSpace(str, parsed); 
 
    if(ownCmdHandler(parsed) == 1)
        return 0;
    else
        return 1; 
 
} 
  
int main() 
{ 
    char inputString[MAXCOM], *parsedArgs[MAXLIST]; 
    int execFlag = 0; 
    init_shell(); 
  
    while (1) { 
        // Exibe o path do diretorio padrão
        //printDir(); 
        // take input 
        if (takeInput(inputString)) 
            continue; 
        // process 
        execFlag = processString(inputString, 
        parsedArgs); 
        // execflag returns zero if there is no command 
        // or it is a builtin command, 
        // 1 if it is a simple command 
        // 2 if it is including a pipe. 
  
        // execute 
        if(execFlag==1)
            execArgs(parsedArgs); 
  
    } 
    return 0; 
} 