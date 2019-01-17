/*
 * implementação do header: ../headerfiles/format_printconsole.h
 * detalhes da funções estão no header
*/

#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../headerfiles/inicializedefault.h"
#include "../headerfiles/format_printconsole.h"


void inicializeConfigServe(struct sockaddr_in *serv, char const *ipserver, int portaserver, int *status){ 

    *status = socket(AF_INET, SOCK_STREAM, 0);
    mensagem("Socket criado com sucesso!", "Nao foi possivel criar o socket!", *status);

    serv->sin_family = AF_INET;
    serv->sin_port = htons(portaserver);
    serv->sin_addr.s_addr = inet_addr(ipserver);
}

_requisicao *inicializeRequisicao(char const (*nome)[LENGTH_NOP], int qt){

    int i;
    _requisicao *vetrequi = malloc(sizeof(_requisicao) * qt);

    for(i = 0; i < qt; i++){
        vetrequi[i].id = i;
        strncpy(vetrequi[i].nome, nome[i], LENGTH_NOP);
    }

    return vetrequi;
}

void resetConfigClient(struct sockaddr_in *clienTemp, int *connectClien){

    clienTemp = malloc(sizeof(struct sockaddr_in));
    *connectClien = -1;
}