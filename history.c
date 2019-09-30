#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<readline/readline.h>
#include<readline/history.h>
#include <string.h>

#include "intcmds.h"


void puthistory(char* buf){
    add_history(buf); 
}
void history(char* flag){
    int count = 0;
    char f[4] = "-p";

    HISTORY_STATE *myhist = history_get_history_state();
    HIST_ENTRY **mylist = history_list();
    
    if(flag!=NULL){
        if(strcmp(flag,f) == 0){
            for (int i; i < myhist->length-1; i++) { /* output history list */
                free_history_entry (mylist[i]);     /* free allocated entries */   
            }
        }
    }
    else{
        int i = myhist->length;
        if(i > 30)
            i = i-30;
        else
            i=0;
        for (i; i < myhist->length-1; i++) { /* output history list */
            printf ("%d  %s  %s\n",count, mylist[i]->line, mylist[i]->timestamp);
            count++;
        //  free_history_entry (mylist[i]);     /* free allocated entries */

            if(count == 30)
                break;
        }

    }


    return;

}