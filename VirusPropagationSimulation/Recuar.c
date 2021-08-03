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
#include <string.h>

#include "utils.h"
#include "structs.h"
#include "struct_recuar.h"

precua carregaIteracao(precua lista, ppessoa p, int *totPess){
    
    precua new = NULL;
    precua aux = NULL;
    
    //Cria novo nó do tamanho recua
    new = malloc(sizeof(recua));
    if(new == NULL){
        printf("Erro na alocacao de memoria");
        return lista;
    }
    
    // Carrega dados que se encontram na lista de recuperacao
    new->nPess = *totPess;
    new->proxlista = gravaDadosREC(p);
    new->pnt = NULL;
    
    //Inserir new na lista ligada
    if(lista == NULL)
        return new;
    else{
        aux = lista;
        while(aux->pnt != NULL)
            aux = aux->pnt;
        aux->pnt = new;
    }
    return lista;
}

ppessoa recuperaListaREC(precua listaREC, ppessoa p, int* totPess,plocal espaco,int totEsp,int arrEsp[]){
    
    precua aux = listaREC;
    ppessoa pont = NULL;
    int op, conta = 0;
    
    //Conta quantas iterações existem
    while(aux!=NULL){
        conta++;
        aux = aux->pnt;
    }
    //Caso nao exista iteracoes
    if ( conta == 0 ){
        printf("\nNao existem iteracoes para recuperar");
        return p;
    }
    //Total de iteracoes que pode recuperar, sempre <=3
    printf("\nPode recuar um total de %d iteracoes\n",conta);
    printf("Pressione '0' para voltar ao menu...\n\n");
    
    do{
        printf("Que iteracao pretende recuperar: ");
        scanf("%d",&op);
    }while(op > conta || op < 0);
    
    //Caso o utilizador queira sair, pressiona 0
    if( op == 0 ){
        printf("Nao foi carregada nenhuma iteracao\n");
        return p;
    }
    
    //Volta a colocar o ponteiro da lista de aux no inicio para poder andar pela lista de novo
    aux = listaREC;
    conta = 1;
    //Enquanto o contador for diferente a opcao selecionado pelo utilizador, procura a iteracao pedida pelo utilizador
    while(conta != op){
        conta ++;
        aux = aux->pnt;
    }
    
    //Apos encontrar essa iteracao, pont fica com os dados
    pont = aux->proxlista;
    (*totPess) = aux->nPess;   //
    printf("\nForam recuperadas no total %d pessoas...\n",*totPess);
    //Adicionado controlador de espaco para garantir que a capacidade fica correta.
    ControlaCapacidade(pont,espaco,totEsp,arrEsp);
    mostra_pessas_orde_esp(pont,espaco,totEsp);
    
    return pont;
}  
ppessoa gravaDadosREC(ppessoa p){
    ppessoa new = NULL, init = NULL, aux = NULL;
    
    //aloca espaço para a lista das pessoas a recuperar
    while(p != NULL){
        new = malloc(sizeof(pessoa));
        if(new == NULL)
            return init;
        //copia dados da lista atual para a de recuperacao
        strcpy(new->id , p->id);
        new->idade = p->idade;
        new->estado = p->estado;
        new->dias_inf = p->dias_inf;
        new->espaco = p->espaco;
        new->prox = NULL;
        
        //Adiciona a pessoa a lista de recuperacao
        if(init == NULL)
            init = new;
        else{
            aux = init;
            while(aux->prox != NULL)
                aux = aux->prox;
            
            aux->prox = new;
        }
        p = p->prox;
    }
    return init;
}

void imprimeListaRecuperacao(precua listaREC,plocal espaco, int totEsp,int arrEsp[]){
    int conta = 1;
    while(listaREC != NULL){
        //Adicionado controlador de espaco para garantir que a capacidade fica correta.
        espaco = ControlaCapacidade(listaREC->proxlista,espaco,totEsp,arrEsp);
        printf("Iteracao numero: %d com uma lista de %d pessoas...\n",conta++,listaREC->nPess);
        mostra_pessas_orde_esp(listaREC->proxlista,espaco,totEsp);
        listaREC = listaREC->pnt;
        puts("\n\n");
    }
}

precua Mantem3itera(precua listaREC){
    
    precua aux = listaREC;
    //Percorre a lista enquanto houver 3 nós
    int conta=1;
    while(conta <= 4){
        //caso o ponteiro para o nó a seguir ao 3 esteja a null, quer dizer que só existem 3 nós, logo não é necessário apagar o mais antigo(1º)
        if(aux == NULL)
            return listaREC;
        aux = aux->pnt;
        conta++;
    }
    
    //Caso existam 4 nodes, liberta o mais antigo, mantendo os ultimos 3
    aux = listaREC->pnt;     //O inicio da nova lista init passa a ser o 2º nó, mantendo os 3 nós pedidos
    liberta_lista(listaREC->proxlista);
    free(listaREC);
    
    return aux;
}

plocal ControlaCapacidade(ppessoa p, plocal espaco, int totEsp,int arrEsp[]){
    
    ppessoa aux = p;
    int i;
    for(i=0; i< totEsp; i++ ){
        espaco[i].capacidade = arrEsp[i];
    }
    
    for(i=0; i < totEsp; i++){
        aux=p;                  //volta ao inicio da lista o aux.
        while(aux != NULL){
            if(aux->espaco == espaco[i].id) //Sempre que verifica que a pessoa tem o espaço em causa, decrementa capacidade do espaco
                espaco[i].capacidade --;
            aux=aux->prox;
        }
    }
    return espaco;
}

void apagaListaInterna(precua listaREC){
    while(listaREC != NULL){
        liberta_lista(listaREC->proxlista);
        listaREC = listaREC->pnt;
    }
}