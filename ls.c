#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#include "intcmds.h"


void listDir(char* dirName){

   DIR* dir;

   printf(dirName);

   struct dirent *dirEntry;

   struct stat inode;

   char name[1000];

   dir = opendir(dirName);

    if (dir == 0) {

        perror ("Erro ao abrir arquivo");

        exit(1);

    }

    while ((dirEntry=readdir(dir)) != 0) {

        sprintf(name,"%s/%s",dirName,dirEntry->d_name); 

        lstat (name, &inode);

        printf(" %s   ", dirEntry->d_name);

     

       // Tipo do arquivo

      /*   if (S_ISDIR(inode.st_mode))

            printf("dir ");

        else if (S_ISREG(inode.st_mode))

                printf ("arquivo ");

        else

            if (S_ISLNK(inode.st_mode))

                printf ("link ");

            else;

                printf(" %s   ", dirEntry->d_name); */

    }
}