/*
 * Headear função: inicializar, configurar objetos
 * implementação da funções: ../implementsHeaders/inicializedefault.c
 */

#ifndef inicializedefault
#define inicializedefault

#include <sys/socket.h>
#define LENGTH_NOP 110 // Tamanho padrão de string

/*
 * Struct modelo das requisições q o servidor vai possui
 */
typedef struct _requisicao{
    int id;
    char nome[LENGTH_NOP];
}_requisicao;

/*
 *Inicializa as configurações do servidor 
 *@param {sockaddr_in: socket server, ip, porta, local para armazenar resultado da criação do socket}
 *@saida mensagem de sucesso ou não, na criação do socket
 */
void inicializeConfigServe(struct sockaddr_in *serv, char const *ipserver, int portaserver, int *status);

/*
 *Inicializa/seta valore da requisiçoes
 *@param {nomes q serão atribuido a requisição, quantidade}
 *@return ponteiro com as requsicoes
 */
_requisicao *inicializeRequisicao(char const (*nome)[LENGTH_NOP], int qt);

/*
 *Restaura o padrão do cliente, para ficar esperando uma nova conexão
 *@param {cliente temporario, numero da conexão aceita pelo socket}
 */
void resetConfigClient(struct sockaddr_in *clienTemp, int *connectClien);

#endif