/*
 * implementação do header: ../headerfiles/process_assicrono.h
 * detalhes das funções estão no header
*/

#include <stdlib.h>
#include "../headerfiles/process_assicrono.h"


void inicializeThreads(_mythread *threads, int qThread){
    
    int q;
    for(q = 0; q < qThread; q++){
        threads[q].processo = malloc(sizeof(pthread_t));
        threads[q].status = 1;
    }
}

_mythread *searchThread(_mythread *threads, int qThread){

    int i;
    for (i = 0; i < qThread; i++){
        if (threads[i].status >= 0){
            threads[i].status = -1;
            return &threads[i];
        }
    }
    return NULL;
}