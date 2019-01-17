/*
 * Headear função: formatar as saidas dos texto no console
 * implementação da funções: ../implementsHeaders/format_printconsole.c
 */

#ifndef format_printconsole
#define format_printconsole

#include "database.h"

/*
 *Print status/resultado da tarefa 
 *@param { Msg caso sucesso, Msg caso falhe, valor do status, valor q define a falha }
 *@saida print mensagem 
 */
void mensagem(char const *textsucess, char const *textfailed, int status);

/*
 *Print erro de uma tarefa
 *@param { texto adicional, mensagem de erro}
 *@saida print mensagem formatada do erro 
 */
void printErro(char const *text, char const *erro);

/*
 *Print Log de execuçao
 *@param {codigo de quem executou, log da tarefa executada}
 *@saida print mensagem formatada do log 
 */
void printLog(int const *codigo, char const *solicitacao);

/*
 *Converte string em número
 *@param {string}
 *@retorn ponteiro para o número convertido
 */
int parseInt(char const *test);

/*
 *Tranforma o vetor de candidatos em uma string com formato semelhante ao JSON
 *formato {id, nome, cargo, partido, sigla_patido, URLfoto}
 *@param {vetor_candidatos, qantidade de elemento, tamanho maximo do arquivo, variavel q receberá o tamanho ultilizado no arquivo} 
 *@return string com formato semelhante ao JSON
 */
char *parseRJSON(_candidato *vetCandi, int qtCandi, int max_buff, int *lengthT);

/*
 *Concatena uma string com outra  
 *@param {string destino, string a ser copiada, posição onde sera iniciada a concatenação(string destino), separdor de palavras(valor '\0' caso não queira)} 
 */
void transfString(char *dest, char *palavra, int *posIniD, char separador);

/*
 *Concatena uma query com os parametros passado 
 *@param {string query, string com valor a ser concatenado)
 *@return nova string
 */
char *queryFormat(char const *query, char const *valor);


#endif