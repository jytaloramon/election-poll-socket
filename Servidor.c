// Para compilar user o comando: gcc -L/usr/lib/mysql -lmysqlclient -pthread implementsHeaders/*.o Servidor.c -o servidor

/* ####### Importação de libs e headers ####### */
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include "headerfiles/format_printconsole.h"
#include "headerfiles/inicializedefault.h"
#include "headerfiles/database.h"
#include "headerfiles/process_assicrono.h"

/* ####### Config do Servidor ####### */
#define PORTSERVER 3059 
#define IPSERVER "10.0.0.190" // Ip da maquina ou localhost: 127.0.0.1
#define LENGTH_FILES 8192
#define CONEXOES_MAX 10
#define MSGFLODSERVER "404- Servidor indisponivel no momento, por favor tente mais tarde."
#define MSGCONEACCEPT "202- Conexão Aceita"

/* Config da conexão Mysql */
#define HOST "localhost"
#define PORTMYSQL 3306
#define USER "root"
#define PSW ""
#define DATABASES "db_tse"

_requisicao *tiporequisicao;

int main(int argc, char const *argv[]){

    struct sockaddr_in sock_server; // Socket servidor
    int status_server, resultBind, resultListem; // Status de cada etapa da conexão

    struct sockaddr_in *clientTemp; // Ponteiro cliente temporario
    int conneClientTemp, lenght_cliente = sizeof(struct sockaddr_in);

    char auxnreq[2][LENGTH_NOP] = {"getallcandidatos\0", "setvoto\0"};

    _mythread threadsConexoes[CONEXOES_MAX]; // Criando threads para cada conexão
    _mythread *auxThread = NULL;                 // Conexão auxiliar para threads

    resetConfigClient(clientTemp, &conneClientTemp);

    tiporequisicao = inicializeRequisicao(auxnreq, 2);

    inicializeConfigServe(&sock_server, IPSERVER, PORTSERVER, &status_server); // Inicializando socket

    // Associando socket: Endereço ip e Porta
    resultBind = bind(status_server, (struct sockaddr *)&sock_server, sizeof(sock_server));
    mensagem("Bind feito com sucesso!", "Falha no Bind! Verifique se o ip estar correto e se a porta estar disponivel.", resultBind);
    
    // Configurando as conexões do servidor
    resultListem = listen(status_server, CONEXOES_MAX);
    mensagem("Listen configurado com suceso!", "Erro ao configurar listen", resultListem);

    mensagem("Servidor no AR", NULL, 1);

    inicializeThreads(threadsConexoes, CONEXOES_MAX);

    while (1){

        // Esperando conexão de um cliente
        conneClientTemp = accept(status_server, (struct sockaddr *)&clientTemp, (socklen_t *)&lenght_cliente);

        if (conneClientTemp < 0) continue;
        
        auxThread = searchThread(threadsConexoes, CONEXOES_MAX);
        if(auxThread == NULL){

            // Enviando para cliente q a conexão foi recusada
            send(conneClientTemp, MSGFLODSERVER, sizeof(MSGFLODSERVER), 0); 
            close(conneClientTemp);
            resetConfigClient(clientTemp, &conneClientTemp);
            continue;
        }

        auxThread->conex_cliente = conneClientTemp;
        pthread_create(auxThread->processo, NULL, &execTask, auxThread);
        
        resetConfigClient(clientTemp, &conneClientTemp); // Resetando dados do temporario
    }

    return 0;
}

void *execTask(void *thread){

    _mythread *cli = thread;
    char buffaux[10];

    send(cli->conex_cliente, MSGCONEACCEPT, sizeof(MSGCONEACCEPT), 0); // Enviando para cliente q a conexão foi aceita

    recv(cli->conex_cliente, buffaux, 1, 0); // Recendo a solicitação do cliente

    cli->codsolicitacao = parseInt(buffaux); // Convertendo a mensagem(valor da solicitação) q vem do usuario para inteiro

    MYSQL connection;

    switch(cli->codsolicitacao){ // Vericando solicitação

        case 0:{ // Código solicitão = 0: lista de todos os candidatos
            
            printLog(&cli->conex_cliente, tiporequisicao[cli->codsolicitacao].nome); // printado log no console do servidor

            mysql_init(&connection); // Inicializando conexão MYSQL

            if (mysql_real_connect(&connection, HOST, USER, PSW, DATABASES, PORTMYSQL, NULL, 0)){ // Vericando se deu algum erro na conexão
                
                int qt, i;
                _candidato *_candidatos = getallcandidatos(&connection, &qt);

                if(_candidatos != NULL){
                    
                    char *text = parseRJSON(_candidatos, qt, LENGTH_FILES, &i);
                    send(cli->conex_cliente, text, i, 0);

                }else{
                    send(cli->conex_cliente, "Falha na consulta\0", 19, 0);
                }
                

            } else{
                printErro("MYSQL conexão", mysql_error(&connection));
                send(cli->conex_cliente, "Falha na consulta\0", 19, 0);
            }

            break;
        } 

        case 1:{ // Código solicitão = 1: Votar em um candidato

            printLog(&cli->conex_cliente, tiporequisicao[cli->codsolicitacao].nome); // printado log no console do servidor
            recv(cli->conex_cliente, buffaux, 5, 0); // recebendo id do candidato
            
            mysql_init(&connection); // Inicializando conexão MYSQL

            if (mysql_real_connect(&connection, HOST, USER, PSW, DATABASES, PORTMYSQL, NULL, 0)){ // Vericando se deu algum erro na conexão
                
                int v = efetueVoto(&connection, buffaux);
                char result[2][45] = {"Candidato inexistente!", "Voto efetuado com sucesso!"};

                send(cli->conex_cliente, result[v], strlen(result[v]), 0); // Retornando resultado
            } else{
                printErro("MYSQL conexão", mysql_error(&connection));
                send(cli->conex_cliente, "Falha ao efetuar voto\0", 19, 0);
            }

            break;
        } 

        case 2:{ // Código solicitão = 1: Votar em um candidato

            printLog(&cli->conex_cliente, tiporequisicao[cli->codsolicitacao].nome); // printado log no console do servidor
            recv(cli->conex_cliente, buffaux, 5, 0); // recebendo id do candidato
            
            mysql_init(&connection); // Inicializando conexão MYSQL

            if (mysql_real_connect(&connection, HOST, USER, PSW, DATABASES, PORTMYSQL, NULL, 0)){ // Vericando se deu algum erro na conexão
                
                int v = efetueVoto(&connection, buffaux);
                char result[2][45] = {"Candidato inexistente!", "Voto efetuado com sucesso!"};

                send(cli->conex_cliente, result[v], strlen(result[v]), 0); // Retornando resultado
            } else{
                printErro("MYSQL conexão", mysql_error(&connection));
                send(cli->conex_cliente, "Falha ao efetuar voto\0", 19, 0);
            }

            break;
        } 
    }
    
    cli->status = 0;
}
