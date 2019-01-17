/* ####### Importação de libs e headers ####### */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

/* ####### Config do Servidor ####### */
#define PORTSERVER 3059
#define IPSERVER "10.0.0.190"
#define LENGTH_FILES 4096 //Tamanho da max mensagem

typedef struct _candidato{
    char id[15],
        nome[45],
        url_foto[256],
        cargo[35],
        partido[65],
        sigla_patido[15],
        qtVotos[10];
}_candidato;

/* ####### Protótipos de função ####### */
void inicializeConfigServe(struct sockaddr_in *serv, int *status); // Inicaliza socket servidor
void mensagem(char const *textsucess, char const *textfailed, int status, int valueErro); // Print resultado da operação
void printes(_candidato *candis, int qt); // print na tela as informações 
int veryfStatus(char const *text, char const *textfalha); // Verifica se a solicitação foi feita com sucesso
_candidato *RJsonDescriptor(char const *rjson, int *qtOb); // Converte array RJson em vetor candidato
_candidato separator(char const *string); // Converte String em um candidato

int main(int argc, char const *argv[]){

    // Variveis
    int conexao, conc, opcao;
    char *msgrecv, tarefa[][10] = {"0\n", "1\n"}, idCand[10];

    while(1){

        struct sockaddr_in servidor; // Alocando socket servidor 
        inicializeConfigServe(&servidor, &conexao); //Inicializando conexão
        msgrecv = malloc(sizeof(char) * LENGTH_FILES);

        conc = connect(conexao, (struct sockaddr *)&servidor, sizeof(servidor));                           // Conectando ao socket
        mensagem("Vc estar conectado com o servidor", "Erro ao tentar conectar com o servidor", conc, -1); // Vereficando se a conexão foi feita

        printf("[1] Ver Candidatos\n[2] Votar\n[3] Sair\nDigite => ");
        scanf("%d", &opcao);

        switch(opcao){

            case 1:{
                recv(conexao, msgrecv, LENGTH_FILES, 0);
                if(!veryfStatus(msgrecv, "404-\0")){
                    send(conexao, tarefa[0], strlen(tarefa[0]), 0);
                    recv(conexao, msgrecv, LENGTH_FILES, 0);
                }

                int quantidade;

                _candidato *candis = RJsonDescriptor(msgrecv, &quantidade);

                printes(candis, quantidade);

                break;
            } 

            case 2:{
                printf("Digite o ID do candidato: ");
                scanf("%s", idCand);

                recv(conexao, msgrecv, LENGTH_FILES, 0);
                
                if(!veryfStatus(msgrecv, "404-\0")){
                    send(conexao, tarefa[1], strlen(tarefa[0]), 0);
                    send(conexao, idCand, strlen(idCand), 0);;
                    recv(conexao, msgrecv, LENGTH_FILES, 0);
                }

                printf("\n##############    %s    #################\n\n", msgrecv);

                break;
            } 

            case 3:{
                exit(0);
                break;

            } 
            
            default:{
                printf("Digite uma opcao valida!\n");
            }
        }
        free(msgrecv);
    }
    
    return 0;
}

/* Implementação de Funções */
void inicializeConfigServe(struct sockaddr_in *serv, int *status){

    *status = socket(AF_INET, SOCK_STREAM, 0);
    mensagem("Socket criado com sucesso!", "Nao foi possivel criar o socket!", *status, 0);

    serv->sin_family = AF_INET;
    serv->sin_port = htons(PORTSERVER);
    serv->sin_addr.s_addr = inet_addr(IPSERVER);
}

void mensagem(char const *textsucess, char const *textfailed, int status, int valueErro){
    if(status <= valueErro){
        printf("xxxxxxxxxxxxxx %s xxxxxxxxxxxxxx\n\n", textfailed);
        exit(0);
    }
}

int veryfStatus(char const *text, char const *textfalha){
    int i = 0;

    while(textfalha[i] != '\0'){
        if(text[i] != textfalha[i]){
            return 0;
        }
        i++;
    }
    return 1;
}

_candidato *RJsonDescriptor(char const *rjson, int *qtObj){

    int i = 0, ca = 0, j = 0;
    char aux[15][200];
    _candidato *cand;

    while(rjson[i] != '\0'){
        if(rjson[i] != ';') aux[ca][j++] = rjson[i];
        else{
            aux[ca++][j] = '\0';
            j = 0;
        }
        i++;
    }

    cand = malloc(sizeof(_candidato) * ca);

    for(i = 0; i < ca; i++){
        cand[i] = separator(aux[i]);
    }

    *qtObj = ca;

    return cand;
}

_candidato separator(char const *string){

    int i = 0, camp = 0, t = 0, q = 0;
    char campos[6][50];
    _candidato *cand = malloc(sizeof(_candidato));

    while(string[i] != '\0'){
        if(string[i] != ','){
           campos[t][q++] = string[i];
        } else{
            campos[t++][q] = '\0';
            q = 0;
        }
        i++;
    }
    campos[t][q] = '\0';

    strcpy(cand->id, campos[0]);
    strcpy(cand->nome, campos[1]);
    strcpy(cand->cargo, campos[2]);
    strcpy(cand->partido, campos[3]);
    strcpy(cand->sigla_patido, campos[4]);
    strcpy(cand->qtVotos, campos[5]);

    return *cand;
}

void printes(_candidato *candis, int qt){

    int i = 0;
    printf("\n\n    ID    ");
    printf("|   Nome   ");
    printf("|   Cargo   ");
    printf("|   Partido   ");
    printf("|   Votos   \n\n");
    
    for(i = 0; i < qt; i++){
        printf("    %s  ", candis[i].id);
        printf("      %s  ", candis[i].nome);
        printf("    %s  ", candis[i].cargo);
        printf("    %s  ", candis[i].sigla_patido);
        printf("           %s\n\n", candis[i].qtVotos);
    }
}
