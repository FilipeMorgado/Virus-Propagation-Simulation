/*
    // Trabalho Pratico Programacao - LEI
   // DEIS-ISEC 2019-2020
 * 
 -> Criado por: Filipe Daniel Ramos Morgado
 -> Número de aluno: a2019137625
 
 */

#ifndef STRUCT_RECUAR_H
#define STRUCT_RECUAR_H

typedef struct rec recua, *precua;
struct rec{
    int nPess;          //guarda nr de pessoas
    ppessoa proxlista;  //Ponteiro para a prox pessoa da lista de pessoas
    precua pnt;    //ponteiro para a proxima lista da lista de recuperados
};

void imprimeListaRecuperacao(precua listaREC,plocal espaco, int totEsp,int arrEsp[]);

ppessoa gravaDadosREC(ppessoa p);
ppessoa recuperaListaREC(precua listaREC, ppessoa p, int* nPes,plocal espaco,int totEsp,int arrEsp[]);
precua carregaIteracao(precua listaREC, ppessoa p, int* nPes);
precua Mantem3itera(precua listaREC);

plocal ControlaCapacidade(ppessoa p, plocal espaco, int nEsp,int arrEsp[]);

void apagaListaInterna(precua listaREC);


#endif /* STRUCT_RECUAR_H */

