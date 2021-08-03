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
#include "struct_recuar.h"
#include "struct_Sim.h"
#include "struct_Propaga.h"
#define TAM 100

local* carregaEspaco(local *espaco,int *totEsp)
{
    FILE *f;
    local aux, *arrD;
    char fichEspaco[20];
    //Pede ficheiro a abrir
    printf("Indique o ficheiro de espaco que quer abrir: ");
    scanf("%s",&fichEspaco);
    
    //verifica ligacao do ficheiro
    if((f = fopen(fichEspaco,"rb")) == NULL){
        printf("Erro no acesso ao ficheiro:  %s \n",fichEspaco);
        return NULL;
    }
    
    //leitura do ficheiro binario local a local
    fread(&aux, sizeof(local),1,f);
    while (feof(f) == 0) {
        // Realoca espaco para array de espacos
        arrD = realloc(espaco, sizeof(local) * ((*totEsp)+1));
        if (arrD == NULL) {
            printf("Erro na realocacao.");
            return NULL; //Não le corretamente, programa termina
        }     
        espaco = arrD; 
        espaco[(*totEsp)++]=aux;
        fread(&aux, sizeof(local),1,f);
    }
    fclose(f);
    return arrD;
}


ppessoa carregaPessoas(char *NomeFichPess){    
    ppessoa listaP = NULL, nova, aux;
    int totLido = 0;
    FILE *f;
    f = fopen(NomeFichPess, "rt");
    if (f == NULL) {    //Verificacao de problemas ao abrir o ficheiro
        printf("Erro no acesso ao ficheiro: %s\n", NomeFichPess);
        fclose(f);
        return NULL;
    }
    do {
        nova = malloc(sizeof (pessoa));     //criacao de espaco para a nova pessoa
        if (nova == NULL) {
            printf("Erro na alocação de memoria\n");
            fclose(f);
            return NULL;
        }
        totLido = fscanf(f, " %s %d %c", nova->id, &(nova->idade), &(nova->estado));    //Leitura dos 3 primeiros campos do txt
        if (totLido == 3) {
            if (nova->estado == 'D') {          //Caso esteja infetado, também vai ter os dados dos dias infetados, logo é feita a leitura desses dados
                fscanf(f, " %d ", &(nova->dias_inf));
            }
            nova->prox = NULL;
        if(listaP == NULL)  //Se a lista estiver vazia ainda, a lista vai ficar com o valor da 1º pessoa
            listaP = nova;
        else{               // caso contrario, é feita a ligação do ultimo elemento da lista ao lido atualmente
            aux = listaP;
            while(aux->prox !=  NULL)
                aux = aux->prox;
            aux->prox = nova;           
        }
        }
        if(totLido<3)          // Caso o total lido seja menor que o minimo dos 3 dados base, quer dizer que não existem mais dados, logo o espaco alocado é libertado
            free(nova);
    }while (totLido == 3);  
    fclose(f);
   return listaP;
}

int verificaDadosPessoas(ppessoa listaP) {
    ppessoa aux=listaP;
    while(aux != NULL){
    if (aux->estado != 'S' && aux->estado != 'D' && aux->estado != 'I')
        return 0;
    if (aux->idade <0 && aux->idade > 120)
        return 0;
   // if(verifica_existe_nome(listaP,aux->id)==0)
     //   return 0;
    aux=aux->prox;
    }
    return 1;
}


void imprime_pessoas(ppessoa listaP) {
    if (!listaP) {
        printf("\nLista vazia! Nada a imprimir.");
        return;
    }

    while (listaP != NULL) {
        if (listaP->estado == 'D') {
            printf("\n Nome: %s\t Idade: %d\t Estado:%c\t Dias Infetado:%d\t ",
                    listaP->id, listaP->idade, listaP->estado, listaP->dias_inf);
        } else {
            printf("\n Nome: %s\t Idade: %d\t Estado:%c", listaP->id, listaP->idade, listaP->estado);
        }
        listaP = listaP->prox;
    }
}

void imprime_espaco(local espaco[],int totEsp){
    
   for(int i = 0; i < totEsp; i++)  {
            printf("ID: %d\t", espaco[i].id);
            printf("Capacidade: %d\t", espaco[i].capacidade);
            printf("1->Ligacao: %d  || \t", espaco[i].liga[0]);
            printf("2->Ligacao: %d  || \t", espaco[i].liga[1]);
            printf("3->Ligacao: %d  ||\n",  espaco[i].liga[2]);
        }
}

int verificaID(local espaco[],int totEsp)
{
    int i,j;
    for(i = 0; i < totEsp; i++)
    {
        if(espaco[i].liga <= 0)  //verifica se tem id's negativos ou com valor 0
        {
            printf("O id e zero ou negativo.");
            return 0;
        }
            for(j = 0; j < totEsp; j++)
            {
                if (j!=i)
                {
                    if (espaco[j].id == espaco[i].id)   //Verifica existencia de ID's repetidos
                    {
                        printf("O id está repetido.");
                        return 0;
                    }
                }
            }      
        printf("Os id's estao corretos.\n\n");
        return 1;
    }
}

int verificaLigacao(local espaco[], int totEsp)
{
    int i, j, k,t, aux, flag=0;
        
    for(i = 0; i < totEsp; i++) {       //Percorre local a local
        for (j = 0; espaco[i].liga[j] != -1 && j<3; j++) {  //Se existir ligacao com outro local qualquer 
            aux = espaco[i].liga[j];                        //aux guarda id do local com que tem ligacao
            for (k = 0; k < totEsp; k++) {                  //percorre todos os locais existentes a procura do id da ligacao
                if (espaco[k].id == aux) {                  //Se encontrar esse local em que existe ligacao
                    flag = 0;                               
                    for (t = 0; t < 3; t++) { //3 e o maximo de ligacoes possiveis entre ficheiros
                        if (espaco[k].liga[t] == espaco[i].id)  //Verifica se a ligacao é mutua entre uma e outra
                            flag = 1;                           //Se for mutua, não existe problemas de ligacao
                    }
                    if (flag == 0) {
                        printf("\nErro na ligacao.\n");        // caso contrario, existe uma falha de ligacação entre locais
                        return 0;
                    }
                }
            }
        }
    }
    printf("\nLigacoes entre espacos efetuada com sucesso.\n\n");   //Caso todas as ligacoes estejam corretas, apresenta mensagem de suceseso
    return 1;
}

void liberta_lista(ppessoa p){
    ppessoa aux;
    
    while(p != NULL){
        aux = p;
        p = p->prox;
        free(aux);
    }
}
