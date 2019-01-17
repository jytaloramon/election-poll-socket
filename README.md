Instituto Federal De Alagoas - IFAL

Disciplina: Introdução a redes de computadores

Professor: Matheus Torquato

##Sistema pesquisa eleitoral

#Objetivo

Implementar um sistema de pesquisa eleitoral, com formato "cliente -> servidor", utilizando socket e persistindo dados em arquivos ou em um SGBD

#Especificações

Linguagem: *C

GCC utilizado: *8

SGBD: *MySQL

#Instruções
   
*Para executar os arquivos altere as variaveis IPSERVE(ip da sua maquina) E PORTSERVE(caso queira ou necessite) nos arquivo "Cliente.c e Servidor.c"

*Caso altere algum arquivo na pasta "implementsHeaders" execute o seguinde comando(na pasta) para recompilar os arquivos: "gcc -c *.c"

*Para o funcionamento do servidor é necessario ter instalado o mysql

   - Execute "CreateDatabase.sql" para cria o banco e as tabelas

   - Execute "PreencherTable.sql" para preencher as tabelas (opcional)

*Compilar Cliente.c: gcc Cliente.c -o cliente

*Compilar Servidor.c: gcc -L/usr/lib/mysql -lmysqlclient -pthread implementsHeaders/*.o Servidor.c -o servidor

