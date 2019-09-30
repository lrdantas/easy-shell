#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>



void getvar(char* var){
    char* env; 
    env = getenv(var);                  
    if(env == NULL){
        perror("getenv");
        return;
    }                       //error ao consultar variavel        
    else
        printf("%s", env);
    return;
}

void setvar(char* var){
    const char c[2] = "=";
    char *env;
    char *value;
    char *str;

    str = strdup (var);

    env = strsep (&str, c);   
    value = strsep (&str, c);    

    int i = setenv(env, value, 1);
    if(i != -1)
        return;
    else
        perror("error ");
    return;
}

void unsetvar(char* var){
    int i = unsetenv(var);
    if(i != -1)
        return;
    else
        perror("error ");
    return;
}

void listenvs(char **envp){
    for (char **env = envp; *env != 0; env++)
  {
    char *thisEnv = *env;
    printf("%s\n", thisEnv);    
  }
  return;
}