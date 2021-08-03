/*
    // Trabalho Pratico Programacao - LEI
   // DEIS-ISEC 2019-2020
 * 
 -> Criado por: Filipe Daniel Ramos Morgado
 -> Número de aluno: a2019137625
 
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "structs.h"
#include "utils.h"

ppessoa distribui_Pessoas(ppessoa listaP, plocal espaco, int totEsp,int *totPess) {
    ppessoa aux = listaP;
    
    int localrand = 0, cap[totEsp], flag = 0;
    
    for (int i = 0; i < totEsp; i++)
        cap[i] = espaco[i].capacidade;  //Criação de um array com a capacidade de cada local

    while (aux != NULL) {
        flag = 0;
        for (int k =0 ; k < totEsp; k++) { //Verifica se tem capacidade nos locais
            if (cap[k] == 0)
                flag++;     
        }
       
        if (flag == totEsp){
            printf("\nNao existe espaco disponivel para distribuir as pessoas"); // caso nenhum local tenha qualquer espaco logo no inicio da distribuicao
            return NULL;
        }
        aux->espaco = 0;
        (*totPess)++;
        
        do {
            localrand = intUniformRnd(0, totEsp - 1);   //Escolha aleatória de um dos espaços a ser inserida a pessoa obedecendo a regra de ter capacidade (>0) 
        } while (cap[localrand] == 0);
        cap[localrand]--;
        aux->espaco = espaco[localrand].id;
        
        //Caso chegue ao ultimo espaco disponivel da simulacao apos a distribuicao da ultima pessoa, evita ler uma nova pessoa desnecessariamente para entrar no if(flag==totEsp) 
        if(flag == totEsp-1 && cap[localrand]==0){
            printf("\nNao existe espaco disponivel para todas as pessoas, simulacao vai comecar... "); 
            aux->prox=NULL;
            return listaP;
        }
        aux = aux->prox;
    }
    
    return listaP;
}
void mostra_pessas_orde_esp(ppessoa p, plocal espaco, int totEsp) {
    
    ppessoa aux = p;
    
    for (int i = 0; i < totEsp; i++) {
        printf("\n____________________________________________________________________________________________________\n");
            printf("ID: %d\t", espaco[i].id);
            printf("Capacidade: %d\t\t", espaco[i].capacidade);
            printf("1->Ligacao: %d  || \t", espaco[i].liga[0]);
            printf("2->Ligacao: %d  || \t", espaco[i].liga[1]);
            printf("3->Ligacao: %d  ||\n",  espaco[i].liga[2]);
            printf("----------------------------------------------------------------------------------------------------\n");
        aux = p;
        while (aux != NULL) {
            if (aux->espaco == espaco[i].id) {
                if (aux->estado == 'D') {
                    printf("\n\t Nome: %s\t Idade: %d\t Estado: %c\t Dias Infetado: %d",
                            aux->id, aux->idade, aux->estado, aux->dias_inf);
                } else {
                    printf("\n\t Nome: %s\t Idade: %d\t Estado: %c", aux->id, aux->idade, aux->estado);
                }
            }
            aux = aux->prox;
        }
    }
}
