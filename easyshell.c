// C Program to design a shell in Linux 
#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<readline/readline.h> 
#include<readline/history.h> 

#include "intcmds.h"
  
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
    char ps1[1024];
    char* username = getenv("USER"); 
    getcwd(ps1, 1024); 
    strcat(ps1, "@");
    strcat(ps1,username);

 
    
    printf("%s", ps1);
    buf = readline(" $ "); 
    if (strlen(buf) != 0) { 
        puthistory(buf);
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
        printf("\nO fork falhou"); 
        return; 
    } else if (pid == 0) { 
        if (execvp(parsed[0], parsed) < 0) { 
            printf("\nNao pode executar o programa\n"); 
        } 
        exit(0); 
    } else { 
        // esperando o processo do filho terminar. 
        wait(NULL);  
        return; 
    } 
} 
  
  
// Function to execute builtin commands 
int ownCmdHandler(char** parsed, char **envp) 
{ 
    int NoOfOwnCmds = 9, i, switchOwnArg = 0; 
    char* ListOfOwnCmds[NoOfOwnCmds]; 
    char* username; 
  
    ListOfOwnCmds[0] = "exit"; 
    ListOfOwnCmds[1] = "cd"; 
    ListOfOwnCmds[2] = "help"; 
    ListOfOwnCmds[3] = "hello";
    ListOfOwnCmds[4] = "pwd"; 
    ListOfOwnCmds[5] = "dir"; 
    ListOfOwnCmds[6] = "history"; 
    ListOfOwnCmds[7] = "echo"; 
    ListOfOwnCmds[8] = "declare"; 
    ListOfOwnCmds[9] = "unset"; 
  
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
       if (chdir(parsed[1]) != 0 && parsed[1] != NULL)
            perror("error "); 
        else
            chdir(parsed[1]); //Chamada de sistema para mudança de repositorio.
        return 1; 
    case 3: 
        openHelp(); 
        return 1; 
    case 4: 
        username = getenv("USER"); 
        printf("\nOla %s.\n Seja Bem vindo!", username); 
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
    case 7: 
        history(parsed[1]); 
        return 1; 
    case 8: 
        printf("%s\n", parsed[1]);
        return 1; 
    case 9: 
        setvar(parsed[1]); 
        return 1; 
    case 10: 
        unsetvar(parsed[1]); 
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
  
int processString(char* str, char** parsed, char **envp) 
{ 

    parseSpace(str, parsed); 
 
    if(ownCmdHandler(parsed, envp) == 1)
        return 0;
    else
        return 1; 
 
} 
  
int main(int argc, char **argv, char **envp) 
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
        parsedArgs, envp); 
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