/*
    // Trabalho Pratico Programacao - LEI
   // DEIS-ISEC 2019-2020
 * 
 -> Criado por: Filipe Daniel Ramos Morgado
 -> Número de aluno: a2019137625
 
 */

//Estrutura da preparação com as estruturas das pessoas e espaços
#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct sala local,*plocal;
struct sala{
    int id;
    int capacidade;
    int liga[3];
};

typedef struct pessoas pessoa, *ppessoa;
struct pessoas {
    char id[50];
    int idade;
    char estado;
    int dias_inf;
    int espaco;
    ppessoa prox;
};


//Funções utilizadas para carregar espaços e pessoas, distribuição e para mostrar ficheiros

//Tratamento dos espaços
local* carregaEspaco(local *espaco,int *totEsp);
void imprime_espaco(local espaco[],int totEsp);
int verificaID(local espaco[],int totEsp);
int verificaLigacao(local espaco[], int totEsp);

ppessoa carregaPessoas(char *NomeFichPess);
int verificaDadosPessoas(ppessoa listaP);

//Distribui Pessoas
ppessoa distribui_Pessoas(ppessoa NLpessoa, plocal espaco, int totEsp,int *totPess);

//Impressão
void imprime_pessoas(ppessoa listaP);
void mostra_pessas_orde_esp(ppessoa p, plocal espaco, int totEsp);

//Liberta lista
void liberta_lista(ppessoa p);
#endif /* STRUCTS_H */

