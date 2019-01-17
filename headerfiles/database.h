/*
 * Headear função: Efetuar operações ralacionadas ao banco de dados
 * implementação da funções: ../implementsHeaders/database.c
 */

#ifndef database
#define database

#include <mysql/mysql.h>

/*
 * Struct modelo, informações dos candidatos
 */
typedef struct _candidato{
    char id[15],
        nome[45],
        url_foto[256],
        cargo[35],
        partido[65],
        sigla_patido[15],
        qtVotos[10];
}_candidato;

/*
 *Retorna a todos o candidatos que estão no banco 
 *@param {conexão mysql, variavel onde serão armazenada a quantidades de registros retornado}
 *@return vetor de _candidatos
 */
_candidato *getallcandidatos(MYSQL *connection, int *qtRegistros);

/*
 *Insere voto 
 *@param {conexão mysql, id do candidato}
 *@return resultado da operação
 */
int efetueVoto(MYSQL *connection, char const *id);

#endif