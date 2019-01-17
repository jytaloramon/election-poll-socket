/*
 * Headear função: Prover funcionalidades multitarefas: theads
 * implementação da funções: ../implementsHeaders/process_assicrono.c
 */

#ifndef process_assicrono
#define process_assicrono

#include <pthread.h>

/*
 *Guarda informações da thread
 */
typedef struct _mythread{
    pthread_t *processo; // thread
    int status, conex_cliente; // status: informação se a thread estar ou não sendo execultada, conex...: id da conexão do cliente vinculado a thread
    int codsolicitacao; // Codigo da requisição feita pelo cliente
}_mythread;

/*
 *execulta tarefa
 *@param objeto do tipo _mythread
 */
void *execTask(void *thread);

/*
 *Inicialize as threads, setando valores padrões e alocando-as 
 *@param {vetor de _mythread, quantidades de threads do sistema}
 */
void inicializeThreads(_mythread *threads, int qThread);

/*
 *Busca threads disponiveis a serem usadas
 *@param {vetor de mythreads, quantidades de threads do sistema}
 *@return endereço da thread disponivel, ou NULL caso não encontre 
 */
_mythread *searchThread(_mythread *threads, int qThread);

#endif