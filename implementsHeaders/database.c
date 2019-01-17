/*
 * implementação do header: ../headerfiles/database.h
 * detalhes das funções estão no header
*/

#include "../headerfiles/database.h"
#include "../headerfiles/format_printconsole.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

_candidato *getallcandidatos(MYSQL *connection, int *qtRegistros){

    MYSQL_RES *result;                // Ponteiro para o resutado da consulta
    MYSQL_ROW registro;               // Variavel q guadará o registro temporariamente
    MYSQL_FIELD *nameCampos;          // Vetor de nome das colunas
    _candidato *allCandidatos = NULL; // Vetor com os candidatos
    *qtRegistros = 0;

    char query[] = "SELECT `cand_id`, `cand_nome`, `carg_nome`, `part_nome`, `part_sigla`, count(`voto_id_cand`) as `votos` FROM `tb_candidato` INNER JOIN `tb_cargo` ON `cand_id_carg` = `carg_id` INNER JOIN `tb_partido` ON `cand_id_part` = `part_id` LEFT JOIN `tb_voto` ON `cand_id` = `voto_id_cand` GROUP BY(`voto_id_cand`) ORDER BY(`votos`) DESC;";

    if (mysql_query(connection, query)){ // Vericando se deu algum erro na query

        printErro("MYSQL query", mysql_error(connection));
        return allCandidatos;
    }

    result = mysql_store_result(connection); // Passando a referência dos registros

    if (result){ // Verificando se há algum registro

        *qtRegistros = mysql_num_rows(result);

        allCandidatos = malloc(sizeof(_candidato) * (*qtRegistros)); // Alocando memória para vetor
        int i = 0;                                                   // Contador

        while ((registro = mysql_fetch_row(result)) != NULL){ // Percorrendo registros
            strcpy(allCandidatos[i].id, registro[0]);
            strcpy(allCandidatos[i].nome, registro[1]);
            strcpy(allCandidatos[i].cargo, registro[2]);
            strcpy(allCandidatos[i].partido, registro[3]);
            strcpy(allCandidatos[i].sigla_patido, registro[4]);
            strcpy(allCandidatos[i].qtVotos, registro[5]);
            i++;
        }
    }

    mysql_close(connection);
    return allCandidatos;
}

int efetueVoto(MYSQL *connection, char const *id){

    char query[] = "INSERT INTO  `tb_voto` (`voto_id_cand`) VALUES (?);";
    if (mysql_query(connection, queryFormat(query, id))){ // Vericando se deu algum erro na query
        printErro("MYSQL query", mysql_error(connection));
        return 0;
    }
    mysql_close(connection);
    
    return 1;
}

