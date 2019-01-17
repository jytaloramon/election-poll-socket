/*
 * implementação do header: ../headerfiles/printconsole.h
 * detalhes das funções estão no header
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headerfiles/format_printconsole.h"

void mensagem(char const *textsucess, char const *textfailed, int status){ 

    if (status < 0){
        printf("xxxxxxxxxxxxxx %s xxxxxxxxxxxxxx\n\n", textfailed);
        exit(0);
    }
    printf("++++++++++++++ %s ++++++++++++++\n\n", textsucess);
}

void printErro(char const *text, char const *erro){

    printf("      |-> Erro %s: %s\n\n", text, erro);
}

void printLog(int const *codigo, char const *solicitacao){

    printf("Cliente: %d  ==>  solicitação: %s\n", *codigo, solicitacao);
}

int parseInt(char const *test){

    int i, valor = 0, multiplicidade = 1;

    for (i = strlen(test) - 1; i >= 0; i--){
        valor += ((test[i] - 48) * multiplicidade);
        multiplicidade *= 10;
    }
    return valor;

}

char *parseRJSON(_candidato *vetCandi, int qtCandi, int max_buff, int *lengthT){

    char *js = malloc(sizeof(char) * max_buff);
    int i, pos = 0;

    for(i = 0; i < qtCandi; i++){
        transfString(js, vetCandi[i].id, &pos, ',');
        transfString(js, vetCandi[i].nome, &pos, ',');
        transfString(js, vetCandi[i].cargo, &pos, ',');
        transfString(js, vetCandi[i].partido, &pos, ',');
        transfString(js, vetCandi[i].sigla_patido, &pos, ',');
        transfString(js, vetCandi[i].qtVotos, &pos, ';');
    }
    js[pos++] = '\0';
    *lengthT = pos;

    return js;
}

void transfString(char *dest, char *palavra, int *posIniD, char separador){
    
    int i = 0;
    while(palavra[i] != '\0'){
        dest[(*posIniD)++] = palavra[i++];
    }
    if(separador != '\0')dest[(*posIniD)++] = separador;
}

char *queryFormat(char const *query, char const *valor){

    int i = 0, t = 0, v, tamQuery = strlen(query), tamValor = strlen(valor);
    char *newQuery = malloc(tamQuery + tamValor + 10);

    while(i < tamQuery){
        if (query[i] == '?'){
            v = 0;
            while(v < tamValor) newQuery[t++] = valor[v++];
            i++;
            continue;
        }
        newQuery[t++] = query[i++];
    }
    newQuery[t] = '\0';

    return newQuery;
}